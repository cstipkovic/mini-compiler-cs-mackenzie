#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"

typedef struct token {
	int nome;
	char* valor;
}TOKEN;

typedef struct ITEM_TABELA ITEM_TABELA;

typedef struct tabela{
	ITEM_TABELA* itens;
	int topo;
	int escopo;
}TABELA;

struct ITEM_TABELA {
	char* tipo;
	char* identificador;
	TABELA sub_tabela;
	int escopo;
	int* parametros;
	int topo_param;
};

char* lookahead;
char* lastTokenValue;

/* TODO: documentar melhor: itoa buffer */
char buffer[20];

void initAnaliseSintatica();
void getFirstTokent();
void match();
void erro(char* esperado, char* encontrado);
char* getTokenAsString(char* ecnontrado);
void getLookaheadFollow(char** lookaheadFollow);
int eRelacao();
int eParametroDeProcedimento();
int eIdentificador();
int eNumero();
int eBool();
/* O uso de nt no comeco das funcoes indica que essa funcao representa um elemento do conjunto nao-terminal da gramatica*/
void ntPROGRAMA();
void ntBLOCO();
void ntPARTE_DE_DECLARACOES_DE_VARIAVEIS();
void ntDECLARACAO_DE_VARIAVEL();
char* ntTIPO();
void ntLISTA_DE_IDENTIFICADORES(char* tipo);
void ntRESTO_DE_IDENTIFICADORES(char* tipo);
void ntRESTO_DE_DECLARACAO_DE_VARIAVEIS();
void ntPARTE_DE_DECLARACOES_DE_PROCEDIMENTOS();
void ntDECLARACAO_DE_PROCEDIMENTO();
void ntPARAMETROS_FORMAIS();
void ntPARAMETRO_FORMAL();
void ntRESTO_DE_PARAMETROS_FORMAIS();
void ntRESTO_DE_DECLARACOES_DE_PROCEDIMENTOS();
void ntCOMANDO_COMPOSTO();
void ntCOMANDO();
void ntRESTO_DE_COMANDOS();
void ntATRIBUICAO();
char* ntVARIAVEL();
char* ntEXPRESSAO();
char* ntEXPRESSAO_SIMPLES();
char* ntRESTO_DE_EXPRESSAO(char* tipo);
char* ntTERMO();
char* ntRESTO_DE_EXPRESSAO_SIMPLES();
char* ntFATOR();
char* ntRESTO_DE_TERMO();
char* ntNUMERO();
char* ntBOOL();
void ntCOMANDO_CONDICIONAL();
char* ntRELACAO();
void ntCOMANDO_REPETITIVO();
void ntCHAMADA_DE_PROCEDIMENTO();
void ntLISTA_DE_PARAMETROS(char* nome_procedimento);
void ntPARAMETRO_DE_PROCEDIMENTO(char* nome_procedimento, int num_param);
void ntRESTO_DE_PARAMETROS_DE_PROCEDIMENTO(char* nome_procedimento, int num_param);

void verificarParametroDoProc(char* nome_procedimento,int num_param, char* tipo );

TABELA tabela;
int escopo_global;

void criarTabela();
void addTabela(char* tipo, char* lastTokenValue);
void removerTabelaProcedimento(TABELA* tabela);
char* getTableItemType(TABELA tabela, char* lastTokenValue);
void verificarTipos(char* tipo_esquerda, char* tipo_direita);

void imprimirTabelaAux(TABELA tabela);
void addItemNaTabelaRecursivo(TABELA *tabela, ITEM_TABELA item);
int tabelaContem(TABELA tabela, char* lastTokenValue);
void addTipoParamNaTabela(TABELA tabela, char* tipo);

int saoIguais(char* tipo,char *resto_tipo);
int eInteiro(char* tipo);
int eBooleano(char* tipo);

int main(int argc, char *argv[]) {
	/* Criar a tabela simbolica */
	criarTabela();

	/* Inicializar o analisador lexico*/
	initAnaliseLexica();

	/* Inicilizar o analisador Sintatico */
	initAnaliseSintatica();

	return 0;
}

void criarTabela(){
	tabela.itens = (ITEM_TABELA *) calloc(800, sizeof(struct ITEM_TABELA));
	tabela.topo = 0;
	tabela.escopo = 0;
	escopo_global = 0;
}

/* TODO: Documentar esse metodo. */
/* O metodo tabelaContem verifica se um certo identificador esta inserido na tabela. Se for elemento da tabela um procedimento, tera chamada recursiva para aprofundar na tabela e buscar novamente.*/
int tabelaContem(TABELA tabela, char* lastTokenValue){
	int i;
	if(tabela.topo > 0 ){
		if(  strcmp(tabela.itens[tabela.topo - 1 ].tipo, itoa( __PROCEDIMENTO__, buffer, 10 ) ) == 0  ){
			return tabelaContem(tabela.itens[tabela.topo - 1 ].sub_tabela, lastTokenValue );
		}else{
			for( i = tabela.topo - 1 ; i >= 0 ; i-- ){
				if(strcmp(tabela.itens[i].identificador , lastTokenValue) == 0){
					return 1;
				}
			}
			return 0;
		}
	}else{
		return 0;
	}
}

char* getTableItemType(TABELA tabela, char* lastTokenValue){
	int i;
	if(tabela.topo > 0 ){
		/* Se o ultimo na tabela for procedimento, e o ultimo na tabela desse procedimento for procedimento, chama de novo recursivamente. */
		if( strcmp(tabela.itens[tabela.topo - 1 ].tipo , itoa(__PROCEDIMENTO__ , buffer, 10 )) == 0 && tabela.itens[tabela.topo - 1].sub_tabela.topo > 0  ){ 
			return getTableItemType(tabela.itens[tabela.topo - 1 ].sub_tabela, lastTokenValue);
		}else{
			for( i = tabela.topo - 1 ; i >= 0 ; i-- ){
				if( strcmp(tabela.itens[i].identificador , lastTokenValue ) == 0 ){
					return tabela.itens[i].tipo;
				}
			}

			printf("ERRO SEMANTICO\n o identificador \"%s\" nao foi declarado.\n", lastTokenValue);
			exit(0);
		}
	}else{
		printf("ERRO SEMANTICO\n o identificador \"%s\" nao foi declarado.\n", lastTokenValue);
		exit(0);
	}
}

