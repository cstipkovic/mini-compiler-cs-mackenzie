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


q0:(*pos)++;
	else return token;

q1:(*pos)++;
	else return token;

q2:(*pos)++;
	else return token;

q3:(*pos)++;
	else return token;

q4:(*pos)++;
	else return token;

q5:(*pos)++;
	else return token;

q6:(*pos)++;
	else return token;

q7:(*pos)++;
	else return token;

q8:(*pos)++;
	else return token;

q9:(*pos)++;
	else return token;

q10:(*pos)++;
	else return token;

q11:(*pos)++;
	else return token;

q12:(*pos)++;
	else return token;

q13:(*pos)++;
	else return token;

q14:(*pos)++;
	else return token;

q15:(*pos)++;
	else return token;

q16:(*pos)++;
	else return token;

q17:(*pos)++;
	else return token;

q18:(*pos)++;
	else return token;

q19:(*pos)++;
	else return token;

q20:(*pos)++;
	else return token;

q21:(*pos)++;
	else return token;

q22:(*pos)++;
	else return token;

q23:(*pos)++;
	else return token;

q24:(*pos)++;
	else return token;

q25:(*pos)++;
	else return token;

q26:(*pos)++;
	else return token;

q27:(*pos)++;
	else return token;

q28:(*pos)++;
	else return token;

q29:(*pos)++;
	else return token;

q30:(*pos)++;
	else return token;

q31:(*pos)++;
	else return token;

q32:(*pos)++;
	else return token;

q33:(*pos)++;
	else return token;

q34:(*pos)++;
	else return token;

q35:(*pos)++;
	else return token;

q36:(*pos)++;
	else return token;

q37:(*pos)++;
	else return token;

q38:(*pos)++;
	else return token;

q39:(*pos)++;
	else return token;

q40:(*pos)++;
	else return token;

q41:(*pos)++;
	else return token;

q42:(*pos)++;
	else return token;

q43:(*pos)++;
	else return token;

q44:(*pos)++;
	else return token;

q45:(*pos)++;
	else return token;

q46:(*pos)++;
	else return token;

q47:(*pos)++;
	else return token;

q48:(*pos)++;
	else return token;

q49:(*pos)++;
	else return token;

q50:(*pos)++;
	else return token;

q51:(*pos)++;
	else return token;

q52:(*pos)++;
	else return token;

q53:(*pos)++;
	else return token;

q54:(*pos)++;
	else return token;

q55:(*pos)++;
	else return token;

q56:(*pos)++;
	else return token;

q57:(*pos)++;
	else return token;

q58:(*pos)++;
	else return token;

q59:(*pos)++;
	else return token;

q60:(*pos)++;
	else return token;

q61:(*pos)++;
	else return token;

q62:(*pos)++;
	else return token;

q63:(*pos)++;
	else return token;

q64:(*pos)++;
	else return token;

q65:(*pos)++;
	else return token;

q66:(*pos)++;
	else return token;

q67:(*pos)++;
	else return token;

q68:(*pos)++;
	else return token;

q69:(*pos)++;
	else return token;

q70:(*pos)++;
	else return token;

q71:(*pos)++;
	else return token;

q72:(*pos)++;
	else return token;

q73:(*pos)++;
	else return token;

q74:(*pos)++;
	else return token;

q75:(*pos)++;
	else return token;

q76:(*pos)++;
	else return token;

q77:(*pos)++;
	else return token;

q78:(*pos)++;
	else return token;

q79:(*pos)++;
	else return token;

q80:(*pos)++;
	else return token;

q81:(*pos)++;
	else return token;

q82:(*pos)++;
	else return token;

q83:(*pos)++;
	else return token;

q84:(*pos)++;
	else return token;

q85:(*pos)++;
	else return token;

q86:(*pos)++;
	else return token;

q87:(*pos)++;
	else return token;

q88:(*pos)++;
	else return token;

q89:(*pos)++;
	else return token;

q90:(*pos)++;
	else return token;

q91:(*pos)++;
	else return token;

q92:(*pos)++;
	else return token;

q93:(*pos)++;
	else return token;

q94:(*pos)++;
	else return token;

q95:(*pos)++;
	else return token;

q96:(*pos)++;
	else return token;

q97:(*pos)++;
	else return token;

q98:(*pos)++;
	else return token;

q99:(*pos)++;
	else return token;

q100:(*pos)++;
	else return token;

q101:(*pos)++;
	else return token;



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
