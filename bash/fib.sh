#!/bin/bash

function fib() {
    if [ $1 == 0 ] || [ $1 == 1 ]; then
        return 1
    else
        a=`fib $(expr $1 - 1))`
        echo $a
        b=`fib $(expr $1 - 1))`
        echo $b
        return $( $a + $b )
    fi
}
fib 0
echo $?
echo "______"
fib 10
echo $?
  