void verificarTipos(char* tipo_esquerda, char* tipo_direita){
	/* TODO: documentar a inconsistencia do string.. */
	char* left;
	char* right;
	left = (char *) calloc(40, sizeof(char));
	right = (char* )calloc(40, sizeof(char));
	strcpy(left, tipo_esquerda);
	strcpy(right, tipo_direita);

	if(strcmp(left, itoa( __INTEIRO__ ,buffer,10) ) == 0  && ( strcmp(right, itoa( __INTEIRO__ ,buffer,10) ) != 0  && strcmp(right, itoa( __NUMERO_POSITIVO__ ,buffer,10) ) != 0 && strcmp(right, itoa( __NUMERO_NEGATIVO__ ,buffer,10) ) != 0 ) ){
		printf("ERRO SEMANTICO\n Nao pode ser feita uma operacao entre %s e %s.\n", getTokenAsString(left), getTokenAsString(right));
		exit(0);
	}
	if(strcmp(left, itoa( __BOOLEANO__ ,buffer,10) ) == 0 && ( strcmp(right, itoa( __BOOLEANO__ ,buffer,10) ) != 0 && strcmp(right, itoa( __VERDADEIRO__ ,buffer,10) ) != 0 && strcmp(right, itoa( __FALSO__ ,buffer,10) ) != 0 ) ){
		printf("ERRO SEMANTICO\n Nao pode ser feita uma operacao entre %s e %s.\n", getTokenAsString(left), getTokenAsString(right));
		exit(0);
	}
}

void verificarProcNaTabela(TABELA tabela,char *nome_procedimento){
	/* TODO: modificar o metodo para fazer a busca recursiva para cobrir todas as tabelas. */
	int i ;
	for ( i = tabela.topo - 1; i >= 0; i-- ){
		if( strcmp(tabela.itens[i].identificador , nome_procedimento ) == 0 && strcmp(tabela.itens[i].tipo, itoa(__PROCEDIMENTO__, buffer, 10)) == 0 ){
			return;
		}
	}

	printf("ERRO SEMANTICO\n o procedimento %s nao foi declarado.\n", nome_procedimento);
	exit(0);	
}

void verificarParametroDoProc(char* nome_procedimento,int num_param, char* tipo ){
	/* TODO: criar um metodo para recuperar o item da tabela .*/
	int i ;
	ITEM_TABELA item;
	for ( i = tabela.topo - 1; i >= 0; i-- ){
		if( strcmp(tabela.itens[i].identificador , nome_procedimento ) == 0 && strcmp(tabela.itens[i].tipo, itoa(__PROCEDIMENTO__, buffer, 10)) == 0 ){
			item = tabela.itens[i];
		}
	}
	if( num_param > item.topo_param - 1){
		printf("ERRO SEMANTICO\n o procedimento %s nao tem %d parametros.\n", item.identificador, num_param + 1);
		exit(0);
	}else if(  strcmp( itoa(item.parametros[num_param], buffer,10), tipo) != 0 ) {
		printf("ERRO SEMANTICO\n o tipo do %d parametro do procedimento %s e diferente de %s.\n", num_param+1, nome_procedimento, getTokenAsString(tipo));
		exit(0);
	}
}

void addTabela(char* tipo, char* lastTokenValue){	
	int i;
	if( tabelaContem(tabela, lastTokenValue) ){
		/* TODO: Se der tempo, melhorar a questao do erro sintatico */
		printf("ERRO SEMANTICO\n o identificador \"%s\" ja esta em uso.\n", lastTokenValue);
		exit(0);
	}

	/* TODO: documentar isso. */
	ITEM_TABELA item_tab;
	item_tab.tipo = calloc(strlen(tipo), sizeof(char));
	item_tab.identificador = calloc(strlen(lastTokenValue), sizeof(char));
	item_tab.escopo = escopo_global;

	strcpy(item_tab.tipo, tipo);
	strcpy(item_tab.identificador, lastTokenValue);	

	if(strcmp( tipo, itoa( __PROCEDIMENTO__ ,buffer,10) ) == 0){
		/* TODO: documentar; */
		escopo_global++;
		item_tab.sub_tabela = (TABELA) item_tab.sub_tabela;
		item_tab.sub_tabela.itens = calloc(256, sizeof(ITEM_TABELA));
		item_tab.sub_tabela.topo = 0;
		item_tab.sub_tabela.escopo = escopo_global;
		item_tab.parametros = calloc(30, sizeof(int));
		item_tab.topo_param = 0;
	}
	/* TODO: documentar melhor. */
	addItemNaTabelaRecursivo(&tabela, item_tab);
}

void addItemNaTabelaRecursivo(TABELA *tabela, ITEM_TABELA item){
	/* Se o escopo global for igual a 0, logo estamos na tabela base, e se for diferente, e pq estamos dentro de um procedimento */
	if( (*tabela).escopo == escopo_global || item.escopo == (*tabela).escopo){
		(*tabela).itens[(*tabela).topo++] = item;
	}else{
		addItemNaTabelaRecursivo( &((*tabela).itens[(*tabela).topo - 1].sub_tabela), item);
	}
}

/* TODO: documentar */
void addTipoParamNaTabela(TABELA tabela, char* tipo){
	if(  strcmp(tabela.itens[tabela.topo - 1 ].tipo, itoa( __PROCEDIMENTO__ , buffer, 10 ) ) ==0 ){
		if( tabela.itens[tabela.topo - 1].sub_tabela.topo > 0 ){
			if( strcmp( tabela.itens[tabela.topo - 1].sub_tabela.itens[tabela.itens[tabela.topo - 1].sub_tabela.topo - 1 ].tipo , itoa(__PROCEDIMENTO__, buffer, 10) ) != 0 ){
				int tipo_int;
				if( strcmp( tipo, itoa( __INTEIRO__ , buffer, 10) ) == 0  ){
					tipo_int = __INTEIRO__;
				}else if(strcmp( tipo, itoa( __BOOLEANO__, buffer, 10 ) ) == 0 ) {
					tipo_int = __BOOLEANO__;
				}
				tabela.itens[tabela.topo - 1 ].parametros[ tabela.itens[tabela.topo - 1 ].topo_param++ ] = tipo_int;
			}	
		}
	}else{
		addTipoParamNaTabela(tabela.itens[tabela.topo - 1].sub_tabela, tipo);
	}
}

