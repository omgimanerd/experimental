import { A } from './TestClasses'

interface JSONReplacerReviver {
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  replacer: (this: any, key: string, value: any) => any
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  reviver: (this: any, key: string, value: any) => any
}

export function getReplacerReviver(): JSONReplacerReviver {
  return {
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    replacer(_key: string, value: any): any {
      if (value instanceof A) {
        Object.defineProperty(value, '__type', {
          value: 'A',
          enumerable: true,
        })
      }
      return value
    },
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    reviver(_key: string, value: any): any {
      const objectType = Object.getOwnPropertyDescriptor(value, '__type')
      if (!objectType || !objectType.value) {
        return value
      }
      if (objectType.value === 'A') {
        const newObject = new A()
        delete value.__type
        Object.assign(newObject, value)
        return newObject
      }
      return value
    },
  }
}

const { replacer, reviver } = getReplacerReviver()

const aInstance = new A()
console.log('Instance of A: ', aInstance)
aInstance.print()
const aStr = JSON.stringify(aInstance, replacer)
console.log('JSON.stringify A: ', aStr)
const aParsed = JSON.parse(aStr, reviver)
console.log('JSON.parse A: ', aParsed)
console.log('aParsed.print: ', aParsed.print)
console.log('aParsed.fields: ', aParsed.fields)
aParsed.print()
