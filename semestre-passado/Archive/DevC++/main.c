#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __PROGRAMA__  "100"
#define __FIMPROGRAMA__ "101"
#define __PROCEDIMENTO__ "102"
#define __FIMPROCEDIMENTO__ "103"
#define __SE__ "104"
#define __FIMSE__ "105"
#define __ENQUANTO__ "106"
#define __FIMENQUANTO__ "107"
#define __ENTAO__  "108"
#define __SENAO__ "109"
#define __BOOLEANO__ "110"
#define __FACA__ "111"
#define __FALSO__ "112"
#define __ESCREVA__ "113"

#define __INTEIRO__ "200"
#define __VERDADEIRO__ "201"
#define __NUMERO_POSITIVO__ "202"
#define __NUMERO_NEGATIVO__ "203"

#define __OPERADOR_SUBTRACAO__ "300"
#define __OPERADOR_ADICAO__ "301"
#define __OPERADOR_DIVISAO__ "302"
#define __OPERADOR_MULTIPLICACAO__ "303"
#define __OPERADOR_MAIOR__ "304"
#define __OPERADOR_MAIOR_IGUAL__ "305"
#define __OPERADOR_MENOR_IGUAL__ "306"
#define __OPERADOR_MENOR__ "307"
#define __OPERADOR_DIFERENCIACAO__ "308"
#define __OPERADOR_COMPARACAO__ "309"
#define __OPERADOR_ATRIBUICAO__ "310"

#define __DELIMITADOR_PA_ABERTO__ "400"
#define __DELIMITADOR_PA_FECHADO__ "401"
#define __DELIMITADOR_VIRGULA__ "402"
#define __DELIMITADOR_DOIS_PONTOS__ "403"
#define __DELIMITADOR_PONTO_VIRGULA__ "404"

#define __COMENTARIO__ "500"

#define __IDENTIFICADOR__ "600"

#define __ERRO__ "700"

#define __EOF__ "800"


typedef struct token {
    int nome;
    char* valor;
}TOKEN;

char* lookahead;
void initAnaliseSintatica();
void getFirstTokent();
void match();
void erro(char* esperado, char* encontrado);
char* getErrorToken(char* ecnontrado);
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
void ntTIPO();
void ntLISTA_DE_IDENTIFICADORES();
void ntRESTO_DE_IDENTIFICADORES();
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
void ntVARIAVEL();
void ntEXPRESSAO();
void ntEXPRESSAO_SIMPLES();
void ntRESTO_DE_EXPRESSAO();
void ntTERMO();
void ntRESTO_DE_EXPRESSAO_SIMPLES();
void ntFATOR();
void ntRESTO_DE_TERMO();
void ntNUMERO();
void ntBOOL();
void ntCOMANDO_CONDICIONAL();
void ntRELACAO();
void ntCOMANDO_REPETITIVO();
void ntCHAMADA_DE_PROCEDIMENTO();
void ntLISTA_DE_PARAMETROS();
void ntPARAMETRO_DE_PROCEDIMENTO();
void ntRESTO_DE_PARAMETROS_DE_PROCEDIMENTO();


int main(int argc, char *argv[]) {
	/* Inicializar o analisador lexico*/
	initAnaliseLexica();

	/* Inicilizar o analisador Sintatico */
	initAnaliseSintatica();

	return 0;
}

void initAnaliseSintatica(){
	ntPROGRAMA();
}

