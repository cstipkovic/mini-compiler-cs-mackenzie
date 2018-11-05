#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __PROGRAMA__  100
#define __FIMPROGRAMA__ 101
#define __PROCEDIMENTO__ 102
#define __FIMPROCEDIMENTO__ 103
#define __SE__ 104
#define __FIMSE__ 105
#define __ENQUANTO__ 106
#define __FIMENQUANTO__ 107
#define __ENTAO__  108
#define __FIMENTAO__ 109
#define __SENAO__ 110
#define __FIMSENAO__ 111
#define __BOOLEANO__ 112
#define __FACA__ 113
#define __FALSO__ 114
#define __ESCREVA__ 115

#define __INTEIRO__ 200
#define __VERDADEIRO__ 201
#define __NUMERO_POSITIVO__ 202
#define __NUMERO_NEGATIVO__ 203

#define __OPERADOR_SUBTRACAO__ 300
#define __OPERADOR_ADICAO__ 301
#define __OPERADOR_DIVISAO__ 302
#define __OPERADOR_MULTIPLICACAO__ 303
#define __OPERADOR_MAIOR__ 304
#define __OPERADOR_MAIOR_IGUAL__ 305
#define __OPERADOR_MENOR_IGUAL__ 306
#define __OPERADOR_MENOR__ 307
#define __OPERADOR_DIFERENCIACAO__ 308
#define __OPERADOR_COMPARACAO__ 309
#define __OPERADOR_ATRIBUICAO__ 310

#define __DELIMITADOR_PA_ABERTO__ 400
#define __DELIMITADOR_PA_FECHADO__ 401
#define __DELIMITADOR_VIRGULA__ 402
#define __DELIMITADOR_DOIS_PONTOS__ 403
#define __DELIMITADOR_PONTO_VIRGULA__ 404

#define __COMENTARIO__ 500

#define __IDENTIFICADOR__ 600

#define __ERRO__ 700



typedef struct token {
    int nome;
    char* valor;
}TOKEN;

void readFile(char txt[]);
void writeFile(char result[], int pos);
int needValue(char aux[]);
int isNumber(char c);
int isLetter(char c);

char* getValue(char txt[],int pos);
TOKEN scanner(char txt[], int *pos);

int main(int argc, char *argv[]) {
    int pos, i, tamanho;
    
    tamanho = 800;
    pos = 0;
    char txt[tamanho];
    char found[tamanho];
    
    /* Inicializar o vetor. */
    for(i = 0; i < tamanho; i++) {
        txt[i] = '\0';
    }
    
    
    readFile(txt);
    char result[tamanho];
    strcpy(result, "");
    
    char res[tamanho];
	
    while (pos < strlen(txt)) {
        
        TOKEN token = scanner(txt, &pos);
        sprintf(res, "%d", token.nome);
        strcat(result, res);
        strcat(result, " ");
        strcpy(res, "");

        if ( token.valor != NULL ) {
            strcat(result, token.valor);
            strcat(result, " ");
        }
        
        if (token.nome == __ERRO__ ) {
            printf("ERRO LEXICO\n");
            printf("%s\n",result);
            break;
        }

    }
    
    writeFile(result, strlen(result));
    
    return 0;
}

