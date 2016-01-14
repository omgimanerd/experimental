all: sizes.out file.out struct.out pointer.out cwd.out

sizes.out: sizes.c
	gcc sizes.c -o sizes.out

run-sizes:
	./sizes.out

file.out: file.c
	gcc file.c -o file.out

run-file:
	./file.out

struct.out: struct.c
	gcc struct.c -o struct.out

run-struct: struct.out
	./struct.out

string.out: string.c
	gcc string.c -o string.out

run-string: string.out
	./string.out

pointer.out: pointer.c
	gcc pointer.c -o pointer.out

run-pointer: pointer.out
	./pointer.out

cwd.out: cwd.c
	gcc cwd.c -o cwd.out

run-cwd: cwd.out
	./cwd.out

clean:
	rm *.out
