#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Códigos das Constantes */
#define IDENTIFICADOR    1000
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

int isLetter(char c) {
    int a = (int) c;
    if ((a > 96 && a < 123) || (a > 64 && a < 91)) {
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

q0:(*pos)++;
	if(inputFile[*pos] == '_')         goto q1;
	else if(inputFile[*pos] == 'b')    goto q2;
	else if(inputFile[*pos] == 'w')    goto q7;
    else if(inputFile[*pos] == 'p')    goto q13;
    else if(inputFile[*pos] == 'v')    goto q25;
    else if(inputFile[*pos] == 'i')    goto q30;
    else if(inputFile[*pos] == 'q')    goto q36;
    else if(inputFile[*pos] == 'f')    goto q41;
    else if(inputFile[*pos] == 'e')    goto q47;
    else if(isNumber(inputFile[*pos])) goto q52;
    else if(inputFile[*pos] == '-')    goto q54;
    else if(inputFile[*pos] == '+')    goto q58;
    else if(inputFile[*pos] == '*')    goto q60;
    else if(inputFile[*pos] == '/')    goto q62;
    else if(inputFile[*pos] == '<')    goto q64;
    else if(inputFile[*pos] == '>')    goto q70;
    else if(inputFile[*pos] == '=')    goto q74;
    else if(inputFile[*pos] == '!')    goto q78;
    else if(inputFile[*pos] == '(')    goto q81;
    else if(inputFile[*pos] == ')')    goto q83;
    else if(inputFile[*pos] == ',')    goto q85;
    else if(inputFile[*pos] == ';')    goto q87;
    else if(inputFile[*pos] == '{')    goto q89;
    else if(inputFile[*pos] == '}')    goto q91;
	else return token;

q1:(*pos)++;
    if(isLetter(inputFile[*pos])) goto q68;
	else return token;

q2:(*pos)++;
    if(inputFile[*pos] == 'o') goto q3;
	else return token;

q3:(*pos)++;
    if(inputFile[*pos] == 'o') goto q4;
	else return token;

q4:(*pos)++;
    if(inputFile[*pos] == 'l') goto q5;
	else return token;

q5:(*pos)++;
    if(inputFile[*pos] == ' ') goto q6;
	else return token;

q6:(*pos)++;
    token.name = BOOLEAN;
    else return token;

q7:(*pos)++;
    if(inputFile[*pos] == 'h') goto q8;
    else return token;

q8:(*pos)++;
    if(inputFile[*pos] == 'i') goto q9;
	else return token;

q9:(*pos)++;
    if(inputFile[*pos] == 'l') goto q10;
	else return token;

q10:(*pos)++;
    if(inputFile[*pos] == 'e') goto q11;
	else return token;

q11:(*pos)++;
    if(inputFile[*pos] == ' ') goto q12;
	else return token;

q12:(*pos)++;
    token.name = WHILE;
	else return token;

q13:(*pos)++;
    if(inputFile[*pos] == 'r') goto q14;
	else return token;

q14:(*pos)++;
    if(inputFile[*pos] == 'o')      goto q15;
    else if(inputFile[*pos] == 'i') goto q21;
	else return token;

q15:(*pos)++;
    if(inputFile[*pos] == 'g') goto q16;
	else return token;

q16:(*pos)++;
    if(inputFile[*pos] == 'r') goto q17;
	else return token;

q17:(*pos)++;
    if(inputFile[*pos] == 'a') goto q18;
	else return token;

q18:(*pos)++;
    if(inputFile[*pos] == 'm') goto q19;
	else return token;

q19:(*pos)++;
    if(inputFile[*pos] == ' ') goto q20;
	else return token;

q20:(*pos)++;
	token.name = PROGRAM;
	else return token;

q21:(*pos)++;
    if(inputFile[*pos] == 'n') goto q22;
	else return token;

q22:(*pos)++;
    if(inputFile[*pos] == 't') goto q23;
	else return token;

q23:(*pos)++;
    if(inputFile[*pos] == ' ') goto q24;
	else return token;

q24:(*pos)++;
	token.name = PRINT;
	else return token;

q25:(*pos)++;
    if(inputFile[*pos] == 'o') goto q26;
	else return token;

q26:(*pos)++;
    if(inputFile[*pos] == 'i') goto q27;
	else return token;

q27:(*pos)++;
    if(inputFile[*pos] == 'd') goto q28;
	else return token;

q28:(*pos)++;
    if(inputFile[*pos] == ' ') goto q29;
	else return token;

q29:(*pos)++;
	token.name = VOID;
	else return token;

q30:(*pos)++;
    if(inputFile[*pos] == 'f')      goto q31;
    else if(inputFile[*pos] == 'n') goto q32;
	else return token;

q31:(*pos)++;
	if(inputFile[*pos] == ' ') goto q34;
	else return token;

q32:(*pos)++;
    if(inputFile[*pos] == 't') goto q33;
	else return token;

q33:(*pos)++;
    if(inputFile[*pos] == ' ') goto q35;
	else return token;

q34:(*pos)++;
	token.name = IF;
	else return token;

q35:(*pos)++;
	token.name = INT;
	else return token;

q36:(*pos)++;
    if(inputFile[*pos] == 'r') goto q37;
	else return token;

q37:(*pos)++;
    if(inputFile[*pos] == 'u') goto q38;
	else return token;

q38:(*pos)++;
    if(inputFile[*pos] == 'e') goto q39;
	else return token;

q39:(*pos)++;
    if(inputFile[*pos] == ' ') goto q40;
	else return token;

q40:(*pos)++;
	token.name = TRUE;
	else return token;

q41:(*pos)++;
    if(inputFile[*pos] == 'a') goto q42;
	else return token;

q42:(*pos)++;
    if(inputFile[*pos] == 'l') goto q43;
	else return token;

q43:(*pos)++;
    if(inputFile[*pos] == 's') goto q44;
	else return token;

q44:(*pos)++;
    if(inputFile[*pos] == 'e') goto q45;
	else return token;

q45:(*pos)++;
    if(inputFile[*pos] == ' ') goto q46;
	else return token;

q46:(*pos)++;
	token.name = FALSE;
	else return token;

q47:(*pos)++;
    if(inputFile[*pos] == 'l') goto q48;
	else return token;

q48:(*pos)++;
    if(inputFile[*pos] == 's') goto q49;
	else return token;

q49:(*pos)++;
    if(inputFile[*pos] == 'e') goto q50;
	else return token;

q50:(*pos)++;
    if(inputFile[*pos] == ' ') goto q51;
	else return token;

q51:(*pos)++;
	token.name = ELSE;
	else return token;

q52:(*pos)++;
    if(isNumber(inputFile[*pos]))   goto q52;
    else if(inputFile[*pos] == ' ') goto q53;
	else return token;

q53:(*pos)++;
	token.name = POSITIVENUMBER;
	else return token;

q54:(*pos)++;
    if(isNumber(inputFile[*pos]))   goto q55;
    else if(inputFile[*pos] == ' ') goto q57;
	else return token;

q55:(*pos)++;
    if(isNumber(inputFile[*pos]))   goto q55;
    else if(inputFile[*pos] == ' ') goto q56;
	else return token;

q56:(*pos)++;
	token.name = NEGATIVENUMBER;
	else return token;

q57:(*pos)++;
    token.name = SUBTRACTION;
	else return token;

q58:(*pos)++;
    if(inputFile[*pos] == ' ') goto q59;
	else return token;

q59:(*pos)++;
	token.name = SUM;
	else return token;

q60:(*pos)++;
    if(inputFile[*pos] == ' ') goto q61;
	else return token;

q61:(*pos)++;
	token.name = MULTIPLICATION;
	else return token;

q62:(*pos)++;
    if(inputFile[*pos] == ' ')      goto q63;
    else if(inputFile[*pos] == '*') goto q93;
	else return token;

q63:(*pos)++;
	token.name = DIVISION;
	else return token;

q64:(*pos)++;
    if(inputFile[*pos] == ' ')      goto q65;
    else if(inputFile[*pos] == '=') goto q66;
	else return token;

q65:(*pos)++;
	token.name = LESSTHAN;
	else return token;

q66:(*pos)++;
    if(inputFile[*pos] == ' ') goto q67;
	else return token;

q67:(*pos)++;
	token.nane = LESSEQUAL;
	else return token;

q68:(*pos)++;
    if(isLetter(inputFile[*pos]))   goto q68;
    else if(inputFile[*pos] == ' ') goto q69;
	else return token;

q69:(*pos)++;
	token.name = IDENTIFICADOR;
	else return token;

q70:(*pos)++;
    if(inputFile[*pos] == ' ')      goto q71;
    else if(inputFile[*pos] == '=') goto q72;
	else return token;

q71:(*pos)++;
	token.name = GREATERTHAN;
	else return token;

q72:(*pos)++;
    if(inputFile[*pos] == ' ') goto q73;
    else return token;

q73:(*pos)++;
    token.name = GREATEREQUAL;
	else return token;

q74:(*pos)++;
    if(inputFile[*pos] == ' ') goto q75;
	else return token;

q75:(*pos)++;
	token.name = ASSIGNMENT;
	else return token;

q76:(*pos)++;
    if(inputFile[*pos] == '=') goto q77;
	else return token;

q77:(*pos)++;
	token.name = EQUALS;
	else return token;

q78:(*pos)++;
    if(inputFile[*pos] == '=') goto q79;
	else return token;

q79:(*pos)++;
    if(inputFile[*pos] == ' ') goto q80;
	else return token;

q80:(*pos)++;
    token.name = DIFF;
	else return token;

q81:(*pos)++;
    if(inputFile[*pos] == ' ') goto q82;
	else return token;

q82:(*pos)++;
	token.name = PARENTHESISOPEN;
	else return token;

q83:(*pos)++;
    if(inputFile[*pos] == ' ') goto q84;
	else return token;

q84:(*pos)++;
    token.name = PARENTHESISCLOSE;
	else return token;

q85:(*pos)++;
    if(inputFile[*pos] == ' ') goto q86;
	else return token;

q86:(*pos)++;
	token.name = COMMA;
	else return token;

q87:(*pos)++;
    if(inputFile[*pos] == ' ') goto q88;
	else return token;

q88:(*pos)++;
	token.name = SEMICOLON;
	else return token;

q89:(*pos)++;
    if(inputFile[*pos] == ' ') goto q90;
	else return token;

q90:(*pos)++;
	token.name = BRACEOPEN;
	else return token;

q91:(*pos)++;
    if(inputFile[*pos] == ' ') goto q92;
	else return token;

q92:(*pos)++;
    token.name = BRACECLOSE;
	else return token;

q93:(*pos)++;
    if(inputFile[*pos] != '*') goto q94;
	else return token;

q94:(*pos)++;
    if(inputFile[*pos] == '*') goto q95;
	else return token;

q95:(*pos)++;
    if(inputFile[*pos] == '/') goto q96;
	else return token;

q96:(*pos)++;
    if(inputFile[*pos] == ' ') goto q97;
	else return token;

q97:(*pos)++;
    token.name = COMMENTS;
	else return token;

#
# q98:(*pos)++;
#	else return token;
#
# q99:(*pos)++;
#	else return token;
#
# q100:(*pos)++;
#	else return token;
#
# q101:(*pos)++;
# 	else return token;