void ntPROGRAMA(){
	/* Token pega sem match, como a primeira vez da execucao. */
	getFirstTokent();
	if (strcmp(lookahead, __PROGRAMA__) == 0) {
		match();
		if (strcmp(lookahead, __IDENTIFICADOR__ ) == 0) {
			match();
			if (strcmp(lookahead, __DELIMITADOR_PONTO_VIRGULA__ ) == 0) {
				match(); ntBLOCO();
				if (strcmp(lookahead , __FIMPROGRAMA__ ) == 0) {
					match();
					if (strcmp( lookahead, __EOF__ ) == 0) {
						printf("Analise sintatica finalizada com sucesso.\n");
					} else {
						erro("EOF", lookahead);
					}
				} else {
					erro(__FIMPROGRAMA__, lookahead );
				}
			} else {
				erro(__DELIMITADOR_PONTO_VIRGULA__, lookahead);
			}
		} else {
			erro(__IDENTIFICADOR__, lookahead);
		}
	} else {
		erro(__PROGRAMA__, lookahead);
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
	if (strcmp(lookahead, __INTEIRO__) == 0 || strcmp(lookahead, __BOOLEANO__) == 0) {
		
		ntTIPO(); ntLISTA_DE_IDENTIFICADORES();
		
		if (strcmp(lookahead, __DELIMITADOR_PONTO_VIRGULA__) == 0) {
			match();
		} else {
			erro(__DELIMITADOR_PONTO_VIRGULA__, lookahead);
		}
	}
}

void ntTIPO() {
	if (strcmp(lookahead, __BOOLEANO__) == 0) {
		match();
	} else if (strcmp(lookahead, __INTEIRO__) == 0) {
		match();
	} else {
		erro("inteiro|booleano", lookahead);
	}
}

void ntLISTA_DE_IDENTIFICADORES() {
	if (strcmp(lookahead, __IDENTIFICADOR__) == 0) {
		match();
		ntRESTO_DE_IDENTIFICADORES();
	} else {
		erro(__IDENTIFICADOR__, lookahead);
	}
}

void ntRESTO_DE_IDENTIFICADORES() {
	if (strcmp(lookahead, __DELIMITADOR_VIRGULA__) == 0) {
		match();

		if (strcmp(lookahead, __IDENTIFICADOR__) == 0) {
			match(); ntRESTO_DE_IDENTIFICADORES();
		} else {
			erro(__IDENTIFICADOR__, lookahead);
		}
	} else {
		/* Considera vazio*/
	}
}

void ntRESTO_DE_DECLARACAO_DE_VARIAVEIS() {
	if (strcmp(lookahead, __INTEIRO__) == 0 || strcmp(lookahead, __BOOLEANO__) == 0) {
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
	if (strcmp(lookahead, __PROCEDIMENTO__ ) == 0) {
		match();
		if (strcmp(lookahead, __IDENTIFICADOR__ ) == 0) {
			match();
			if (strcmp(lookahead, __DELIMITADOR_PA_ABERTO__) == 0) {
				match(); ntPARAMETROS_FORMAIS();
				if (strcmp(lookahead, __DELIMITADOR_PA_FECHADO__) == 0) {
						match(); ntBLOCO();
						if (strcmp(lookahead, __FIMPROCEDIMENTO__) == 0) {
							match();
						} else {
							erro(__FIMPROCEDIMENTO__, lookahead);
						}
				} else {
					erro(__DELIMITADOR_PA_FECHADO__, lookahead);
				}
			} else {
				erro(__DELIMITADOR_PA_ABERTO__, lookahead);
			}
		} else {
			erro(__IDENTIFICADOR__, lookahead);
		}
	} else {
		/* Considera Vazio*/
	}
}

void ntPARAMETROS_FORMAIS() {
	/* Parametros formais sao opcionais no procedimento, entao verificamos se ha comeco de algum parametro formal para prosseguir */
	if (strcmp(lookahead, __INTEIRO__) == 0 || strcmp(lookahead, __BOOLEANO__) == 0) {
		ntPARAMETRO_FORMAL(); ntRESTO_DE_PARAMETROS_FORMAIS();
	}
}

void ntPARAMETRO_FORMAL() {
	ntTIPO();
	if (strcmp(lookahead, __IDENTIFICADOR__) == 0) {
		match();
	} else {
		erro(__IDENTIFICADOR__, lookahead);
	}
}

void ntRESTO_DE_PARAMETROS_FORMAIS() {
	if (strcmp(lookahead, __DELIMITADOR_VIRGULA__) == 0) {
		match(); ntPARAMETRO_FORMAL(); ntRESTO_DE_PARAMETROS_FORMAIS();
	} else {
		/* Considera Vazio*/
	}
}

void ntRESTO_DE_DECLARACOES_DE_PROCEDIMENTOS() {
	if (strcmp(lookahead, __PROCEDIMENTO__) == 0) {
		ntDECLARACAO_DE_PROCEDIMENTO(); ntRESTO_DE_DECLARACOES_DE_PROCEDIMENTOS();
	} else {
		/* Considera Vazio*/
	}
}

void ntCOMANDO_COMPOSTO() {
	ntCOMANDO();  ntRESTO_DE_COMANDOS();
}

void ntCOMANDO() {
	if (strcmp(lookahead, __IDENTIFICADOR__) == 0) { /* Pode ser atribuicao ou chamada de funcao */
	/* Para definir o que seria invocado, iremos verificar o proximo token para decidir.*/
		char* lookaheadFollow;
		getLookaheadFollow(&lookaheadFollow);
		if (strcmp(lookaheadFollow, __OPERADOR_ATRIBUICAO__) == 0) {
			ntATRIBUICAO();
		} else if (strcmp(lookaheadFollow, __DELIMITADOR_PA_ABERTO__) == 0) {
			ntCHAMADA_DE_PROCEDIMENTO();
		} else {
			erro("atribuicao|funcao", lookaheadFollow);
		}
	} else if (strcmp(lookahead, __SE__) == 0) {
		ntCOMANDO_CONDICIONAL();
	} else if (strcmp(lookahead, __ENQUANTO__) == 0) {
		ntCOMANDO_REPETITIVO();
	} else if (strcmp(lookahead, __ESCREVA__) == 0) {
		match();
		if (strcmp(lookahead, __DELIMITADOR_PA_ABERTO__) == 0) {
			match();
			if (strcmp(lookahead, __IDENTIFICADOR__) == 0) {
				match();
				if (strcmp(lookahead, __DELIMITADOR_PA_FECHADO__) == 0) {
					match();

					if (strcmp(lookahead, __DELIMITADOR_PONTO_VIRGULA__) == 0) {
						match();
					} else {
						erro(__DELIMITADOR_PONTO_VIRGULA__, lookahead);
					}
				} else {
					erro(__DELIMITADOR_PA_FECHADO__, lookahead);
				}
			} else {
				erro(__IDENTIFICADOR__, lookahead);
			}
		} else {
			erro(__DELIMITADOR_PA_ABERTO__, lookahead);
		}
	} else {
		erro("COMANDO", lookahead);
	}
}

void ntATRIBUICAO() {
	ntVARIAVEL();
	if (strcmp(lookahead, __OPERADOR_ATRIBUICAO__) == 0) {
		match();
		ntEXPRESSAO();
		if (strcmp(lookahead, __DELIMITADOR_PONTO_VIRGULA__) == 0) {
			match();
		} else {
			erro(__DELIMITADOR_PONTO_VIRGULA__, lookahead);
		}
	} else {
		erro(__OPERADOR_ATRIBUICAO__, lookahead);
	}
}

void ntVARIAVEL() {
	if (strcmp(lookahead, __IDENTIFICADOR__) == 0) {
		match();
	} else {
		erro(__IDENTIFICADOR__, lookahead);
	}
}

void ntEXPRESSAO() {
	ntEXPRESSAO_SIMPLES(); ntRESTO_DE_EXPRESSAO();
}

void ntEXPRESSAO_SIMPLES() {
	/* O sinal de Adicao e subtracao e opcional seguindo a gramatica.*/
	if (strcmp(lookahead, __OPERADOR_ADICAO__) == 0 || strcmp(lookahead, __OPERADOR_SUBTRACAO__) == 0) {
		match();
	}

	ntTERMO(); ntRESTO_DE_EXPRESSAO_SIMPLES();
}

void ntTERMO() {
	ntFATOR(); ntRESTO_DE_TERMO();
}

void ntFATOR() {
	if (strcmp(lookahead, __IDENTIFICADOR__) == 0) {
		ntVARIAVEL();
	} else if (strcmp(lookahead, __NUMERO_NEGATIVO__) == 0 || strcmp(lookahead, __NUMERO_POSITIVO__) == 0) {
		ntNUMERO();
	} else if (strcmp(lookahead, __VERDADEIRO__) == 0 || strcmp(lookahead, __FALSO__) == 0) {
		ntBOOL();
	} else if (strcmp(lookahead, __DELIMITADOR_PA_ABERTO__) == 0) {
		match();
		ntEXPRESSAO_SIMPLES();
		if (strcmp(lookahead, __DELIMITADOR_PA_FECHADO__) == 0) {
			match();
		} else {
			erro(__DELIMITADOR_PA_FECHADO__, lookahead);
		}
	} else {
		erro("IDENTIFICADOR|NUMERO|BOOL|PA", lookahead);
	}
}

void ntNUMERO() {
	if (strcmp(lookahead, __NUMERO_POSITIVO__) == 0 || strcmp(lookahead, __NUMERO_NEGATIVO__) == 0) {
		match();
	} else {
		erro("POSITIVO|NEGATIVO", lookahead);
	}
}

void ntBOOL() {
	if (strcmp(lookahead, __VERDADEIRO__) == 0 || strcmp(lookahead, __FALSO__) == 0) {
		match();
	} else {
		erro("VERDADEIRO|FALSO", lookahead);
	}
}

void ntRESTO_DE_TERMO() {
	if (strcmp(lookahead, __OPERADOR_MULTIPLICACAO__) == 0 || strcmp(lookahead, __OPERADOR_DIVISAO__) == 0) {
		match();
		ntFATOR();
	} else {
		/* Considera Vazio*/
	}
}

void ntRESTO_DE_EXPRESSAO() {
	/* Como e opcional, temos que verificar se ha alguma relacao para invocar as funcoes. */
	if (eRelacao()) {
		ntRELACAO(); ntEXPRESSAO_SIMPLES();
	} else {
		/* Considera Vazio */
	}
}

void ntRELACAO() {
  if (strcmp(lookahead, __OPERADOR_COMPARACAO__) == 0) {
    match();
  } else if (strcmp(lookahead, __OPERADOR_DIFERENCIACAO__) == 0) {
    match();
  } else if (strcmp(lookahead, __OPERADOR_MENOR__) == 0) {
    match();
  } else if (strcmp(lookahead, __OPERADOR_MENOR_IGUAL__) == 0) {
    match();
  } else if (strcmp(lookahead, __OPERADOR_MAIOR_IGUAL__) == 0) {
    match();
  } else if (strcmp(lookahead, __OPERADOR_MAIOR__) == 0) {
    match();
  } else {
    erro("RELACAO", lookahead);
  }
}

int eRelacao() {
  if (strcmp(lookahead, __OPERADOR_COMPARACAO__) == 0 || strcmp(lookahead, __OPERADOR_DIFERENCIACAO__) == 0 || strcmp(lookahead, __OPERADOR_MENOR__) == 0 || strcmp(lookahead, __OPERADOR_MENOR_IGUAL__ ) == 0 || strcmp(lookahead, __OPERADOR_MAIOR_IGUAL__) == 0 || strcmp(lookahead, __OPERADOR_MAIOR__) == 0) {
    return 1;
  } else {
    return 0;
  }
}

void ntRESTO_DE_COMANDOS() {
	/* Como o resto de comandos e opcional, temos que verificar se ha algum comeco de algum comando para prosseguir. */
  	if (strcmp( lookahead, __IDENTIFICADOR__) == 0 || strcmp(lookahead, __SE__ ) == 0 || strcmp(lookahead , __ENQUANTO__) == 0 || strcmp(lookahead , __ESCREVA__) == 0) { /* Pode ser atribuicao ou chamada ou condicao ou rempiticao ou escreva */
    	ntCOMANDO();
    	ntRESTO_DE_COMANDOS();
  	} else {
  	 	 /* Considera Vazio */
  	}
}

void ntRESTO_DE_EXPRESSAO_SIMPLES() {
  /* Temos que verificar se ha um termo ou seja, um fator pelo menos */
  if (strcmp(lookahead, __OPERADOR_ADICAO__) == 0 || strcmp(lookahead, __OPERADOR_SUBTRACAO__) == 0 || strcmp(lookahead, __IDENTIFICADOR__) == 0 ||  strcmp(lookahead , __NUMERO_NEGATIVO__) == 0 || strcmp(lookahead , __NUMERO_POSITIVO__) == 0 || strcmp(lookahead, __VERDADEIRO__) == 0 || strcmp(lookahead, __FALSO__) == 0 || strcmp(lookahead, __DELIMITADOR_PA_ABERTO__) == 0) {
  	/* Como aqui e opcional, devemos verificar o sinal [ + | - ]*/
    if (strcmp(lookahead, __OPERADOR_ADICAO__) == 0) {
      match();
    } else if (strcmp(lookahead, __OPERADOR_SUBTRACAO__) == 0) {
      match();
    }
    ntTERMO();
  } else {
      /* Considera vazio */
  }
}

void ntCOMANDO_CONDICIONAL() {
  if (strcmp(lookahead, __SE__) == 0) {
    match();

    if (strcmp(lookahead, __DELIMITADOR_PA_ABERTO__) == 0) {
      match();
      ntEXPRESSAO();

      if (strcmp(lookahead, __DELIMITADOR_PA_FECHADO__ ) == 0) {
        match();

        if (strcmp(lookahead, __ENTAO__) == 0) {
          match();
          ntCOMANDO_COMPOSTO();

		  /* SENAO e opcional, portanto verificamos so se tem.*/
          if (strcmp(lookahead, __SENAO__) == 0) {
            match();
            ntCOMANDO_COMPOSTO();
          }

          if (strcmp(lookahead, __FIMSE__) == 0) {
            match();
          } else {
            erro(__FIMSE__, lookahead);
          }
        } else {
          erro(__ENTAO__, lookahead);
        }
      } else {
        erro(__DELIMITADOR_PA_FECHADO__, lookahead);
      }
    } else {
      erro(__DELIMITADOR_PA_ABERTO__, lookahead);
    }
  } else {
    erro(__SE__, lookahead);
  }
}

void ntCOMANDO_REPETITIVO() {
  if (strcmp(lookahead, __ENQUANTO__) == 0) {
    match();

    if (strcmp(lookahead, __DELIMITADOR_PA_ABERTO__) == 0) {
      match();
      ntEXPRESSAO();

      if (strcmp(lookahead, __DELIMITADOR_PA_FECHADO__) == 0) {
        match();

        if (strcmp(lookahead, __FACA__) == 0) {
          match();
          ntCOMANDO_COMPOSTO();

          if (strcmp(lookahead, __FIMENQUANTO__) == 0) {
            match();
          } else {
            erro(__FIMENQUANTO__, lookahead);
          }
        } else {
          erro(__FACA__, lookahead);
        }
      } else {
        erro(__DELIMITADOR_PA_FECHADO__, lookahead);
      }
    } else {
      erro(__DELIMITADOR_PA_ABERTO__, lookahead);
    }
  } else {
    erro(__ENQUANTO__, lookahead);
  }
}

void ntCHAMADA_DE_PROCEDIMENTO() {
	if (strcmp(lookahead, __IDENTIFICADOR__) == 0) {
		match();

		if (strcmp(lookahead, __DELIMITADOR_PA_ABERTO__) == 0) {
		
			match(); ntLISTA_DE_PARAMETROS();

			if (strcmp(lookahead, __DELIMITADOR_PA_FECHADO__) == 0) {
				match();
				if (strcmp(lookahead, __DELIMITADOR_PONTO_VIRGULA__) == 0) {
					match();
				} else {
					erro(__DELIMITADOR_PONTO_VIRGULA__, lookahead);
				}
    		} else {
				erro(__DELIMITADOR_PA_FECHADO__, lookahead);
			}
		} else {
			erro(__DELIMITADOR_PA_ABERTO__, lookahead);
		}
	} else {
		erro(__IDENTIFICADOR__, lookahead);
	}
}

void ntLISTA_DE_PARAMETROS() {
	/* Como os parametros sao opcionais, tem que verificar se ha algum para ver se e valido.*/
	if (eParametroDeProcedimento()) {
		ntPARAMETRO_DE_PROCEDIMENTO(); ntRESTO_DE_PARAMETROS_DE_PROCEDIMENTO();
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
	if (strcmp(lookahead, __IDENTIFICADOR__) == 0)
		return 1;
	return 0;
}

int eNumero() {
	if (strcmp(lookahead, __NUMERO_POSITIVO__) == 0 || strcmp(lookahead, __NUMERO_NEGATIVO__) == 0)
		return 1;
	return 0;
}

int eBool() {
	if (strcmp(lookahead, __VERDADEIRO__) == 0 || strcmp(lookahead, __FALSO__) == 0)
		return 1;
	return 0;
}

void ntPARAMETRO_DE_PROCEDIMENTO() {
	if (eIdentificador()) {
		match();
	} else if (eNumero()) {
		ntNUMERO();
	} else if (eBool()) {
		ntBOOL();
	} else {
		erro("IDENTIFICADOR|NUMERO|BOOL", lookahead);
	}
}

void ntRESTO_DE_PARAMETROS_DE_PROCEDIMENTO() {
	if (strcmp(lookahead, __DELIMITADOR_VIRGULA__) == 0) {
		match(); ntPARAMETRO_DE_PROCEDIMENTO(); ntRESTO_DE_PARAMETROS_DE_PROCEDIMENTO();
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

	/* Se for um comentario na entrada, entao descarta e vai para o proximo. */
	if (strcmp(lookahead, __COMENTARIO__) == 0) {
		match();
	}
}

void erro(char* esperado, char* encontrado) {
  printf("ERRO SINTATICO\n");
  if (strcmp(esperado, __PROGRAMA__) == 0) {                                                           	
    printf("Esperava o token <programa> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __IDENTIFICADOR__) == 0) {
    printf("Esperava o token <identificador> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __DELIMITADOR_PONTO_VIRGULA__) == 0) {
    printf("Esperava o token <delimitador_ponto_virgula> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, "inteiro|booleano") == 0) {
    printf("Esperava o token <booleano> ou <inteiro> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __DELIMITADOR_PA_ABERTO__) == 0) {
    printf("Esperava o token <delimitador_parentese_aberto> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __DELIMITADOR_PA_FECHADO__) == 0) {
    printf("Esperava o token <delimitador_parentese_fechado> mas encontrou %s\n",getErrorToken(encontrado));
  } else if (strcmp(esperado, __FIMPROCEDIMENTO__) == 0) {
    printf("Esperava o token <fimprocedimento> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __DELIMITADOR_VIRGULA__) == 0) {
    printf("Esperava o token <delimitador_virgula> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, "COMANDO") == 0) {
    printf("Esperava o token <identificador> ou <se> ou <enqunato> ou <escreva> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, "atribuicao|funcao") == 0) {
    printf("Esperava o token <operador_atribuicao> ou <delimitador_parentese_aberto> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, "POSITIVO|NEGATIVO") == 0) {
    printf("Esperava o token <numero_positivo> ou <numero_negativo> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, "VERDADEIRO|FALSO") == 0) {
    printf("Esperava o token <verdadeiro> ou <falso> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, "IDENTIFICADOR|NUMERO|BOOL|PA") == 0) {
    printf("Esperava o token <identificador> ou <numero_positivo> ou <numero_negativo> ou <verdadeiro> ou <falso> ou <delimitador_parentese_aberto> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __SE__) == 0) {
    printf("Esperava o token <se> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, "RELACAO") == 0) {
    printf("Esperava o token <operador_comparacao> ou <operador_diferenciacao> ou <operador_menor> ou <operador_menor_igual> ou <operador_maior> ou <operador_maior_igual> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __ENTAO__) == 0) {
    printf("Esperava o token <entao> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __FIMSE__) == 0) {
    printf("Esperava o token <fimse> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __ENQUANTO__) == 0) {
    printf("Esperava o token <enquanto> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __FACA__) == 0) {
    printf("Esperava o token <faca> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __FIMENQUANTO__) == 0) {
    printf("Esperava o token <fimenquanto> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, __FIMPROGRAMA__) == 0) {
    printf("Esperava o token <fimprograma> mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado, "EOF") == 0) {
    printf("Esperava o fim do arquivo, mas encontrou %s\n", getErrorToken(encontrado));
  } else if (strcmp(esperado , "IDENTIFICADOR|NUMERO|BOOL") == 0) {
  	printf("Esperava o token <identificador> ou <numero_positivo> ou <numero_negativo> ou <verdadeiro> ou <falso>, mas encontrou %s\n", getErrorToken(encontrado));
	} else {
    printf("Esperava o token <%s> mas encontrou %s\n", esperado, getErrorToken(encontrado));
  }

  exit(0); /* para matar as chamads recursivas e sair do programa. */
}

char* getErrorToken(char* encontrado) {
  char* token ;
  token = malloc(40 * sizeof(char));
  strcpy(token, encontrado);

  if (strcmp(encontrado, __PROGRAMA__) == 0) {
    strcpy(token, "<programa>");
  } else if (strcmp(encontrado, __IDENTIFICADOR__) == 0) {
    strcpy(token, "<identificador>");
  } else if (strcmp(encontrado, __DELIMITADOR_PONTO_VIRGULA__) == 0) {
    strcpy(token, "<delimitador_ponto_virgula>");
  } else if (strcmp(encontrado, __INTEIRO__) == 0) {
    strcpy(token, "<inteiro>");
  } else if (strcmp(encontrado, __BOOLEANO__) == 0) {
    strcpy(token, "<booleano>");
  } else if (strcmp(encontrado, __DELIMITADOR_PA_ABERTO__) == 0) {
    strcpy(token, "<delimitador_parentese_aberto>");
  } else if (strcmp(encontrado, __DELIMITADOR_PA_FECHADO__) == 0) {
    strcpy(token, "<delimitador_parentese_fechado>");
  } else if (strcmp(encontrado, __FIMPROCEDIMENTO__) == 0) {
    strcpy(token, "<fimprocedimento>");
  } else if (strcmp(encontrado, __DELIMITADOR_VIRGULA__) == 0) {
    strcpy(token, "<delimitador_virgula>");
  } else if (strcmp(encontrado, __OPERADOR_ATRIBUICAO__) == 0) {
    strcpy(token, "<operador_atribuicao>");
  } else if (strcmp(encontrado, __NUMERO_POSITIVO__) == 0) {
    strcpy(token, "<numero_positivo>");
  } else if (strcmp(encontrado, __NUMERO_NEGATIVO__) == 0) {
    strcpy(token, "<numero_negativo>");
  } else if (strcmp(encontrado, __VERDADEIRO__) == 0) {
    strcpy(token, "<verdadeiro>");
  } else if (strcmp(encontrado, __FALSO__) == 0) {
    strcpy(token, "<falso>");
  } else if (strcmp(encontrado, __SE__) == 0) {
    strcpy(token, "<se>");
  } else if (strcmp(encontrado, __OPERADOR_COMPARACAO__) == 0) {
    strcpy(token, "<operador_comparacao>");
  } else if (strcmp(encontrado, __OPERADOR_DIFERENCIACAO__) == 0) {
    strcpy(token, "<operador_diferenciacao>");
  } else if (strcmp(encontrado, __OPERADOR_MENOR__) == 0) {
    strcpy(token, "<operador_menor>");
  } else if (strcmp(encontrado, __OPERADOR_MENOR_IGUAL__) == 0) {
    strcpy(token, "<operador_menor_igual>");
  } else if (strcmp(encontrado, __OPERADOR_MAIOR_IGUAL__) == 0) {
    strcpy(token, "<operador_maior_igual>");
  } else if(strcmp(encontrado, __OPERADOR_MAIOR__) == 0) {
    strcpy(token, "<operador_maior>");
  } else if (strcmp(encontrado, __ENTAO__) == 0) {
    strcpy(token, "<entao>");
  } else if (strcmp(encontrado, __FIMSE__) == 0) {
    strcpy(token, "<fimse>");
  } else if (strcmp(encontrado, __ENQUANTO__) == 0) {
    strcpy(token, "<enquanto>");
  } else if (strcmp(encontrado, __FACA__) == 0) {
    strcpy(token, "<faca>");
  } else if (strcmp(encontrado, __FIMENQUANTO__) == 0) {
    strcpy(token, "<fimenquanto>");
  } else if (strcmp(encontrado, __FIMPROGRAMA__) == 0) {
    strcpy(token, "<fimprograma>");
  }else if( strcmp(encontrado, __PROCEDIMENTO__ ) == 0 ){
  	strcpy(token, "<procedimento>");
  }else if( strcmp(encontrado, __SENAO__ ) == 0 ){
  	strcpy(token, "<senao>");
  }else if( strcmp(encontrado, __ESCREVA__ ) == 0 ){
  	strcpy(token, "<escreva>");
  }else if( strcmp(encontrado, __OPERADOR_SUBTRACAO__ ) == 0 ){
  	strcpy(token, "<operador_subtracao>");
  }else if( strcmp(encontrado, __OPERADOR_ADICAO__ ) == 0 ){
  	strcpy(token, "<operador_adicao>");
  }else if( strcmp(encontrado, __OPERADOR_DIVISAO__ ) == 0 ){
  	strcpy(token, "<operador_divisao>");
  }else if( strcmp(encontrado, __OPERADOR_MULTIPLICACAO__ ) == 0 ){
  	strcpy(token, "<operador_multiplicacao>");
  }else if( strcmp(encontrado, __PROCEDIMENTO__ ) == 0 ){
  	strcpy(token, "<__DELIMITADOR_DOIS_PONTOS>");
  }else if( strcmp(encontrado, __EOF__ ) == 0 ){
  	strcpy(token, "<fim_do_arquivo>");
  }
  return token;
}
