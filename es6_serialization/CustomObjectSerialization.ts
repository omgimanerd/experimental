/**
 * @fileoverview Returns a JSON replacer and reviver function that allows for
 * registered classes to be serialized and deserialized from JSON objects.
 */

const __typename__ = '__typename__'
const TYPENAME_MAP = 'Map'

type SerializableTypes = {
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  [key: string]: any
}
interface JSONReplacerReviver {
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  replacer: (this: any, key: string, value: any) => any
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  reviver: (this: any, key: string, value: any) => any
}

/**
 * Given an object containing the classes to be serialized/deserialized, this
 * function returns a replacer and reviver function that can be used with
 * JSON.stringify and JSON.parse which will allow for the classes to be
 * serialized into a JSON object and deserialized back into an instance of
 * themselves.
 *
 * The classes must not have a __typename__ property defined since this will be
 * written into the object in order to preserve type information. The classes
 * must also have a default no-argument constructor which will be used to
 * constructor an empty instance of the class. We use Object.assign to assign
 * all enumerable properties into the empty instance.
 *
 * @param types An object specifying the classes that the custom serialization
 * logic will apply to, best specified using the object shorthand notation as {
 * Class1, Class2 }.
 * @returns JSONReplacerReviver, an object with two keys storing the custom
 * replacer and reviver functions to be used with JSON.parse and JSON.stringify
 */
export function getReplacerReviver(
  types: SerializableTypes,
): JSONReplacerReviver {
  // The logic in the custom replacer and reviver functions only works if the
  // types argument is a level order traversal of all the types specified. If
  // a superclass is specified before a subclass, then a serialized subclass
  // will deserialize into its superclass.
  const numSuperclasses = new Map<string, number>()
  for (const [typename, type] of Object.entries(types)) {
    for (const [typenameOther, typeOther] of Object.entries(types)) {
      if (typename === typenameOther) {
        continue
      }
      const currentSuperclasses = numSuperclasses.get(typename) || 0
      if (Object.prototype.isPrototypeOf.call(typeOther, type)) {
        numSuperclasses.set(typename, currentSuperclasses + 1)
      } else {
        numSuperclasses.set(typename, currentSuperclasses)
      }
    }
  }
  const levelOrderTypes = new Map(
    [...numSuperclasses.entries()]
      .sort((a, b) => b[1] - a[1])
      .map((value) => [value[0], types[value[0]]]),
  )

  return {
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    replacer(_key: string, value: any): any {
      if (!value) {
        return value
      }
      // If the object to be serialized has an existing __typename__ property
      if (Object.prototype.hasOwnProperty.call(value, __typename__)) {
        throw new Error(
          'Objects to be serialized cannot have a __typename__ property',
        )
      }
      // ES6 maps are a special case which we will automatically handle, since
      // using Object.assign on an ES6 map will leave it in a funky state.
      if (value instanceof Map) {
        return {
          __typename__: TYPENAME_MAP,
          entries: Array.from(value.entries()),
        }
      }
      // Iterate through the list of specified SerializableTypes to see if the
      // object to serialize is in the list. If it is, write the __typename__
      // field to the object and continue on the way.
      for (const [typename, type] of Object.entries(levelOrderTypes)) {
        if (value instanceof type) {
          Object.defineProperty(value, __typename__, {
            value: typename,
            enumerable: true,
          })
        }
      }
      return value
    },
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    reviver(_key: string, value: any): any {
      if (!value) {
        return value
      }
      const typename = Object.getOwnPropertyDescriptor(value, __typename__)
      if (!typename || !typename.value) {
        return value
      }
      // Special handling for ES6 maps.
      if (typename.value === TYPENAME_MAP) {
        return new Map(value.entries)
      }
      // For all other types, invoke the constructor specified in the types
      // argument and use Object.assign to set all its values.
      const constructor = levelOrderTypes.get(typename.value)
      if (constructor) {
        const newObject = new constructor()
        delete value.__typename__
        Object.assign(newObject, value)
        return newObject
      }
      return value
    },
  }
}

class A {}

class B extends A {}

class C extends B {}

class D extends B {}

class E extends D {}

class F extends A {}

const { replacer, reviver } = getReplacerReviver({
  A,
  B,
  C,
  D,
  E,
  F,
})
const a = new Map()
a.set(1, 2)
a.set('b', 3)

const res = JSON.stringify(a, replacer)
console.log('stringified', res)
const back = JSON.parse(res, reviver)
console.log('back', back, '\n\n\n')

// const p = Player.create('blah', 'empty')
// console.log(p)
// console.log('p instanceof Player', p instanceof Player)
// console.log('p instanceof Entity', p instanceof Entity)
// console.log('Entity instanceof Player', Entity instanceof Player)
// console.log('Player instanceof Entity', Player instanceof Entity)
// console.log(Object.prototype.isPrototypeOf.call(Player, Entity))
// console.log(Object.prototype.isPrototypeOf.call(Entity, Player))
// const res2 = JSON.stringify(p, replacer)
// console.log('res2', res2)
// const back2 = JSON.parse(res2, reviver)
// console.log('back2', back2)

const testvalues = {
  entries: [
    [1, 2],
    ['b', 4],
  ],
}
Object.assign(a, testvalues)
console.log(a)
