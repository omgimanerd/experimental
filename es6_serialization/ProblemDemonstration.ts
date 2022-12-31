// eslint-disable-next-line @typescript-eslint/no-explicit-any
const obj: { [key: string]: any } = {}
obj[1] = 2
// eslint-disable-next-line dot-notation
obj['a'] = 'b'
console.log('Object contents: ', obj)
const stringifiedObj = JSON.stringify(obj)
console.log('Stringified object: ', stringifiedObj)
const parsedObj = JSON.parse(stringifiedObj)
console.log('Parsed object: ', parsedObj, '\n')

const map = new Map()
map.set(1, 2)
map.set('a', 'b')
console.log('Map contents: ', map)
const stringifiedMap = JSON.stringify(map)
console.log('Stringified map: ', stringifiedMap)
const parsedMap = JSON.parse(stringifiedMap)
console.log('Parsed map object', parsedMap)