/* TODO: Documentar. */
void removerTabelaProcedimento(TABELA* tabela){
	if( (*tabela).escopo == escopo_global ){
		(*tabela).itens = (ITEM_TABELA *) calloc(800, sizeof(struct ITEM_TABELA));
		(*tabela).topo = 0;
		escopo_global--;
	}else{
		removerTabelaProcedimento(&((*tabela).itens[(*tabela).topo - 1].sub_tabela) );
	}
}

void imprimirTabela(){
	printf("\nTabela Simbolica: \n");
	printf("----------------------------\n");
	imprimirTabelaAux(tabela);	
	printf("\n----------------------------\n");
}

void imprimirTabelaAux(TABELA tabela){
	int i , j;
	char* tipo = calloc(40, sizeof(char));
	for( i = 0 ; i < tabela.topo ; i++ ){
		printf("\n| %s\t%s", getTokenAsString(tabela.itens[i].tipo), tabela.itens[i].identificador);
		if( strcmp(tabela.itens[i].tipo , itoa( __PROCEDIMENTO__ ,buffer,10) ) == 0){
			printf("  |  params:  ");
			for( j = 0 ; j < tabela.itens[i].topo_param ; j++ ){
				strcpy(tipo, itoa(tabela.itens[i].parametros[j] , buffer , 10 ));
				printf("\t %s ",  getTokenAsString(tipo));
			}
			/* Se estamos dentro do procedimento. */
			if(tabela.itens[i].sub_tabela.topo > 0){
				printf("\n----------------------------\n");
				imprimirTabelaAux(tabela.itens[i].sub_tabela);
			}
		}
	}	
}

void initAnaliseSintatica(){
	ntPROGRAMA();
}

void ntPROGRAMA(){
	/* Token pega sem match, como a primeira vez da execucao. */
	getFirstTokent();
	if (strcmp(lookahead, itoa( __PROGRAMA__  ,buffer,10)) == 0) {
		match();
		if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10) ) == 0) {
			match();
			if (strcmp(lookahead, itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10) ) == 0) {
				match(); ntBLOCO();
				if (strcmp(lookahead , itoa( __FIMPROGRAMA__,buffer,10) ) == 0) {
					match();
					if (strcmp( lookahead, itoa( __EOF__ ,buffer,10) ) == 0) {
						printf("Analise sintatica finalizada com sucesso.\n");
						printf("Analise semantica finalizada com sucesso.\n");
					} else {
						erro("EOF", lookahead);
					}
				} else {
					erro(itoa( __FIMPROGRAMA__,buffer,10), lookahead );
				}
			} else {
				erro(itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10), lookahead);
			}
		} else {
			erro(itoa( __IDENTIFICADOR__ ,buffer,10), lookahead);
		}
	} else {
		erro(itoa( __PROGRAMA__  ,buffer,10), lookahead);
	}
}

void ntBLOCO() {
	ntPARTE_DE_DECLARACOES_DE_VARIAVEIS();
	ntPARTE_DE_DECLARACOES_DE_PROCEDIMENTOS();
	ntCOMANDO_COMPOSTO(); 
}

void ntPARTE_DE_DECLARACOES_DE_VARIAVEIS() {
	ntDECLARACAO_DE_VARIAVEL(); ntRESTO_DE_DECLARACAO_DE_VARIAVEIS();
}

void ntDECLARACAO_DE_VARIAVEL() {
	/* Como a declaracao de variaveis e opcional, logo verificamos se ha declaracoes, entao chama os metodos que precisa. */
	if (strcmp(lookahead, itoa( __INTEIRO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __BOOLEANO__ ,buffer,10)) == 0) {
		char* tipo = ntTIPO(); 
		ntLISTA_DE_IDENTIFICADORES(tipo);

		if (strcmp(lookahead, itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10)) == 0) {
			match();
		} else {
			erro(itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10), lookahead);
		}
	}
}

char* ntTIPO() {
	char* tipo = calloc(40, sizeof(char));
	if (strcmp(lookahead, itoa( __BOOLEANO__ ,buffer,10)) == 0) {
		strcpy(tipo, lookahead);
		match();
		return tipo;
	} else if (strcmp(lookahead, itoa( __INTEIRO__ ,buffer,10)) == 0) {
		strcpy(tipo, lookahead);
		match();
		return tipo;
	} else {
		erro("inteiro|booleano", lookahead);
	}
}

void ntLISTA_DE_IDENTIFICADORES(char* tipo) {
	if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) {
		addTabela(tipo, lastTokenValue);
		match();
		ntRESTO_DE_IDENTIFICADORES(tipo);
	} else {
		erro(itoa( __IDENTIFICADOR__ ,buffer,10), lookahead);
	}
}

void ntRESTO_DE_IDENTIFICADORES(char* tipo) {
	if (strcmp(lookahead, itoa( __DELIMITADOR_VIRGULA__ ,buffer,10)) == 0) {
		match();
		if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) {
			addTabela(tipo, lastTokenValue);
			match(); ntRESTO_DE_IDENTIFICADORES(tipo);
		} else {
			erro(itoa( __IDENTIFICADOR__ ,buffer,10), lookahead);
		}
	} else {
		/* Considera vazio*/
	}
}

void ntRESTO_DE_DECLARACAO_DE_VARIAVEIS() {
	if (strcmp(lookahead, itoa( __INTEIRO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __BOOLEANO__ ,buffer,10)) == 0) {
		ntDECLARACAO_DE_VARIAVEL(); ntRESTO_DE_DECLARACAO_DE_VARIAVEIS();
	} else {
		/* Considera vazio*/
	}
}

void ntPARTE_DE_DECLARACOES_DE_PROCEDIMENTOS() {
	ntDECLARACAO_DE_PROCEDIMENTO(); ntRESTO_DE_DECLARACOES_DE_PROCEDIMENTOS();
}

void ntDECLARACAO_DE_PROCEDIMENTO() {
	/* Como a declaracao de procedimento e opcional, iremos verificar se alguma declaracao. */

	if (strcmp(lookahead, itoa( __PROCEDIMENTO__ ,buffer,10) ) == 0) {
		match();
		if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10) ) == 0) {
			/* TODO: documentar esse caso. */

			addTabela(itoa( __PROCEDIMENTO__ ,buffer,10), lastTokenValue);

			match();
			if (strcmp(lookahead, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
				match(); ntPARAMETROS_FORMAIS();
				if (strcmp(lookahead, itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10)) == 0) {
					match(); ntBLOCO();
					if (strcmp(lookahead, itoa( __FIMPROCEDIMENTO__ ,buffer,10)) == 0) {
						removerTabelaProcedimento(&tabela);
						match();
					} else {
						erro(itoa( __FIMPROCEDIMENTO__ ,buffer,10), lookahead);
					}
				} else {
					erro(itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10), lookahead);
				}
			} else {
				erro(itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10), lookahead);
			}
		} else {
			erro(itoa( __IDENTIFICADOR__ ,buffer,10), lookahead);
		}
	} else {
		/* Considera Vazio*/
	}
}