TOKEN scanner(char txt[], int *pos) {
    
    TOKEN token;
    token.nome = __ERRO__;
    token.valor = NULL;
    
    (*pos)--;
q0:(*pos)++;
    if(txt[*pos] == 'b') goto q1;
    else if(txt[*pos] == 'e') goto q10;
    else if(txt[*pos] == 'f') goto q30;
    else if(txt[*pos] == 'i') goto q72;
    else if(txt[*pos] == 'p') goto q80;
    else if(txt[*pos] == 's') goto q99;
    else if(txt[*pos] == 'v') goto q106;
    else if(isNumber(txt[*pos])) goto q117;
    else if(txt[*pos] == '-') goto q119;
    else if(txt[*pos] == '+') goto q123;
    else if(txt[*pos] == 'd') goto q125;
    else if(txt[*pos] == 'm') goto q129;
    else if(txt[*pos] == '>') goto q133;
    else if(txt[*pos] == '<') goto q137;
    else if(txt[*pos] == '=') goto q143;
    else if(txt[*pos] == '(') goto q147;
    else if(txt[*pos] == ')') goto q149;
    else if(txt[*pos] == ',') goto q151;
    else if(txt[*pos] == ':') goto q153;
    else if(txt[*pos] == ';') goto q155;
    else if(txt[*pos] == '/') goto q157;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q1:(*pos)++;
    if(txt[*pos] == 'o') goto q2;
    else if( isLetter(txt[*pos]) ) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q2:(*pos)++;
    if(txt[*pos] == 'o') goto q3;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q3:(*pos)++;
    if(txt[*pos] == 'l') goto q4;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q4:(*pos)++;
    if(txt[*pos] == 'e') goto q5;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q5:(*pos)++;
    if(txt[*pos] == 'a') goto q6;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q6:(*pos)++;
    if(txt[*pos] == 'n') goto q7;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q7:(*pos)++;
    if(txt[*pos] == 'o') goto q8;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q8:(*pos)++;
    if(txt[*pos] == ' ') goto q9;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q9:(*pos)++;
    token.nome = __BOOLEANO__;
    return token;
q10:(*pos)++;
    if(txt[*pos] == 'n') goto q11;
    else if(txt[*pos] == 's') goto q23;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q11:(*pos)++;
    if(txt[*pos] == 'q') goto q12;
    else if(txt[*pos] == 't') goto q19;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    
    else return token;
q12:(*pos)++;
    if(txt[*pos] == 'u') goto q13;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    
    else return token;
q13:(*pos)++;
    if(txt[*pos] == 'a') goto q14;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    
    else return token;
q14:(*pos)++;
    if(txt[*pos] == 'n') goto q15;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    
    else return token;
q15:(*pos)++;
    if(txt[*pos] == 't') goto q16;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    
    else return token;
q16:(*pos)++;
    if(txt[*pos] == 'o') goto q17;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    
    else return token;
q17:(*pos)++;
    if(txt[*pos] == ' ') goto q18;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q18:(*pos)++;
    token.nome = __ENQUANTO__;
    return token;
q19:(*pos)++;
    if(txt[*pos] == 'a') goto q20;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q20:(*pos)++;
    if(txt[*pos] == 'o') goto q21;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q21:(*pos)++;
    if(txt[*pos] == ' ') goto q22;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q22:(*pos)++;
    token.nome = __ENTAO__;
    return token;
q23:(*pos)++;
    if(txt[*pos] == 'c') goto q24;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q24:(*pos)++;
    if(txt[*pos] == 'r') goto q25;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q25:(*pos)++;
    if(txt[*pos] == 'e') goto q26;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q26:(*pos)++;
    if(txt[*pos] == 'v') goto q27;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q27:(*pos)++;
    if(txt[*pos] == 'a') goto q28;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q28:(*pos)++;
    if(txt[*pos] == ' ') goto q29;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q29:(*pos)++;
    token.nome = __ESCREVA__;
    return token;
q30:(*pos)++;
    if(txt[*pos] == 'a') goto q31;
    else if(txt[*pos] == 'i') goto q39;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q31:(*pos)++;
    if(txt[*pos] == 'c') goto q32;
    else if(txt[*pos] == 'l') goto q35;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q32:(*pos)++;
    if(txt[*pos] == 'a') goto q33;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q33:(*pos)++;
    if(txt[*pos] == ' ') goto q34;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q34:(*pos)++;
    token.nome = __FACA__;
    return token;
q35:(*pos)++;
    if(txt[*pos] == 's') goto q36;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q36:(*pos)++;
    if(txt[*pos] == 'o') goto q37;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q37:(*pos)++;
    if(txt[*pos] == ' ') goto q38;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q38:(*pos)++;
    token.nome = __FALSO__;
    return token;
q39:(*pos)++;
    if(txt[*pos] == 'm') goto q40;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q40:(*pos)++;
    if(txt[*pos] == 'e') goto q41;
    else if(txt[*pos] == 'p') goto q50;
    else if(txt[*pos] == 's') goto q69;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q41:(*pos)++;
    if(txt[*pos] == 'n') goto q42;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q42:(*pos)++;
    if(txt[*pos] == 'q') goto q43;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q43:(*pos)++;
    if(txt[*pos] == 'u') goto q44;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q44:(*pos)++;
    if(txt[*pos] == 'a') goto q45;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q45:(*pos)++;
    if(txt[*pos] == 'n') goto q46;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q46:(*pos)++;
    if(txt[*pos] == 't') goto q47;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q47:(*pos)++;
    if(txt[*pos] == 'o') goto q48;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q48:(*pos)++;
    if(txt[*pos] == ' ') goto q49;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q49:(*pos)++;
    token.nome = __FIMENQUANTO__;
    return token;
q50:(*pos)++;
    if(txt[*pos] == 'r') goto q51;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q51:(*pos)++;
    if(txt[*pos] == 'o') goto q52;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q52:(*pos)++;
    if(txt[*pos] == 'c') goto q53;
    else if(txt[*pos] == 'g') goto q63;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q53:(*pos)++;
    if(txt[*pos] == 'e') goto q54;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q54:(*pos)++;
    if(txt[*pos] == 'd') goto q55;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q55:(*pos)++;
    if(txt[*pos] == 'i') goto q56;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q56:(*pos)++;
    if(txt[*pos] == 'm') goto q57;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q57:(*pos)++;
    if(txt[*pos] == 'e') goto q58;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q58:(*pos)++;
    if(txt[*pos] == 'n') goto q59;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q59:(*pos)++;
    if(txt[*pos] == 't') goto q60;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q60:(*pos)++;
    if(txt[*pos] == 'o') goto q61;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q61:(*pos)++;
    if(txt[*pos] == ' ') goto q62;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q62:(*pos)++;
    token.nome = __FIMPROCEDIMENTO__;
    return token;
q63:(*pos)++;
    if(txt[*pos] == 'r') goto q64;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q64:(*pos)++;
    if(txt[*pos] == 'a') goto q65;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q65:(*pos)++;
    if(txt[*pos] == 'm') goto q66;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q66:(*pos)++;
    if(txt[*pos] == 'a') goto q67;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q67:(*pos)++;
    if(txt[*pos] == ' ') goto q68;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q68:(*pos)++;
    token.nome = __FIMPROGRAMA__;
    return token;
q69:(*pos)++;
    if(txt[*pos] == 'e') goto q70;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q70:(*pos)++;
    if(txt[*pos] == ' ') goto q71;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q71:(*pos)++;
    token.nome = __FIMSE__;
    return token;
q72:(*pos)++;
    if(txt[*pos] == 'n') goto q73;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q73:(*pos)++;
    if(txt[*pos] == 't') goto q74;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q74:(*pos)++;
    if(txt[*pos] == 'e') goto q75;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q75:(*pos)++;
    if(txt[*pos] == 'i') goto q76;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q76:(*pos)++;
    if(txt[*pos] == 'r') goto q77;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q77:(*pos)++;
    if(txt[*pos] == 'o') goto q78;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q78:(*pos)++;
    if(txt[*pos] == ' ') goto q79;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q79:(*pos)++;
    token.nome = __INTEIRO__;
    return token;
q80:(*pos)++;
    if(txt[*pos] == 'r') goto q81;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q81:(*pos)++;
    if(txt[*pos] == 'o') goto q82;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q82:(*pos)++;
    if(txt[*pos] == 'g') goto q83;
    if(txt[*pos] == 'c') goto q89;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q83:(*pos)++;
    if(txt[*pos] == 'r') goto q84;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q84:(*pos)++;
    if(txt[*pos] == 'a') goto q85;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q85:(*pos)++;
    if(txt[*pos] == 'm') goto q86;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q86:(*pos)++;
    if(txt[*pos] == 'a') goto q87;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q87:(*pos)++;
    if(txt[*pos] == ' ') goto q88;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q88:(*pos)++;
    token.nome = __PROGRAMA__;
    return token;
q89:(*pos)++;
    if(txt[*pos] == 'e') goto q90;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q90:(*pos)++;
    if(txt[*pos] == 'd') goto q91;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q91:(*pos)++;
    if(txt[*pos] == 'i') goto q92;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q92:(*pos)++;
    if(txt[*pos] == 'm') goto q93;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q93:(*pos)++;
    if(txt[*pos] == 'e') goto q94;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q94:(*pos)++;
    if(txt[*pos] == 'n') goto q95;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q95:(*pos)++;
    if(txt[*pos] == 't') goto q96;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q96:(*pos)++;
    if(txt[*pos] == 'o') goto q97;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q97:(*pos)++;
    if(txt[*pos] == ' ') goto q98;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q98:(*pos)++;
    token.nome = __PROCEDIMENTO__;
    return token;
q99:(*pos)++;
    if(txt[*pos] == 'e') goto q100;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q100:(*pos)++;
    if(txt[*pos] == ' ') goto q101;
    else if(txt[*pos] == 'n') goto q102;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q101:(*pos)++;
    token.nome = __SE__;
    return token;
q102:(*pos)++;
    if(txt[*pos] == 'a') goto q103;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q103:(*pos)++;
    if(txt[*pos] == 'o') goto q104;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q104:(*pos)++;
    if(txt[*pos] == ' ') goto q105;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q105:(*pos)++;
    token.nome = __SENAO__;
    return token;
q106:(*pos)++;
    if(txt[*pos] == 'e') goto q107;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q107:(*pos)++;
    if(txt[*pos] == 'r') goto q108;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q108:(*pos)++;
    if(txt[*pos] == 'd') goto q109;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q109:(*pos)++;
    if(txt[*pos] == 'a') goto q110;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q110:(*pos)++;
    if(txt[*pos] == 'd') goto q111;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q111:(*pos)++;
    if(txt[*pos] == 'e') goto q112;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q112:(*pos)++;
    if(txt[*pos] == 'i') goto q113;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q113:(*pos)++;
    if(txt[*pos] == 'r') goto q114;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q114:(*pos)++;
    if(txt[*pos] == 'o') goto q115;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q115:(*pos)++;
    if(txt[*pos] == ' ') goto q116;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q116:(*pos)++;
    token.nome = __VERDADEIRO__;
    return token;
q117:(*pos)++;
    if(isNumber(txt[*pos])) goto q117;
    else if(txt[*pos] == ' ') goto q118;
    else return token;
q118:(*pos)++;
    token.nome = __NUMERO_POSITIVO__;
    token.valor = getValue(txt,*pos);
    return token;
q119:(*pos)++;
    if( isNumber( txt[*pos]) ) goto q120;
    if(txt[*pos] == ' ') goto q122;
    else return token;
q120:(*pos)++;
    if( isNumber( txt[*pos]) ) goto q120;
    if(txt[*pos] == ' ') goto q121;
    else return token;
q121:(*pos)++;
    token.nome = __NUMERO_NEGATIVO__;
    token.valor = getValue(txt, *pos);
    return token;
q122:(*pos)++;
    token.nome = __OPERADOR_SUBTRACAO__;
    return token;
q123:(*pos)++;
    if(txt[*pos] == ' ') goto q124;
    else return token;
q124:(*pos)++;
    token.nome = __OPERADOR_ADICAO__;
    return token;
q125:(*pos)++;
    if(txt[*pos] == 'i') goto q126;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q126:(*pos)++;
    if(txt[*pos] == 'v') goto q127;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q127:(*pos)++;
    if(txt[*pos] == ' ') goto q128;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q128:(*pos)++;
    token.nome = __OPERADOR_DIVISAO__;
    return token;
q129:(*pos)++;
    if(txt[*pos] == 'u') goto q130;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q130:(*pos)++;
    if(txt[*pos] == 'l') goto q131;
    else if(isLetter(txt[*pos])) goto q163;
    else if(txt[*pos] == ' ') goto q164;
    else return token;
q131:(*pos)++;
    if(txt[*pos] == ' ') goto q132;
    else if(isLetter(txt[*pos])) goto q163;
    else return token;
q132:(*pos)++;
    token.nome = __OPERADOR_MULTIPLICACAO__;
    return token;
q133:(*pos)++;
    if(txt[*pos] == ' ' ) goto q134;
    else if(txt[*pos] == '=') goto q135;
    else return token;
q134:(*pos)++;
    token.nome = __OPERADOR_MAIOR__;
    return token;
q135:(*pos)++;
    if(txt[*pos] == ' ') goto q136;
    else return token;
q136:(*pos)++;
    token.nome = __OPERADOR_MAIOR_IGUAL__;
    return token;
q137:(*pos)++;
    if(txt[*pos] == '=') goto q138;
    if(txt[*pos] == '>') goto q141;
    if(txt[*pos] == ' ') goto q140;
    else return token;
q138:(*pos)++;
    if(txt[*pos] == ' ') goto q139;
    else return token;
q139:(*pos)++;
    token.nome = __OPERADOR_MENOR_IGUAL__;
    return token;
q140:(*pos)++;
    token.nome = __OPERADOR_MENOR__;
    return token;
q141:(*pos)++;
    if(txt[*pos] == ' ') goto q142;
    else return token;
q142:(*pos)++;
    token.nome = __OPERADOR_DIFERENCIACAO__;
    return token;
q143:(*pos)++;
    if(txt[*pos] == '=') goto q144;
    else if(txt[*pos] == ' ') goto q146;
    else return token;
q144:(*pos)++;
    if(txt[*pos] == ' ') goto q145;
    else return token;
q145:(*pos)++;
    token.nome = __OPERADOR_COMPARACAO__;
    return token;
q146:(*pos)++;
    token.nome = __OPERADOR_ATRIBUICAO__;
    return token;
q147:(*pos)++;
    if(txt[*pos] == ' ') goto q148;
    else return token;
q148:(*pos)++;
    token.nome = __DELIMITADOR_PA_ABERTO__;
    return token;
q149:(*pos)++;
    if(txt[*pos] == ' ') goto q150;
    else return token;
q150:(*pos)++;
    token.nome = __DELIMITADOR_PA_FECHADO__;
    return token;
q151:(*pos)++;
    if(txt[*pos] == ' ') goto q152;
    else return token;
q152:(*pos)++;
    token.nome = __DELIMITADOR_VIRGULA__;
    return token;
q153:(*pos)++;
    if(txt[*pos] == ' ') goto q154;
    else return token;
q154:(*pos)++;
    token.nome = __DELIMITADOR_DOIS_PONTOS__;
    return token;
q155:(*pos)++;
    if(txt[*pos] == ' ') goto q156;
    else return token;
q156:(*pos)++;
    token.nome = __DELIMITADOR_PONTO_VIRGULA__;
    return token;
q157:(*pos)++;
    if(txt[*pos] == '*') goto q158;
    else return token;
q158:(*pos)++;
    if(txt[*pos] == '*') goto q160;
    else if(txt[*pos] != '*') goto q159; 
    else return token;
q159:(*pos)++;
    if(txt[*pos] == '*') goto q160;
    else if(txt[*pos] != '*') goto q159;  
    else return token;
q160:(*pos)++;
    if(txt[*pos] == '*') goto q160;
    else if(txt[*pos] == '/') goto q161;
    else if(txt[*pos] != '*') goto q159; 
    else return token;
q161:(*pos)++;
    if(txt[*pos] == ' ') goto q162;
    else return token;
q162:(*pos)++;
    token.nome = __COMENTARIO__;
    return token;
q163:(*pos)++;
    if(isLetter(txt[*pos])) goto q163;
    if( txt[*pos] == ' ') goto q164;
    else return token;
q164: (*pos)++;
    token.nome = __IDENTIFICADOR__;
    token.valor = getValue(txt, *pos);
    return token;
}


