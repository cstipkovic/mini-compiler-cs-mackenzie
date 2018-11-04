/*
 * Allan Gustavo Fernandes         - 31568211
 * Clauber Pereira Stipkovic Halic - 31243045
 * Fabio Shimada Pinto             - 31160344
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Global variables*/
char *lookahead;
char *token;

/* Constants codes */
#define IDENTIFIER       1000
#define BOOLEAN          1001
#define WHILE            1002
#define PROGRAM          1003
#define PRINT            1004
#define VOID             1005
#define IF               1006
#define INT              1007
#define TRUE_            1008
#define FALSE_           1009
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

/*
 * non-terminal functions
 */
/* Syntax */
void nonPROGRAMA();
void nonBLOCO();
void nonPARTE_DECLARACOE_VARIAVEIS();
void nonPARTE_DECLARACOE_FUNCOES();
void nonCOMANDO_COMPOSTO();
/* Defintions */
void nonDECLARACAO_VARIAVEIS();
void nonDECLARACAO_FUNCOES();
void nonTIPO();
void nonLISTA_IDENTIFICADORES();
void nonIDENTIFICADOR();
void nonPARAMETROS_FORMAIS();
void nonPARAMETRO_FORMAL();
/* Commands */
void nonCOMANDO_COMPOSTO();
void nonCOMANDO();
void nonATRIBUICAO();
void nonCHAMADA_PROCEDIMENTO();
void nonCOMANDO_CONDICIONAL();
void nonCOMANDO_REPETITIVO();
void nonEXPRESSAO();
void nonLISTA_PARAMETROS();
void nonINT();
void nonBOL();
/* Expressions */
void nonEXPRESSAO_SIMPLES();
void nonRELACAO();
void nonTERMO();
void nonFATOR();

/*
 * Validation functions
 */

int isRELACAO();
int isBOL();
int isIDENTIFICADOR();
/*
 * int isINT();          -> using function isNumber to validate it.
 * int isDIGITO(char n); -> using function isNumber to validate it.
 * int isLETRA(char c);  -> using function isLetter to validate it.
 */

/*
 * Extra functions to help at validations
 */
int isNumber(char n);
int isLetter(char c);
void next();

/*
 * Function implementation
 */

void next();

/*
 * Function implementation
 */

void nonPROGRAMA(){

    /* ADICIONAR FUNCAO PARA PEGAR O PRIMEIRO TOKEN */

    if (token == PROGRAM) {
        next();
        if (token == IDENTIFIER) {
            next();
            if (token == BRACEOPEN) {
                next();
                nonBLOCO();
            } else {
                printf("ERROR: doesn't found block declaration");
            }
        } else {
            printf("ERROR: after PROGRAM declaration an identifier is not defined");
        }
    } else {
        printf("ERROR: invalid PROGRAM begin declaration");
    }
}

void nonBLOCO() {
    nonPARTE_DECLARACOE_VARIAVEIS();
    nonPARTE_DECLARACOE_FUNCOES();
    nonCOMANDO_COMPOSTO();
}

void nonPARTE_DECLARACOE_VARIAVEIS() {
    nonDECLARACAO_VARIAVEIS();
}

void nonPARTE_DECLARACOE_FUNCOES() {
    nonDECLARACAO_FUNCOES();
}

void nonCOMANDO_COMPOSTO() {
    nonCOMANDO();
}

void nonDECLARACAO_VARIAVEIS() {
    if (token == INT || token == BOOLEAN) {
        nonTIPO();
        nonLISTA_IDENTIFICADORES();
    }
}