void ntPARAMETROS_FORMAIS() {
	/* Parametros formais sao opcionais no procedimento, entao verificamos se ha comeco de algum parametro formal para prosseguir */
	if (strcmp(lookahead, itoa( __INTEIRO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __BOOLEANO__ ,buffer,10)) == 0) {
		ntPARAMETRO_FORMAL(); ntRESTO_DE_PARAMETROS_FORMAIS();
	}
}

void ntPARAMETRO_FORMAL() {
	char* tipo = ntTIPO();
	if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) {
		addTabela(tipo, lastTokenValue );
		addTipoParamNaTabela(tabela, tipo);
		match();
	} else {
		erro(itoa( __IDENTIFICADOR__ ,buffer,10), lookahead);
	}
}

void ntRESTO_DE_PARAMETROS_FORMAIS() {
	if (strcmp(lookahead, itoa( __DELIMITADOR_VIRGULA__ ,buffer,10)) == 0) {
		match(); ntPARAMETRO_FORMAL(); ntRESTO_DE_PARAMETROS_FORMAIS();
	} else {
		/* Considera Vazio*/
	}
}

void ntRESTO_DE_DECLARACOES_DE_PROCEDIMENTOS() {
	if (strcmp(lookahead, itoa( __PROCEDIMENTO__ ,buffer,10)) == 0) {
		ntDECLARACAO_DE_PROCEDIMENTO(); ntRESTO_DE_DECLARACOES_DE_PROCEDIMENTOS();
	} else {
		/* Considera Vazio*/
	}
}

void ntCOMANDO_COMPOSTO() {
	ntCOMANDO();  ntRESTO_DE_COMANDOS();
}

void ntCOMANDO() {
	if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) { /* Pode ser atribuicao ou chamada de funcao */
		/* Para definir o que seria invocado, iremos verificar o proximo token para decidir.*/
		char* lookaheadFollow;
		getLookaheadFollow(&lookaheadFollow);
		if (strcmp(lookaheadFollow, itoa( __OPERADOR_ATRIBUICAO__ ,buffer,10)) == 0) {
			ntATRIBUICAO();
		} else if (strcmp(lookaheadFollow, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
			ntCHAMADA_DE_PROCEDIMENTO();
		} else {
			erro("atribuicao|funcao", lookaheadFollow);
		}
	} else if (strcmp(lookahead, itoa( __SE__ ,buffer,10)) == 0) {
		ntCOMANDO_CONDICIONAL();
	} else if (strcmp(lookahead, itoa( __ENQUANTO__ ,buffer,10)) == 0) {
		ntCOMANDO_REPETITIVO();
	} else if (strcmp(lookahead, itoa( __ESCREVA__ ,buffer,10)) == 0) {
		imprimirTabela();
		match();
		if (strcmp(lookahead, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
			match();
			if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) {
				match();
				if (strcmp(lookahead, itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10)) == 0) {
					match();
					if (strcmp(lookahead, itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10)) == 0) {
						match();
					} else {
						erro(itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10), lookahead);
					}
				} else {
					erro(itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10), lookahead);
				}
			} else {
				erro(itoa( __IDENTIFICADOR__ ,buffer,10), lookahead);
			}
		} else {
			erro(itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10), lookahead);
		}
	} else {
		erro("COMANDO", lookahead);
	}
}

void ntATRIBUICAO() { 
	/* TODO: documentar  */
	char* tipo_esquerda = ntVARIAVEL();
	char* tipo_direita;
	if (strcmp(lookahead, itoa( __OPERADOR_ATRIBUICAO__ ,buffer,10)) == 0) {
		match();
		tipo_direita = ntEXPRESSAO();
		verificarTipos(tipo_esquerda, tipo_direita);

		if (strcmp(lookahead, itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10)) == 0) {
			match();
		} else {
			/*TODO: verificar o erro da itoa pq troca para programa no lugar de delimitador ponto virgula. */
			erro( itoa( __DELIMITADOR_PONTO_VIRGULA__ , buffer, 10 ) , lookahead);
		}
	} else {
		erro(itoa( __OPERADOR_ATRIBUICAO__ ,buffer,10), lookahead);
	}
} 

char* ntVARIAVEL() {
	char* tipo;
	if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) {
		tipo = getTableItemType(tabela, lastTokenValue);
		match();
		return tipo;
	} else {
		erro(itoa( __IDENTIFICADOR__ ,buffer,10), lookahead);
	}
}

char* ntEXPRESSAO() {
	char* tipo;
	char* resto_tipo;

	tipo = ntEXPRESSAO_SIMPLES();
	resto_tipo = ntRESTO_DE_EXPRESSAO(tipo); 

	if(resto_tipo == NULL ){
		return tipo;
	}else{
		if(saoIguais(tipo, resto_tipo)){
			return tipo;
		}else{
			printf("ERRO SEMANTICO\n nao e permitido fazer relacao entre %s e %s", getTokenAsString(tipo), getTokenAsString(resto_tipo));
			exit(0);
		}
	}	 
}

char* ntEXPRESSAO_SIMPLES() { 
	char* tipo;
	char* resto_tipo;
	/* O sinal de Adicao e subtracao e opcional seguindo a gramatica.*/
	if (strcmp(lookahead, itoa( __OPERADOR_ADICAO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __OPERADOR_SUBTRACAO__,buffer,10)) == 0) {
		match();
	}

	tipo =  ntTERMO();
	resto_tipo = ntRESTO_DE_EXPRESSAO_SIMPLES();

	if( resto_tipo == NULL){
		return tipo;
	}

	if( saoIguais(tipo, resto_tipo) ){
		return tipo;
	}else{
		/* TODO: melhorar essas mensagens como criar um metodo para unificar o tipo das variavies.. intiero, numeropositivo e numero negativo e para booleano , verdadeiro e falso. */
		printf("ERRO SEMANTICO\n Nao pode fazer uma operacao de adicao ou subtracao entre %s e %s \n", getTokenAsString(tipo), getTokenAsString(resto_tipo) );
		exit(0);
	}
}

