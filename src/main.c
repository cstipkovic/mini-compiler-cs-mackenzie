#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Códigos das Constantes */
#define ERROR 404;

/* Struct do token */
typedef struct token {
	int name;
	char* value;
} TOKEN;

/* Lê o arquivo com o código proposto */
void readFile(char text[]) {
	FILE *inputFile;
	inputFile = fopen("./test/test-algC.txt", "r");
	char line[400];

	if (inputFile) {
		while (fscanf(inputFile, "%s ", line) != EOF) {
			strcat(line, " ");
			strcat(text, line);
		}
		fclose(inputFile);
	}
}

TOKEN scanner(char text[], int *pos) {
	TOKEN token;
	token.name = ERROR;
	token.value = NULL;

	(*pos)--;

	return token;
}

int main(int argc, const char *argv[]) {
	int pos, i, inputSize;

	inputSize = 800;
	pos = 0;
	char inputFile[inputSize];
	char found[inputSize];

	for (i = 0; i < inputSize; i++) {
		inputFile[i] = '\0';
	}

	readFile(inputFile);
	char result[inputSize];
	strcpy(result, "");

	char res[inputSize];

	while (pos < strlen(inputFile)) {
		TOKEN token = scanner(inputFile, &pos);
	}

	return 0;
}
