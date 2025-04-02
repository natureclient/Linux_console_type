a.out: src/main.c src/error.c src/typing.c src/terminal.c
	gcc -o bin/a.out src/main.c src/error.c src/filetype.c src/typing.c src/terminal.c

clean:
	rm -f bin/a.out