char* ntTERMO() {
	char* tipo = calloc(40, sizeof(char));
	char* resto_tipo = calloc(40, sizeof(char));

	tipo  = ntFATOR();
	resto_tipo = ntRESTO_DE_TERMO();

	if( resto_tipo == NULL){
		return tipo;
	}

	if( saoIguais(tipo, resto_tipo) ){
		if( eBooleano(tipo) ){
			printf("ERRO SEMANTICO\n Nao pode fazer uma operacao de devisao ou multiplicacao entre variaveis do tipo <booleano> \n");	
			exit(0);
		}else
			return tipo;
	}else{

		/* TODO: melhorar essas mensagens como criar um metodo para unificar o tipo das variavies.. intiero, numeropositivo e numero negativo e para booleano , verdadeiro e falso. */
		printf("ERRO SEMANTICO\n Nao pode fazer uma operacao de devisao ou multiplicacao entre %s e %s \n", getTokenAsString(tipo), getTokenAsString(resto_tipo) );
		exit(0);
	}
}

char* ntFATOR() {
	char* tipo_direita = calloc(40, sizeof(char));
	if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) {
		tipo_direita = ntVARIAVEL();		
	} else if (strcmp(lookahead, itoa( __NUMERO_NEGATIVO__,buffer,10)) == 0 || strcmp(lookahead, itoa( __NUMERO_POSITIVO__ ,buffer,10)) == 0) {
		tipo_direita = ntNUMERO();
	} else if (strcmp(lookahead, itoa( __VERDADEIRO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __FALSO__ ,buffer,10)) == 0) {
		tipo_direita = ntBOOL();		
	} else if (strcmp(lookahead, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
		match();
		tipo_direita = ntEXPRESSAO_SIMPLES();	
		if (strcmp(lookahead, itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10)) == 0) {
			match();
		} else {
			erro(itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10), lookahead);
		}
	} else {
		erro("IDENTIFICADOR|NUMERO|BOOL|PA", lookahead);
	}
	return tipo_direita;
}

char* ntNUMERO() {
	char* tipo = calloc(40, sizeof(char));
	if (strcmp(lookahead, itoa( __NUMERO_POSITIVO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __NUMERO_NEGATIVO__,buffer,10)) == 0) {
		strcpy(tipo, lookahead);
		match();
		return tipo;
	} else {
		erro("POSITIVO|NEGATIVO", lookahead);
	}
}

char* ntBOOL() {
	char* tipo = calloc(40, sizeof(char));
	if (strcmp(lookahead, itoa( __VERDADEIRO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __FALSO__ ,buffer,10)) == 0) {
		strcpy(tipo, lookahead);
		match();
		return tipo;
	} else {
		erro("VERDADEIRO|FALSO", lookahead);
	}
}

char* ntRESTO_DE_TERMO() {
	char* tipo;
	tipo = (char *) calloc(40, sizeof(char));
	tipo = NULL;

	if (strcmp(lookahead, itoa( __OPERADOR_MULTIPLICACAO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __OPERADOR_DIVISAO__ ,buffer,10)) == 0) {
		match(); 
		tipo = ntFATOR();
	} else { 
		/* Considera Vazio*/
	}
	return tipo;
}

char* ntRESTO_DE_EXPRESSAO(char* tipo) { 
	char* resto_tipo = (char *) calloc(40,sizeof(char));
	resto_tipo = NULL;
	char* rel = (char *) calloc(40, sizeof(char));
	/* Como e opcional, temos que verificar se ha alguma relacao para invocar as funcoes. */
	if (eRelacao()) {
		/* TODO: continuar o fluxo  */
		rel = ntRELACAO();   
		resto_tipo = ntEXPRESSAO_SIMPLES(); 

		if(  eBooleano(tipo) && eBooleano(resto_tipo) && strcmp(rel, itoa(__OPERADOR_COMPARACAO__ ,buffer,10)) != 0 && strcmp(rel, itoa(__OPERADOR_DIFERENCIACAO__,buffer,10)) !=0 ){
			printf("ERRO SEMANTICO\n Nao pode utilizar o %s entre variaveis de tipo <booleano>", getTokenAsString(lookahead));
			exit(0);
		}
	} else {
		/* Considera Vazio */
	}

	return resto_tipo;
}

char* ntRELACAO() {
	if (strcmp(lookahead, itoa( __OPERADOR_COMPARACAO__ ,buffer,10)) == 0) {
		match();
	} else if (strcmp(lookahead, itoa( __OPERADOR_DIFERENCIACAO__ ,buffer,10)) == 0) {
		match();
	} else if (strcmp(lookahead, itoa( __OPERADOR_MENOR__ ,buffer,10)) == 0) {
		match();
	} else if (strcmp(lookahead, itoa( __OPERADOR_MENOR_IGUAL__ ,buffer,10)) == 0) {
		match();
	} else if (strcmp(lookahead, itoa( __OPERADOR_MAIOR_IGUAL__ ,buffer,10)) == 0) {
		match();
	} else if (strcmp(lookahead, itoa( __OPERADOR_MAIOR__ ,buffer,10)) == 0) {
		match();
	} else {
		erro("RELACAO", lookahead);
	}
	return lookahead;
}

int eRelacao() {
	if (strcmp(lookahead, itoa( __OPERADOR_COMPARACAO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __OPERADOR_DIFERENCIACAO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __OPERADOR_MENOR__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __OPERADOR_MENOR_IGUAL__ ,buffer,10) ) == 0 || strcmp(lookahead, itoa( __OPERADOR_MAIOR_IGUAL__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __OPERADOR_MAIOR__ ,buffer,10)) == 0) {
		return 1;
	} else {
		return 0;
	}
}

void ntRESTO_DE_COMANDOS() {
	/* Como o resto de comandos e opcional, temos que verificar se ha algum comeco de algum comando para prosseguir. */
	if (strcmp( lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __SE__ ,buffer,10) ) == 0 || strcmp(lookahead , itoa( __ENQUANTO__ ,buffer,10)) == 0 || strcmp(lookahead , itoa( __ESCREVA__ ,buffer,10)) == 0) { /* Pode ser atribuicao ou chamada ou condicao ou rempiticao ou escreva */
		ntCOMANDO();
		ntRESTO_DE_COMANDOS();
	} else {
		/* Considera Vazio */
	}
}

