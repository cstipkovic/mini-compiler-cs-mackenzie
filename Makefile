main: clean
	gcc -ansi -o main ./src/main.c -g
clean:
	rm -rf main
