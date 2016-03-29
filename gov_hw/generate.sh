#!/bin/bash

read -p Chapter: chapter

for i in `seq 1 4`;
do
	python generate.py "./raw/ch0$chapter.txt" $i > "./summary/$chapter\_$i.txt"
done
