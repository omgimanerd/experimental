#!/bin/bash

printf "Number of arguments: $#\n"
printf "Second arguments: $2\n"
printf "Random word: $( shuf -n 1 /usr/share/dict/words )\n"
word=$( grep -E "^[a-zA-Z]{$1}$" /usr/share/dict/words | shuf -n $2 )
echo $word
echo $word | xargs -n1 -i touch {}.txt