char* ntRESTO_DE_EXPRESSAO_SIMPLES() {
	char* tipo;
	tipo = (char *) calloc(40, sizeof(char));
	tipo = NULL;
	/* Temos que verificar se ha um termo ou seja, um fator pelo menos */
	if (strcmp(lookahead, itoa( __OPERADOR_ADICAO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __OPERADOR_SUBTRACAO__,buffer,10)) == 0 || strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0 ||  strcmp(lookahead , itoa( __NUMERO_NEGATIVO__,buffer,10)) == 0 || strcmp(lookahead , itoa( __NUMERO_POSITIVO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __VERDADEIRO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __FALSO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
		/* Como aqui e opcional, devemos verificar o sinal [ + | - ]*/
		if (strcmp(lookahead, itoa( __OPERADOR_ADICAO__ ,buffer,10)) == 0) {
			match();
		} else if (strcmp(lookahead, itoa( __OPERADOR_SUBTRACAO__,buffer,10)) == 0) {
			match();
		}
		tipo = ntTERMO();
	} else {
		/* Considera vazio */
	}
	return tipo;
}

void ntCOMANDO_CONDICIONAL() {
	if (strcmp(lookahead, itoa( __SE__ ,buffer,10)) == 0) {
		match();
		if (strcmp(lookahead, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
			match();
			/* TODO: verificar uma opcao melhor do que enviar NULL */
			ntEXPRESSAO();
			if (strcmp(lookahead, itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10) ) == 0) {
				match();
				if (strcmp(lookahead, itoa( __ENTAO__ ,buffer,10)) == 0) {
					match();
					ntCOMANDO_COMPOSTO();
					/* SENAO e opcional, portanto verificamos so se tem.*/
					if (strcmp(lookahead, itoa( __SENAO__ ,buffer,10)) == 0) {
						match();
						ntCOMANDO_COMPOSTO();
					}
					if (strcmp(lookahead, itoa( __FIMSE__ ,buffer,10)) == 0) {
						match();
					} else {
						erro(itoa( __FIMSE__ ,buffer,10), lookahead);
					}
				} else {
					erro(itoa( __ENTAO__ ,buffer,10), lookahead);
				}
			} else {
				erro(itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10), lookahead);
			}
		} else {
			erro(itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10), lookahead);
		}
	} else {
		erro(itoa( __SE__ ,buffer,10), lookahead);
	}
}

void ntCOMANDO_REPETITIVO() {
	if (strcmp(lookahead, itoa( __ENQUANTO__ ,buffer,10)) == 0) {
		match();
		if (strcmp(lookahead, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
			match();
			/* TODO: verificar uma opcao melhor do que enviar NULL */
			ntEXPRESSAO();
			if (strcmp(lookahead, itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10)) == 0) {
				match();
				if (strcmp(lookahead, itoa( __FACA__ ,buffer,10)) == 0) {
					match();
					ntCOMANDO_COMPOSTO();
					if (strcmp(lookahead, itoa( __FIMENQUANTO__ ,buffer,10)) == 0) {
						match();
					} else {
						erro(itoa( __FIMENQUANTO__ ,buffer,10), lookahead);
					}
				} else {
					erro(itoa( __FACA__ ,buffer,10), lookahead);
				}
			} else {
				erro(itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10), lookahead);
			}
		} else {
			erro(itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10), lookahead);
		}
	} else {
		erro(itoa( __ENQUANTO__ ,buffer,10), lookahead);
	}
}

void ntCHAMADA_DE_PROCEDIMENTO() {
	/* TODO: documentar */
	char* nome_procedimento = (char *) calloc(40, sizeof(char));
	if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) {
		strcpy(nome_procedimento, lastTokenValue);
		verificarProcNaTabela(tabela, nome_procedimento);
		match();
		if (strcmp(lookahead, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
			match(); ntLISTA_DE_PARAMETROS(nome_procedimento);
			if (strcmp(lookahead, itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10)) == 0) {
				match();
				if (strcmp(lookahead, itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10)) == 0) {
					match();
				} else {
					erro(itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10), lookahead);
				}
			} else {
				erro(itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10), lookahead);
			}
		} else {
			erro(itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10), lookahead);
		}
	} else {
		erro(itoa( __IDENTIFICADOR__ ,buffer,10), lookahead);
	}
}

void ntLISTA_DE_PARAMETROS(char* nome_procedimento) {
	/* a posicao do parametro a ser analisado. */
	int param_num = 0;
	/* Como os parametros sao opcionais, tem que verificar se ha algum para ver se e valido.*/
	if (eParametroDeProcedimento()) {
		ntPARAMETRO_DE_PROCEDIMENTO(nome_procedimento, param_num); ntRESTO_DE_PARAMETROS_DE_PROCEDIMENTO(nome_procedimento, param_num);
	} else {
		/* Considera Vazio.*/
	}
}

/* Foi criada essa funcao para ficar mais simples a visualizacao na condicao no metodo ntLISTA_DE_PARAMETROS(). */
int eParametroDeProcedimento() {
	if (eIdentificador() || eNumero() || eBool())
		return 1;
	return 0;
}

