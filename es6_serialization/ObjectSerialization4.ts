import { A, B, C, D, E, F, G } from './TestClasses'

const __type = '__type'

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

export function getReplacerReviver(
  types: SerializableTypes,
): JSONReplacerReviver {
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
      if (Object.prototype.hasOwnProperty.call(value, __type)) {
        throw new Error(
          'Objects to be serialized cannot have a __type property',
        )
      }
      for (const [typename, type] of levelOrderTypes.entries()) {
        if (value instanceof type) {
          Object.defineProperty(value, __type, {
            value: typename,
            enumerable: true,
          })
          return value
        }
      }
      return value
    },
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    reviver(_key: string, value: any): any {
      if (!value) {
        return value
      }
      const typename = Object.getOwnPropertyDescriptor(value, __type)
      if (!typename || !typename.value) {
        return value
      }
      const constructor = levelOrderTypes.get(typename.value)
      if (constructor) {
        const newObject = new constructor()
        delete value.__type
        Object.assign(newObject, value)
        return newObject
      }
      return value
    },
  }
}

const { replacer, reviver } = getReplacerReviver({ A, B, C, D, E, F, G })
const e = new E()
console.log(e)
const parsedStringifiedE = JSON.parse(JSON.stringify(e, replacer), reviver)
console.log(parsedStringifiedE)
