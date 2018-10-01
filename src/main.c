/*
 * Allan Gustavo Fernandes         - 31568211
 * Clauber Pereira Stipkovic Halic - 31243045
 * Fabio Shimada Pinto             - 31160344
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Códigos das Constantes */
#define IDENTIFIER       1000
#define BOOLEAN          1001
#define WHILE            1002
#define PROGRAM          1003
#define PRINT            1004
#define VOID             1005
#define IF               1006
#define INT              1007
#define TRUE             1008
#define FALSE            1009
#define ELSE             1010
#define COMMENTS         1011
#define DIVISION         1012
#define SUBTRACTION      1013
#define SUM              1014
#define MULTIPLICATION   1015
#define LESSTHAN         1016
#define LESSEQUAL        1017
#define GREATERTHAN      1018
#define GREATEREQUAL     1019
#define EQUALS           1020
#define DIFF             1021
#define COMMA            1022
#define SEMICOLON        1023
#define PARENTHESISOPEN  1024
#define PARENTHESISCLOSE 1025
#define BRACEOPEN        1026
#define BRACECLOSE       1027
#define POSITIVENUMBER   1028
#define NEGATIVENUMBER   1029
#define ASSIGNMENT       1030
#define ERROR            404

/* Struct do token */
typedef struct token {
	int name;
	char* value;
} TOKEN;

/* Verifica se entrada é um número - [0 - 9]*/
int isNumber(char n) {
	if (n == '0' || n == '1' || n == '2' || n == '3' || n == '4' || n == '5' || n == '6' || n == '7' || n == '8' || n == '9') {
		return 1;
	}

	return 0;
}
/* Verifica se entrada é uma letra de A-z */
int isLetter(char c) {
	int a = (int) c;
	if ((a > 96 && a < 123) || (a > 64 && a < 91)) {
		return 1;
	}

	return 0;
}

/* Funcao auxiliar para definir se é um valor positivo, negativo ou um identificador*/
int needValue(char aux[]) {
	int c;

	c = atoi(aux);

	if (c == POSITIVENUMBER || c == NEGATIVENUMBER || c == IDENTIFIER) {
		return 1;
	}

	return 0;
}

/* Lê o arquivo com o código proposto */
void readFile(char text[]) {
	FILE *inputFile;
	inputFile = fopen("test-algC.txt", "r");
	char line[1000];

	if (inputFile) {
		while (fscanf(inputFile, "%s ", line) != EOF) {
			strcat(line, " ");
			strcat(text, line);
		}
		fclose(inputFile);
	}
}

/* Escreve os resultados no arquivo de saida */
void writeFile(char result[], int pos) {
	int i, j, k;
	j = 0;
	char aux[100];
	printf("%s", result);
	printf("\n\n------------\n\n");

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
	fprintf(outputFile, "%s", result);
	fclose(outputFile);
}

char* getValue(char text[], int pos) {
	char *value;
	int i, j, count;

	count = 0;

	for (i = pos - 2; text[i] != ' ' && i >= 0; i--) {
		count++;
	}

	value = malloc(2 * count * sizeof(char));
	j = 0;

	for (i = pos - 2; text[i] != ' ' && i >= 0; i--) {
		value[j] = text[i - count + 1 + (2 * j)];
		j++;
	}

	printf("Value: %s\n", value);

	return value;
}

