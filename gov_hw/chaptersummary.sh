#!/bin/bash
read -p "Chapter(ch01)": chapter
read -p Sections: sections
echo $sections
for section in $(seq 1 $sections); do echo $section && echo $section >> test.txt && python generate.py raw/$chapter.unlocked.txt $section >> ./test.txt; done
