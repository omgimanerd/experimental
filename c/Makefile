all: sizes.out file.out

sizes.out: sizes.c
	gcc sizes.c -o sizes.out

run-sizes:
	./sizes.out

file.out: file.c
	gcc file.c -o file.out

run-file:
	./file.out

clean:
	rm *.out
