#!/usr/bin/python

import candycompetition
import mycandycompetition

print "Output follows this format:"
print "[Test case]"
print "[Correct output]"
print "[Your output]"
print "\n"

print "swap() test case:"
print 'swap("aabbabababaabababa", "a", "b")'
print candycompetition.swap("aabbabababaabababa", "a", "b")
print mycandycompetition.swap("aabbabababaabababa", "a", "b")
print 'swap("abuehis f;lie da alsieh bdsfh", "a", "b")'
print candycompetition.swap("abuehis f;lie da alsieh bdsfh", "a", "b")
print mycandycompetition.swap("abuehis f;lie da alsieh bdsfh", "a", "b")
print "\n"

print "peterpan() test case:"
print 'peterpan("aa"):'
print candycompetition.peterpan("aa")
print mycandycompetition.peterpan("aa")
print 'peterpan("I am a dog.")'
print candycompetition.peterpan("I am a dog")
print mycandycompetition.peterpan("I am a dog")
print 'peterpan("aabbbbbbaaabababa")'
print candycompetition.peterpan("aabbbbbbaaabababa")
print mycandycompetition.peterpan("aabbbbbbaaabababa")
print "\n"

print "growl() test case:"
print 'growl("bbddbbbfeef")'
print candycompetition.growl("bbddbbbfee")
print mycandycompetition.growl("bbddbbbfee")
print 'growl("yolo the darth vader has come")'
print candycompetition.growl("yolo the darth vader has come")
print mycandycompetition.growl("yolo the darth vader has come")
print 'growl("absdfffbeijffaaae")'
print candycompetition.growl("absdfffbeijffaaae")
print mycandycompetition.growl("absdfffbeijffaaae")
print "\n"

print "overdose() test case:"
print 'overdose("The swift brown dog jumped over the lazy blue fence", "o")'
print candycompetition.overdose("The swift brown dog jumped over the lazy blue fence", "o")
print mycandycompetition.overdose("The swift brown dog jumped over the lazy blue fence", "o")
print 'overdose("myspacebarisbrokenplzsendhelp", "a")'
print candycompetition.overdose("myspacebarisbrokenplzsendhelp", "a")
print mycandycompetition.overdose("myspacebarisbrokenplzsendhelp", "a")
print "\n"

print "dontgo() test case:"
print 'dontgo("anosejsdfabb", "a", "b")'
print candycompetition.dontgo("anosejsdfabb", "a", "b")
print mycandycompetition.dontgo("anosejsdfabb", "a", "b")
print 'dontgo("The big blue dog named Clifford?", "n", "m")'
print candycompetition.dontgo("The big blue dog named Clifford?", "n", "m")
print mycandycompetition.dontgo("The big blue dog named Clifford?", "n", "m")
print 'dontgo("aaabb", "a", "b")'
print candycompetition.dontgo("aaabb", "a", "b")
print mycandycompetition.dontgo("aaabb", "a", "b")
print "\n"

print "isPrime() test case:"
print 'isPrime(0)'
print candycompetition.isPrime(0)
print mycandycompetition.isPrime(0)
print 'isPrime(1)'
print candycompetition.isPrime(1)
print mycandycompetition.isPrime(1)
print 'isPrime(2)'
print candycompetition.isPrime(2)
print mycandycompetition.isPrime(2)
print 'isPrime(10)'
print candycompetition.isPrime(10)
print mycandycompetition.isPrime(10)
print 'isPrime(210929)'
print candycompetition.isPrime(210929)
print mycandycompetition.isPrime(210929)
print "\n"

print "primes() test case:"
print "primes(0)"
print candycompetition.primes(0)
print mycandycompetition.primes(0)
print "primes(1)"
print candycompetition.primes(1)
print mycandycompetition.primes(1)
print "primes(10)"
print candycompetition.primes(10)
print mycandycompetition.primes(10)
print "primes(200)"
print candycompetition.primes(200)
print mycandycompetition.primes(200)
print "\n"

print "factor() test case:"
print "factor(0)"
print candycompetition.factor(0)
print mycandycompetition.factor(0)
print "factor(1)"
print candycompetition.factor(1)
print mycandycompetition.factor(1)
print "factor(2)"
print candycompetition.factor(2)
print mycandycompetition.factor(2)
print "factor(100)"
print candycompetition.factor(100)
print mycandycompetition.factor(100)
print "factor(875672)"
print candycompetition.factor(875672)
print mycandycompetition.factor(875672)
print "factor(43046721)"
print candycompetition.factor(43046721)
print mycandycompetition.factor(43046721)
print "\n"

print "place() test case:"
print "place(123456789, 1)"
print candycompetition.place(123456789, 1)
print mycandycompetition.place(123456789, 1)
print "place(123456789, 2)"
print candycompetition.place(123456789, 2)
print mycandycompetition.place(123456789, 2)
print "place(123456789, 5)"
print candycompetition.place(123456789, 5)
print mycandycompetition.place(123456789, 5)
print "place(123456789, 7)"
print candycompetition.place(123456789, 7)
print mycandycompetition.place(123456789, 7)
print "\n"

print "sort() test case:"
print "sort([1, 4, 5, 2, 4, 6, 3, 5, 2, 5, 7])"
print candycompetition.sort([1, 4, 5, 2, 4, 6, 3, 5, 2, 5, 7])
print mycandycompetition.sort([1, 4, 5, 2, 4, 6, 3, 5, 2, 5, 7])
print "sort([99, 2, 5, 1, 33, 5, 2, 66, 4])"
print candycompetition.sort([99, 2, 5, 1, 33, 5, 2, 66, 4])
print mycandycompetition.sort([99, 2, 5, 1, 33, 5, 2, 66, 4])
