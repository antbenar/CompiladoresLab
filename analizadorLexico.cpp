#include <iostream>
#include <stdio.h>
#include <vector>
#include <regex>
#define BUF_SIZE 1000
using namespace std;


void printChar(char* linea){
	for(; *linea!='\0'; linea++){
		cout << *linea;
	}cout << endl;
}

class Token{
public:
	char* data;
	int index;
	char variable; //E (entero), V (variable), O (operador), I(Igual), P(parentesis)
	Token(char* data_, int index_, char variable_): data(data_), index(index_), variable(variable_){}
};

char* reconocerNumero(char** linea, int& i){
	char* charIni;
	char* charFin;

	charIni = charFin = new char[BUF_SIZE];
	*charFin = **linea;
	charFin++;

	while( (*(*linea+1))!= '\0' && (*(*linea+1))-'0' < 10 && (*(*linea+1))-'0' >= 0){
		*charFin=*(*linea+1);
		++charFin;
		++(*linea);
	}

	*charFin ='\0';
	
	return charIni;
}


char* reconocerVariable(char** linea, int& i){
	char* charIni;
	char* charFin;
	
	charIni = charFin = new char[BUF_SIZE];
	*charFin = **linea;
	charFin++;
	
	while( (*(*linea+1))!= '\0' && ((*(*linea+1))-'a' < 26 && (*(*linea+1))-'a' >= 0) or (*(*linea+1))=='_' or ((*(*linea+1))-'A' < 26  && (*(*linea+1))-'A' >= 0) or ((*(*linea+1))-'0' < 10 && (*(*linea+1))-'0' >= 0) ){
		*charFin=*(*linea+1);
		++charFin;
		++(*linea);
	}
	
	*charFin ='\0';
	
	return charIni;
}


vector<Token*> analizadorLexico( char* linea ) {
	vector<Token*> tokens;
	
	for(int i = 0; *linea!='\0'; linea++, ++i){
		int i_cur = i;
		if(*linea == '='){
			tokens.push_back(new Token(&(*linea), i_cur, 'I'));
		}
		else if(*linea == '(' or *linea == ')'){
			tokens.push_back(new Token(&(*linea), i_cur, 'P'));
		}
		else if(*linea == '+' or *linea == '-' or *linea == '*' or *linea == '/'){
			//cout << "signo: " << *linea << endl;
			tokens.push_back(new Token(&(*linea), i_cur, 'O'));
		}
		else if((*linea)-'0' < 10  && (*linea)-'0' >= 0){
			char* token = reconocerNumero(&linea, i);
			//cout << "numero: "; printChar(token);
			tokens.push_back(new Token(token, i_cur, 'E'));
		}
		else if( ((*linea)-'a' < 26  && (*linea)-'a' >= 0) or (*linea)=='_' or ((*linea)-'A' < 26  && (*linea)-'A' >= 0)){
			char* token = reconocerVariable(&linea, i);
			//cout << "variable: "; printChar(token);
			tokens.push_back(new Token(token, i_cur, 'V'));
		}
	}
	return tokens;
}

