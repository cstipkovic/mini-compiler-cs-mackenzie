main: clean
	gcc -I./src/constants.h ./src/main.c -ansi -o main
clean:
	rm -rf main
