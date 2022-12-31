/**
 * @fileoverview Test classes for object serialization
 */

export class A {
  fieldA1 = 'fieldA1'
  fieldA2 = 2

  print(): void {
    console.log('Class A has fields ', this.fieldA1, ', ', this.fieldA2)
  }

  get fields(): string {
    return `${this.fieldA1} + ${this.fieldA2}`
  }
}
export class B extends A {}
export class C extends B {
  fieldC = 'fieldC'

  get fields(): string {
    return this.fieldC
  }
}
export class D extends B {}
export class E extends D {
  fieldE = 'fieldE'

  get fields(): string {
    return this.fieldE
  }

  doSomething(): void {
    console.log('something was done in class E!', this.fieldE)
  }
}
export class F extends A {}
export class G {
  fieldG = 'fieldG'

  doSomething(): void {
    console.log('something was done in class G! ', this.fieldG)
  }
}
