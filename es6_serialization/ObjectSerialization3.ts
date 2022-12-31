import { A, B, C, D, E, F, G } from './TestClasses'

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
  return {
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    replacer(_key: string, value: any): any {
      if (!value) {
        return value
      }
      if (Object.prototype.hasOwnProperty.call(value, '__type')) {
        throw new Error(
          'Objects to be serialized cannot have a __type property',
        )
      }
      for (const [typename, type] of Object.entries(types)) {
        if (value instanceof type) {
          Object.defineProperty(value, '__type', {
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
      const objectType = Object.getOwnPropertyDescriptor(value, '__type')
      if (!objectType || !objectType.value) {
        return value
      }
      const objectConstructor = types[objectType.value]
      if (objectConstructor) {
        // eslint-disable-next-line new-cap
        const newObject = new objectConstructor()
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
const stringifiedE = JSON.stringify(e, replacer)
console.log(stringifiedE)
const parsedStringifiedE = JSON.parse(stringifiedE, reviver)
console.log(parsedStringifiedE)
