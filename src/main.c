#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Códigos das Constantes */
#define ERROR 404

/* Struct do token */
typedef struct token {
	int name;
	char* value;
} TOKEN;

TOKEN scanner(char text[], int *pos) {
	TOKEN token;
	token.name = ERROR;
	token.value = NULL;

	(*pos)--;

	return token;
}

int isNumber(char n) {
	if (n == '0' || n == '1' || n == '2' || n == '3' || n == '4' || n == '5' || n == '6' || n == '7' || n == '8' || n == '9') {
		return 1;
	}

	return 0;
}

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

void writeFile(char result[], int pos) {
	int i, j, k;
	j = 0;
	char aux[100];
	printf(result);
	printf("\n\n------------");

	for (i = 0; i < pos; i++) {
		aux[j] = result[i];
		j++;

		if (result[i] == ' ') {
			if (needValue(aux)) {
				for (k = i + 1; result[k] != ' '; k++, i++) {
					i++;
				}
			}

			result[i] = '\n';
			j = 0;
			aux[0] = '\0';
		}
	}

	FILE *outputFile;
	outputFile = fopen("output.txt", "w+");
	/*fprint(file, "")*/
	printf(result);
	fprintf(outputFile, result);
	fclose(outputFile);
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
		sprintf(res, "%d", token.name);
		strcat(result, res);
		strcat(result, " ");
		strcpy(res, "");

		if (token.value == NULL) {
			strcat(result, token.value);
			strcat(result, " ");
		}

		if (token.name == ERROR) {
			printf("ERRO LEXICO\n");
			printf("%s\n", result);
			break;
		}
	}

	writeFile(result, strlen(result));

	return 0;
}