void nonDECLARACAO_FUNCOES() {
    if (token == VOID {
        next();
        nonIDENTIFICADOR();
        if (token == PARENTHESISOPEN) {
            next();
            nonPARAMETROS_FORMAIS();
            if (token == PARENTHESISCLOSE) {
                next();
                if (token = BRACEOPEN) {
                    next();
                    nonBLOCO();
                } else {
                    printf("ERROR: expected { to open a function block");
                }
            } else { printf("ERROR: expected ) to paramenters function");
            }
        } else {
            printf("ERROR: expected { to open a function block ");
        }
    } else {
        printf("ERROR: expected { to open a function block");
    } else {
        printf("ERROR: expected VOID to function definition");
    }
}

void nonTIPO() {
    if (token == INT || token == BOOLEAN) {
        next();
    } else {
        printf("ERROR: type isn't defined {INT | BOOLEAN}");
    }
}

void nonLISTA_IDENTIFICADORES() {
    nonIDENTIFICADOR();
}

void nonIDENTIFICADOR() {
    /*
     * ADICIONAR IDENTIFICADOR EM UM ARRAY E CONTRORLAR O ESCOPO, PARA IMPRESSAO
     */
    if (token == IDENTIFIER) {
        next();
    } else {
        printf("ERROR: invalid IDENTIFIER");
    }
}

void nonPARAMETROS_FORMAIS() {
    nonPARAMETRO_FORMAL();
}

void nonPARAMETRO_FORMAL() {
    if (token == INT || token == BOOLEAN) {
        next();
        nonIDENTIFICADOR();
    }
}

void nonCOMANDO_COMPOSTO() {
    nonCOMANDO();
}

void nonCOMANDO() {
    nonATRIBUICAO();
    nonCHAMADA_PROCEDIMENTO();
    nonCOMANDO_CONDICIONAL();
    nonCOMANDO_REPETITIVO();
    if (token == PRINT) {
        next();
        /*
         * CRIAR FUNCAO PRA IMPRIMIR TABELA DE ESCOPO
         */
    }
}

void nonATRIBUICAO() {
    if (token  == ASSIGNMENT) {
        /*
         * VER COMO ISSO FAZER
         */
    }

}

void nonCHAMADA_PROCEDIMENTO() {
    nonIDENTIFICADOR();
    nonLISTA_PARAMETROS();

}

void nonCOMANDO_CONDICIONAL() {
    if (token == IF) {
        next();
        nonEXPRESSAO();
        nonCOMANDO_COMPOSTO();
        if (token == BRACEOPEN) {
            if (token ==  ELSE) {
                next();
                nonCOMANDO_COMPOSTO();
            }
        } else {
            printf("ERROR: expected { to open a function block");
        }
    }
}

void nonCOMANDO_REPETITIVO() {
    if (token == WHILE) {
        next();
        nonEXPRESSAO();
        if (token == BRACEOPEN) {
            next();
            nonCOMANDO_COMPOSTO();
        } else {
            printf("ERROR: expected { to open a function block");
        }
    }
}

void nonEXPRESSAO() {
    nonEXPRESSAO_SIMPLES();
}

void nonLISTA_PARAMETROS() {
    if (token == IDENTIFIER || token == POSITIVENUMBER || token == NEGATIVENUMBER || token == BOOLEAN) {
        next();
        nonIDENTIFICADOR();
        nonINT();
        nonBOL();
    }
}

void nonINT() {
    if (token == POSITIVENUMBER || token == NEGATIVENUMBER) {
        next();
    } else {
        printf("ERROR: was expected INT");
    }
}

void nonBOL() {
    if (token == BOOLEAN) {
        next();
    } else {
        printf("ERROR: was expected BOOLEAN");
    }
}

void nonEXPRESSAO_SIMPLES() {
    if (token == SUM || token == SUBTRACTION) {
        next();
        nonTERMO();
        nonRELACAO();
    } else {
        printf("ERROR: invalid expression");
    }
}

void nonRELACAO() {
    if (token == EQUALS || token == LESSEQUAL || token == GREATEREQUAL || token == DIFF || token == LESSTHAN || token == GREATERTHAN) {
        next();
    } else {
        printf("ERROR: invalid expression");
    }
}

void nonTERMO() {
    if (token == MULTIPLICATION ||token == DIVISION) {
        next();
        nonFATOR();
    } else {
        printf("ERROR: invalid expression");
    }

}

void nonFATOR() {
    if (token == IDENTIFIER || token == NEGATIVENUMBER || token == POSITIVENUMBER || token == BOOLEAN) {
        next();
        nonEXPRESSAO_SIMPLES();
    }
}

/* Struct do token */
typedef struct token {
	int name;
	char* value;
} TOKEN;


int isRELACAO() {
	return  0;
}

int isBOL() {
	return 0;
}

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
void readFile(char text[], char filename[]) {
	FILE *inputFile;
	inputFile = fopen(filename, "r");
	char line[400];

	if (inputFile) {
		while (fscanf(inputFile, "%s ", line) != EOF) {
			strcat(line, " ");
			strcat(text, line);
		}
		fclose(inputFile);
	}
}

/* Escreve os resultados no arquivo de saida */
void writeFile(char result[], int pos, char filename[]) {
	int i, j, k;
	j = 0;
	char aux[100];

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
	outputFile = fopen(filename, "w+");
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
	else if (text[*pos] == 't') goto q36;
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
	token.name = TRUE_;
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
	token.name = FALSE_;
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
}

/*
void next() {
   char res[100];
   int len;
   TOKEN token;
   getToken(&token);
   sprintf(res, "%d", token.name);
   len = strlen(res);

   lookahead = (char *) malloc(len * sizeof(char));
   strcpy(lookahead, res);

	// se houver comentario descarta e vai para a proxima entrada
	if (strcmp(lookahead, COMMENTS) == 0) {
		match();
	}
}
*/

void syntax() {
	printf("Syntax\n");
}

int main(int argc, char *argv[]) {
	int pos = 0;
	int inputSize = 800;
	int i;
	char inputFile[inputSize];
	char found[inputSize];

	for (i = 0; i < inputSize; i++) {
		inputFile[i] = '\0';
	}

	readFile(inputFile, "test-algC.txt");
	char result[inputSize];
	strcpy(result, "");

	char res[inputSize];

	while (pos < strlen(inputFile)) {
		TOKEN token = scanner(inputFile, &pos);
		sprintf(res, "%d", token.name);
		strcat(result, res);
		strcat(result, "\n");
		strcpy(res, "");

		if (token.name == ERROR) {
			printf("ERRO LEXICO\n");
			printf("%s\n", result);
			break;
		}
	}

	writeFile(result, strlen(result), "lexical_analysis.txt");

	syntax();

	return 0;
}