int eIdentificador() {
	if (strcmp(lookahead, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0)
		return 1;
	return 0;
}

int eNumero() {
	if (strcmp(lookahead, itoa( __NUMERO_POSITIVO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __NUMERO_NEGATIVO__,buffer,10)) == 0)
		return 1;
	return 0;
}

int eBool() {
	if (strcmp(lookahead, itoa( __VERDADEIRO__ ,buffer,10)) == 0 || strcmp(lookahead, itoa( __FALSO__ ,buffer,10)) == 0)
		return 1;
	return 0;
}

void ntPARAMETRO_DE_PROCEDIMENTO(char* nome_procedimento, int num_param) {
	/* TODO: verificar se os metodos ntNumero e bool retornam o tipo.. */
	char* tipo = (char *) calloc(40, sizeof(char));
	if (eIdentificador()) {
		tipo = getTableItemType(tabela, lastTokenValue);
		match();
	} else if (eNumero()) {
		strcpy(tipo, itoa(__INTEIRO__, buffer, 10));
		ntNUMERO();
	} else if (eBool()) {
		strcpy(tipo, itoa(__BOOLEANO__, buffer, 10));
		ntBOOL();
	} else {
		erro("IDENTIFICADOR|NUMERO|BOOL", lookahead);
	}

	verificarParametroDoProc(nome_procedimento, num_param, tipo );
}

void ntRESTO_DE_PARAMETROS_DE_PROCEDIMENTO(char* nome_procedimento, int num_param) {
	if (strcmp(lookahead, itoa( __DELIMITADOR_VIRGULA__ ,buffer,10)) == 0) {
		match(); ntPARAMETRO_DE_PROCEDIMENTO(nome_procedimento, num_param + 1 ); ntRESTO_DE_PARAMETROS_DE_PROCEDIMENTO( nome_procedimento, num_param + 1);
	} else {
		/* Considera Vazio;*/
	}
}

void getLookaheadFollow(char** lookaheadFollow) {
	/* Este metodo foi criado para ajudar na decisao quando tem mais que uma alternativa de elemento nao terminal */
	/* Por exemplo: quando tiver atribuicao e chamada de funcao, as duas comecam com identificador, e pra isso precisamos */
	/* verificar o token que esta a seguir.*/
	char res[100];
	int len;
	TOKEN token;
	getToken(&token);
	sprintf(res, "%d", token.nome);
	len = strlen(res);

	*lookaheadFollow = (char *) malloc(len * sizeof(char));
	strcpy(*lookaheadFollow, res);
	if (token.valor != NULL) {
		len = len + strlen(token.valor);
	}

	/* o rollback foi criado para retornar a posicao da variavel pos, no analisador lexico, um token atras para que a analise continue normal sem escapar um token que foi pego o lookaheadFollow. */
	rollBackPos(len);
}

void getFirstTokent(){
	TOKEN token;
	getToken(&token);
	lookahead = (char *) malloc( 10 * sizeof(char) );
	sprintf(lookahead, "%d", token.nome); /* Converter o token de int para char* */
}

void match() {
	char res[100];
	int len; 
	TOKEN token;
	getToken(&token);
	sprintf(res, "%d", token.nome);
	len = strlen(res);

	lookahead = (char *) malloc(len * sizeof(char));
	strcpy(lookahead, res);

	if (token.valor != NULL) {
		lastTokenValue = calloc(strlen(token.valor), sizeof(char));
		strcpy(lastTokenValue, token.valor);
	}

	/* Se for um comentario na entrada, entao descarta e vai para o proximo. */
	if (strcmp(lookahead, itoa( __COMENTARIO__ ,buffer,10)) == 0) {
		match();
	}
}

/* TODO: documentar o metodo. */
int saoIguais(char* tipo,char *resto_tipo){

	if(strcmp(tipo, resto_tipo) == 0 ){
		return 1;
	}else if( eInteiro(tipo) && eInteiro(resto_tipo) ){
		return 1;
	}else if( eBooleano(tipo) && eBooleano(resto_tipo) ){
		return 1;
	}else{
		return 0;
	}
}

int eInteiro(char* tipo){
	if( strcmp(tipo, itoa(__INTEIRO__ , buffer, 10)) == 0 || strcmp(tipo, itoa( __NUMERO_POSITIVO__ , buffer, 10)) == 0 || strcmp(tipo, itoa( __NUMERO_NEGATIVO__ , buffer, 10)) == 0 ){
		return 1;
	}
	return 0;
}

int eBooleano(char* tipo){
	if( strcmp(tipo, itoa(__BOOLEANO__ , buffer, 10)) == 0 || strcmp(tipo, itoa( __VERDADEIRO__ , buffer, 10)) == 0 || strcmp(tipo, itoa( __FALSO__ , buffer, 10)) == 0 ){
		return 1;
	}
	return 0;
}



void erro(char* esperado, char* encontrado) {
	printf("%s\n", esperado );
	printf("ERRO SINTATICO\n");
	if (strcmp(esperado, itoa( __PROGRAMA__  ,buffer,10) ) == 0) {
		printf("Esperava o token <programa> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) {
		printf("Esperava o token <identificador> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10)) == 0) {
		printf("Esperava o token <delimitador_ponto_virgula> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, "inteiro|booleano") == 0) {
		printf("Esperava o token <booleano> ou <inteiro> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
		printf("Esperava o token <delimitador_parentese_aberto> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10)) == 0) {
		printf("Esperava o token <delimitador_parentese_fechado> mas encontrou %s\n",getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __FIMPROCEDIMENTO__ ,buffer,10)) == 0) {
		printf("Esperava o token <fimprocedimento> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __DELIMITADOR_VIRGULA__ ,buffer,10)) == 0) {
		printf("Esperava o token <delimitador_virgula> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, "COMANDO") == 0) {
		printf("Esperava o token <identificador> ou <se> ou <enqunato> ou <escreva> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, "atribuicao|funcao") == 0) {
		printf("Esperava o token <operador_atribuicao> ou <delimitador_parentese_aberto> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, "POSITIVO|NEGATIVO") == 0) {
		printf("Esperava o token <numero_positivo> ou <numero_negativo> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, "VERDADEIRO|FALSO") == 0) {
		printf("Esperava o token <verdadeiro> ou <falso> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, "IDENTIFICADOR|NUMERO|BOOL|PA") == 0) {
		printf("Esperava o token <identificador> ou <numero_positivo> ou <numero_negativo> ou <verdadeiro> ou <falso> ou <delimitador_parentese_aberto> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __SE__ ,buffer,10)) == 0) {
		printf("Esperava o token <se> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, "RELACAO") == 0) {
		printf("Esperava o token <operador_comparacao> ou <operador_diferenciacao> ou <operador_menor> ou <operador_menor_igual> ou <operador_maior> ou <operador_maior_igual> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __ENTAO__ ,buffer,10)) == 0) {
		printf("Esperava o token <entao> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __FIMSE__ ,buffer,10)) == 0) {
		printf("Esperava o token <fimse> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __ENQUANTO__ ,buffer,10)) == 0) {
		printf("Esperava o token <enquanto> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __FACA__ ,buffer,10)) == 0) {
		printf("Esperava o token <faca> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __FIMENQUANTO__ ,buffer,10)) == 0) {
		printf("Esperava o token <fimenquanto> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, itoa( __FIMPROGRAMA__,buffer,10)) == 0) {
		printf("Esperava o token <fimprograma> mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado, "EOF") == 0) {
		printf("Esperava o fim do arquivo, mas encontrou %s\n", getTokenAsString(encontrado));
	} else if (strcmp(esperado , "IDENTIFICADOR|NUMERO|BOOL") == 0) {
		printf("Esperava o token <identificador> ou <numero_positivo> ou <numero_negativo> ou <verdadeiro> ou <falso>, mas encontrou %s\n", getTokenAsString(encontrado));
	} else {
		printf("Esperava o token <%s> mas encontrou %s\n", esperado, getTokenAsString(encontrado));
	}

	exit(0); /* para matar as chamads recursivas e sair do programa. */
}

char* getTokenAsString(char* encontrado) {
	char* token ;
	token = malloc(40 * sizeof(char));
	strcpy(token, encontrado);

	if (strcmp(encontrado, itoa( __PROGRAMA__  ,buffer,10)) == 0) {
		strcpy(token, "<programa>");
	} else if (strcmp(encontrado, itoa( __IDENTIFICADOR__ ,buffer,10)) == 0) {
		strcpy(token, "<identificador>");
	} else if (strcmp(encontrado, itoa( __DELIMITADOR_PONTO_VIRGULA__ ,buffer,10)) == 0) {
		strcpy(token, "<delimitador_ponto_virgula>");
	} else if (strcmp(encontrado, itoa( __INTEIRO__ ,buffer,10)) == 0) {
		strcpy(token, "<inteiro>");
	} else if (strcmp(encontrado, itoa( __BOOLEANO__ ,buffer,10)) == 0) {
		strcpy(token, "<booleano>");
	} else if (strcmp(encontrado, itoa( __DELIMITADOR_PA_ABERTO__ ,buffer,10)) == 0) {
		strcpy(token, "<delimitador_parentese_aberto>");
	} else if (strcmp(encontrado, itoa( __DELIMITADOR_PA_FECHADO__ ,buffer,10)) == 0) {
		strcpy(token, "<delimitador_parentese_fechado>");
	} else if (strcmp(encontrado, itoa( __FIMPROCEDIMENTO__ ,buffer,10)) == 0) {
		strcpy(token, "<fimprocedimento>");
	} else if (strcmp(encontrado, itoa(__DELIMITADOR_VIRGULA__, buffer, 10) ) == 0) {
		strcpy(token, "<delimitador_virgula>");
	} else if (strcmp(encontrado, itoa( __OPERADOR_ATRIBUICAO__ ,buffer,10)) == 0) {
		strcpy(token, "<operador_atribuicao>");
	} else if (strcmp(encontrado, itoa( __NUMERO_POSITIVO__ ,buffer,10)) == 0) {
		strcpy(token, "<numero_positivo>");
	} else if (strcmp(encontrado, itoa( __NUMERO_NEGATIVO__,buffer,10)) == 0) {
		strcpy(token, "<numero_negativo>");
	} else if (strcmp(encontrado, itoa( __VERDADEIRO__ ,buffer,10)) == 0) {
		strcpy(token, "<verdadeiro>");
	} else if (strcmp(encontrado, itoa( __FALSO__ ,buffer,10)) == 0) {
		strcpy(token, "<falso>");
	} else if (strcmp(encontrado, itoa( __SE__ ,buffer,10)) == 0) {
		strcpy(token, "<se>");
	} else if (strcmp(encontrado, itoa( __OPERADOR_COMPARACAO__ ,buffer,10)) == 0) {
		strcpy(token, "<operador_comparacao>");
	} else if (strcmp(encontrado, itoa( __OPERADOR_DIFERENCIACAO__ ,buffer,10)) == 0) {
		strcpy(token, "<operador_diferenciacao>");
	} else if (strcmp(encontrado, itoa( __OPERADOR_MENOR__ ,buffer,10)) == 0) {
		strcpy(token, "<operador_menor>");
	} else if (strcmp(encontrado, itoa( __OPERADOR_MENOR_IGUAL__ ,buffer,10)) == 0) {
		strcpy(token, "<operador_menor_igual>");
	} else if (strcmp(encontrado, itoa( __OPERADOR_MAIOR_IGUAL__ ,buffer,10)) == 0) {
		strcpy(token, "<operador_maior_igual>");
	} else if(strcmp(encontrado, itoa( __OPERADOR_MAIOR__ ,buffer,10)) == 0) {
		strcpy(token, "<operador_maior>");
	} else if (strcmp(encontrado, itoa( __ENTAO__ ,buffer,10)) == 0) {
		strcpy(token, "<entao>");
	} else if (strcmp(encontrado, itoa( __FIMSE__ ,buffer,10)) == 0) {
		strcpy(token, "<fimse>");
	} else if (strcmp(encontrado, itoa( __ENQUANTO__ ,buffer,10)) == 0) {
		strcpy(token, "<enquanto>");
	} else if (strcmp(encontrado, itoa( __FACA__ ,buffer,10)) == 0) {
		strcpy(token, "<faca>");
	} else if (strcmp(encontrado, itoa( __FIMENQUANTO__ ,buffer,10)) == 0) {
		strcpy(token, "<fimenquanto>");
	} else if (strcmp(encontrado, itoa( __FIMPROGRAMA__,buffer,10)) == 0) {
		strcpy(token, "<fimprograma>");
	}else if( strcmp(encontrado, itoa( __PROCEDIMENTO__ ,buffer,10) ) == 0 ){
		strcpy(token, "<procedimento>");
	}else if( strcmp(encontrado, itoa( __SENAO__ ,buffer,10) ) == 0 ){
		strcpy(token, "<senao>");
	}else if( strcmp(encontrado, itoa( __ESCREVA__ ,buffer,10) ) == 0 ){
		strcpy(token, "<escreva>");
	}else if( strcmp(encontrado, itoa( __OPERADOR_SUBTRACAO__,buffer,10) ) == 0 ){
		strcpy(token, "<operador_subtracao>");
	}else if( strcmp(encontrado, itoa( __OPERADOR_ADICAO__ ,buffer,10) ) == 0 ){
		strcpy(token, "<operador_adicao>");
	}else if( strcmp(encontrado, itoa( __OPERADOR_DIVISAO__ ,buffer,10) ) == 0 ){
		strcpy(token, "<operador_divisao>");
	}else if( strcmp(encontrado, itoa( __OPERADOR_MULTIPLICACAO__ ,buffer,10) ) == 0 ){
		strcpy(token, "<operador_multiplicacao>");
	}else if( strcmp(encontrado, itoa( __PROCEDIMENTO__ ,buffer,10) ) == 0 ){
		strcpy(token, "<__DELIMITADOR_DOIS_PONTOS>");
	}else if( strcmp(encontrado, itoa( __EOF__ ,buffer,10) ) == 0 ){
		strcpy(token, "<fim_do_arquivo>");
	}
	return token;
}