/* Retorna a saida da entrada segundo especificacao do automato*/
TOKEN scanner(char text[], int *pos) {
	TOKEN token;
	token.name = ERROR;
	token.value = NULL;

	(*pos)--;

q0:
	(*pos)++;
	if (text[*pos] == '_') goto q1;
	else if (text[*pos] == 'b') goto q2;
	else if (text[*pos] == 'w') goto q7;
	else if (text[*pos] == 'p') goto q13;
	else if (text[*pos] == 'v') goto q25;
	else if (text[*pos] == 'i') goto q30;
	else if (text[*pos] == 'q') goto q36;
	else if (text[*pos] == 'f') goto q41;
	else if (text[*pos] == 'e') goto q47;
	else if (isNumber(text[*pos])) goto q52;
	else if (text[*pos] == '-') goto q54;
	else if (text[*pos] == '+') goto q58;
	else if (text[*pos] == '*') goto q60;
	else if (text[*pos] == '/') goto q62;
	else if (text[*pos] == '<') goto q64;
	else if (text[*pos] == '>') goto q70;
	else if (text[*pos] == '=') goto q74;
	else if (text[*pos] == '!') goto q78;
	else if (text[*pos] == '(') goto q81;
	else if (text[*pos] == ')') goto q83;
	else if (text[*pos] == ',') goto q85;
	else if (text[*pos] == ';') goto q87;
	else if (text[*pos] == '{') goto q89;
	else if (text[*pos] == '}') goto q91;
	else return token;

q1:
	(*pos)++;
	if (isLetter(text[*pos])) goto q68;
	else return token;

q2:
	(*pos)++;
	if (text[*pos] == 'o') goto q3;
	else return token;

q3:
	(*pos)++;
	if (text[*pos] == 'o') goto q4;
	else return token;

q4:
	(*pos)++;
	if (text[*pos] == 'l') goto q5;
	else return token;

q5:
	(*pos)++;
	if (text[*pos] == ' ') goto q6;
	else return token;

q6:
	(*pos)++;
	token.name = BOOLEAN;
	return token;

q7:
	(*pos)++;
	if (text[*pos] == 'h') goto q8;
	else return token;

q8:
	(*pos)++;
	if (text[*pos] == 'i') goto q9;
	else return token;

q9:
	(*pos)++;
	if (text[*pos] == 'l') goto q10;
	else return token;

q10:
	(*pos)++;
	if (text[*pos] == 'e') goto q11;
	else return token;

q11:
	(*pos)++;
	if (text[*pos] == ' ') goto q12;
	else return token;

q12:
	(*pos)++;
	token.name = WHILE;
	return token;

q13:
	(*pos)++;
	if (text[*pos] == 'r') goto q14;
	else return token;

q14:
	(*pos)++;
	if (text[*pos] == 'o') goto q15;
	else if (text[*pos] == 'i') goto q21;
	else return token;

q15:
	(*pos)++;
	if (text[*pos] == 'g') goto q16;
	else return token;

q16:
	(*pos)++;
	if (text[*pos] == 'r') goto q17;
	else return token;

q17:
	(*pos)++;
	if (text[*pos] == 'a') goto q18;
	else return token;

q18:
	(*pos)++;
	if (text[*pos] == 'm') goto q19;
	else return token;

q19:
	(*pos)++;
	if (text[*pos] == ' ') goto q20;
	else return token;

q20:
	(*pos)++;
	token.name = PROGRAM;
	return token;

q21:
	(*pos)++;
	if (text[*pos] == 'n') goto q22;
	else return token;

q22:
	(*pos)++;
	if (text[*pos] == 't') goto q23;
	else return token;

q23:
	(*pos)++;
	if (text[*pos] == ' ') goto q24;
	else return token;

q24:
	(*pos)++;
	token.name = PRINT;
	return token;

q25:
	(*pos)++;
	if (text[*pos] == 'o') goto q26;
	else return token;

q26:
	(*pos)++;
	if (text[*pos] == 'i') goto q27;
	else return token;

q27:
	(*pos)++;
	if (text[*pos] == 'd') goto q28;
	else return token;

q28:
	(*pos)++;
	if (text[*pos] == ' ') goto q29;
	else return token;

q29:
	(*pos)++;
	token.name = VOID;
	return token;

q30:
	(*pos)++;
	if (text[*pos] == 'f') goto q31;
	else if (text[*pos] == 'n') goto q32;
	else return token;

q31:
	(*pos)++;
	if (text[*pos] == ' ') goto q34;
	else return token;

q32:
	(*pos)++;
	if (text[*pos] == 't') goto q33;
	else return token;

q33:
	(*pos)++;
	if (text[*pos] == ' ') goto q35;
	else return token;

q34:
	(*pos)++;
	token.name = IF;
	return token;

q35:
	(*pos)++;
	token.name = INT;
	return token;

q36:
	(*pos)++;
	if (text[*pos] == 'r') goto q37;
	else return token;

q37:
	(*pos)++;
	if (text[*pos] == 'u') goto q38;
	else return token;

q38:
	(*pos)++;
	if (text[*pos] == 'e') goto q39;
	else return token;

q39:
	(*pos)++;
	if (text[*pos] == ' ') goto q40;
	else return token;

q40:
	(*pos)++;
	token.name = TRUE;
	return token;

q41:
	(*pos)++;
	if (text[*pos] == 'a') goto q42;
	else return token;

q42:
	(*pos)++;
	if (text[*pos] == 'l') goto q43;
	else return token;

q43:
	(*pos)++;
	if (text[*pos] == 's') goto q44;
	else return token;

q44:
	(*pos)++;
	if (text[*pos] == 'e') goto q45;
	else return token;

q45:
	(*pos)++;
	if (text[*pos] == ' ') goto q46;
	else return token;

q46:
	(*pos)++;
	token.name = FALSE;
	return token;

q47:
	(*pos)++;
	if (text[*pos] == 'l') goto q48;
	else return token;

q48:
	(*pos)++;
	if (text[*pos] == 's') goto q49;
	else return token;

q49:
	(*pos)++;
	if (text[*pos] == 'e') goto q50;
	else return token;

q50:
	(*pos)++;
	if (text[*pos] == ' ') goto q51;
	else return token;

q51:
	(*pos)++;
	token.name = ELSE;
	return token;

q52:
	(*pos)++;
	if (isNumber(text[*pos])) goto q52;
	else if (text[*pos] == ' ') goto q53;
	else return token;

q53:
	(*pos)++;
	token.name = POSITIVENUMBER;
	return token;

q54:
	(*pos)++;
	if (isNumber(text[*pos])) goto q55;
	else if (text[*pos] == ' ') goto q57;
	else return token;

q55:
	(*pos)++;
	if (isNumber(text[*pos])) goto q55;
	else if (text[*pos] == ' ') goto q56;
	else return token;

q56:
	(*pos)++;
	token.name = NEGATIVENUMBER;
	return token;

q57:
	(*pos)++;
	token.name = SUBTRACTION;
	return token;

q58:
	(*pos)++;
	if (text[*pos] == ' ') goto q59;
	else return token;

q59:
	(*pos)++;
	token.name = SUM;
	return token;

q60:
	(*pos)++;
	if (text[*pos] == ' ') goto q61;
	else return token;

q61:
	(*pos)++;
	token.name = MULTIPLICATION;
	return token;

q62:
	(*pos)++;
	if (text[*pos] == ' ') goto q63;
	else if (text[*pos] == '*') goto q93;
	else return token;

q63:
	(*pos)++;
	token.name = DIVISION;
	return token;

q64:
	(*pos)++;
	if (text[*pos] == ' ') goto q65;
	else if (text[*pos] == '=') goto q66;
	else return token;

q65:
	(*pos)++;
	token.name = LESSTHAN;
	return token;

q66:
	(*pos)++;
	if (text[*pos] == ' ') goto q67;
	else return token;

q67:
	(*pos)++;
	token.name = LESSEQUAL;
	return token;

q68:
	(*pos)++;
	if (isLetter(text[*pos])) goto q68;
	else if (text[*pos] == ' ') goto q69;
	else if (text[*pos] == '=') goto q69;
	else return token;

q69:
	(*pos)++;
	token.name = IDENTIFIER;
	return token;

q70:
	(*pos)++;
	if (text[*pos] == ' ') goto q71;
	else if (text[*pos] == '=') goto q72;
	else return token;

q71:
	(*pos)++;
	token.name = GREATERTHAN;
	return token;

q72:
	(*pos)++;
	if (text[*pos] == ' ') goto q73;
	else return token;

q73:
	(*pos)++;
	token.name = GREATEREQUAL;
	return token;

q74:
	(*pos)++;
	if (text[*pos] == ' ') goto q75;
	else if (text[*pos] == '=') goto q76;
	else return token;

q75:
	(*pos)++;
	token.name = ASSIGNMENT;
	return token;

q76:
	(*pos)++;
	if (text[*pos] == '=') goto q77;
	else return token;

q77:
	(*pos)++;
	token.name = EQUALS;
	return token;

q78:
	(*pos)++;
	if (text[*pos] == '=') goto q79;
	else return token;

q79:
	(*pos)++;
	if (text[*pos] == ' ') goto q80;
	else return token;

q80:
	(*pos)++;
	token.name = DIFF;
	return token;

q81:
	(*pos)++;
	if (text[*pos] == ' ') goto q82;
	else return token;

q82:
	(*pos)++;
	token.name = PARENTHESISOPEN;
	return token;

q83:
	(*pos)++;
	if (text[*pos] == ' ') goto q84;
	else return token;

q84:
	(*pos)++;
	token.name = PARENTHESISCLOSE;
	return token;

q85:
	(*pos)++;
	if (text[*pos] == ' ') goto q86;
	else return token;

q86:
	(*pos)++;
	token.name = COMMA;
	return token;

q87:
	(*pos)++;
	if (text[*pos] == ' ') goto q88;
	else return token;

q88:
	(*pos)++;
	token.name = SEMICOLON;
	return token;

q89:
	(*pos)++;
	if (text[*pos] == ' ') goto q90;
	else return token;

q90:
	(*pos)++;
	token.name = BRACEOPEN;
	return token;

q91:
	(*pos)++;
	if (text[*pos] == ' ') goto q92;
	else return token;

q92:
	(*pos)++;
	token.name = BRACECLOSE;
	return token;

q93:
	(*pos)++;
	if (text[*pos] != '*') goto q94;
	else return token;

q94:
	(*pos)++;
	if (text[*pos] == '*') goto q95;
	else return token;

q95:
	(*pos)++;
	if (text[*pos] == '/') goto q96;
	else return token;

q96:
	(*pos)++;
	if (text[*pos] == ' ') goto q97;
	else return token;

q97:
	(*pos)++;
	token.name = COMMENTS;
	return token;

	/*
q98:(*pos)++;
else return token;

q99:(*pos)++;
else return token;

q100:(*pos)++;
else return token;

q101:(*pos)++;
else return token;
*/

}

int main(int argc, char *argv[]) {
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