void readFile(char txt[]) {
    FILE *arquivo_entrada;
    arquivo_entrada = fopen("input.txt","r");
    char line[400];
    
    if (arquivo_entrada) {
        while (fscanf(arquivo_entrada,"%s ", line) != EOF) {
            strcat(line, " ");
            strcat(txt,line);
        }
        fclose(arquivo_entrada);
    }
}

int isNumber(char c) {
    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
        return 1;
    return 0;
}



char* getValue(char txt[],int pos) {
   
    char *valor;
    int i,j;
    int count;
    count = 0;
    
    for (i = pos - 2 ; txt[i] != ' ' && i >= 0 ; i--) {
        count++;
    }

    valor = malloc( 2*count * sizeof(char));
    j =0;
    
    for (i = pos - 2; txt[i] != ' ' && i >= 0; i--) {
        valor[j] = txt[i - count + 1 + 2*j];
        j++;
    }
    
    /* Sem esse print, por algum motivo, ele mistura o valor na memoria. */
    printf("valor: %s\n",valor); 
    
    return valor;
}

/* Verifica se o parametro e um caractere valido na tabela ascii
   [a-z] = [97-122] e [A-Z] = [65-90] */
int isLetter(char c) {
    int a = (int) c;
    if ((a > 96 && a < 123) || (a > 64 && a < 91)) {
        return 1;
    }
    
    return 0;
}

void writeFile(char result[], int pos){
    int i,j,k;
    j = 0;
    char aux[100];
    for(i = 0 ; i< pos ; i++){
        aux[j] = result[i];
        j++;
        if (result[i] == ' ') {
            if (needValue(aux)){
                for(k = i+1 ; result[k] != ' '; k++) i++;
                i++;
            }
            result[i] = '\n';
            j = 0;
            aux[0] = '\0';
        }
    }
    FILE *file;
    file = fopen("output.txt", "w+");
    fprintf(file, result);
    fclose(file);
}

int needValue(char aux[]){
    int c;
    c = atoi(aux);
    if(  c == __NUMERO_POSITIVO__ || c == __NUMERO_NEGATIVO__ || c == __IDENTIFICADOR__) return  1;
    return 0;
}
