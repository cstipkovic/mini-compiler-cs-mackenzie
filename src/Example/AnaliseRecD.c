#include<stdio.h>
#include<stdlib.h>

/*
 * S -> aBc$
 * B -> bB | e
 *
 */
char lookahead;

int  match(char t, char palavra[], int *pos){
	if (lookahead == t){
		lookahead= palavra[++(*pos)];
		return(1);
	}
	return(0);  
}

int S(char palavra[], int *pos){
	if (lookahead == 'a'){
		if (match('a', palavra, pos)  &&
		    B(palavra, pos)           &&
		    match('c', palavra, pos)  &&
	   	    match('$', palavra, pos)  )
	   	return(1);
	}
	return(0);
}

int B(char palavra[], int *pos){
	if (lookahead == 'b'){
		if (match('b', palavra, pos) &&
		    B(palavra, pos)          )
	   	return(1);
	} else return(1);
}

void trataErro(){
	printf("\n\nERRO DE SINTAXE\n\n");
	/* Faca um tratamento melhor */
}

int main(){
	char palavra[]= "ac$";
	int  pos=0;
	
	lookahead= palavra[pos];
	if (S(palavra, &pos))
	    printf("\nPalavra %s reconhecida\n", palavra);
	else 
	    trataErro();
	system("PAUSE");
	return(0);
	
}

