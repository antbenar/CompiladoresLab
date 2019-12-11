/**************************************
*
*			HECHO POR ANTHONY BENAVIDES
*
*
***************************************/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "analizadorLexico.cpp"
using namespace std;

typedef pair<int,int> Coord;


Coord getEXPR1(vector<Token*>& tokens, int start, int last);
Coord getEXPR2(vector<Token*>& tokens, int start, int last);
Coord getEXPR3(vector<Token*>& tokens, int start, int last);
Coord getEXPR(vector<Token*>& tokens, int start, int last);
Coord getIGUALDAD(vector<Token*>& tokens, int start, int last);
Coord getCOM( vector<Token*>& tokens );

Coord getEXPR3(vector<Token*>& tokens, int start, int last){
	if(start == last){
		if(tokens[start]->variable == 'E' || tokens[start]->variable == 'V')
			return make_pair(start,last);
	}
	
	return make_pair(-1,-1);
}


Coord getEXPR1(vector<Token*>& tokens, int start, int last){
	for(int i=start; i<last; ++i){
		if(tokens[i]->variable == 'O'){
			Coord expr = getEXPR(tokens, start, i-1);
			if( expr.first != -1 ){
				Coord expr2 = getEXPR(tokens, i+1, last);
				if( expr2.first != -1 )
					return make_pair(start,last);
			}
		}
	}
	
	return make_pair(-1,-1);
}


Coord getEXPR2(vector<Token*>& tokens, int start, int last){
	if( *(tokens[start]->data) == '(' && *(tokens[last]->data) == ')'){
		Coord expr = getEXPR(tokens, start+1, last-1);
		if( expr.first != -1 )
			return make_pair(start,last);
	}
	
	return make_pair(-1,-1);
}


Coord getEXPR(vector<Token*>& tokens, int start, int last){
	Coord expr1 = getEXPR1(tokens, start, last);
	if( expr1.first != -1 )
		return make_pair(start,last);
	
	Coord expr2 = getEXPR2(tokens, start, last);
	if( expr2.first != -1 )
		return make_pair(start,last);
	
	Coord expr3 = getEXPR3(tokens, start, last);
	if( expr3.first != -1 )
		return make_pair(start,last);
	
	return make_pair(-1,-1);
}

Coord getIGUALDAD(vector<Token*>& tokens, int start, int last){
	if(tokens[start]->variable == 'V' && tokens[start+1]->variable == 'I'){
		Coord expr = getEXPR(tokens, start+2, last);
		if( expr.first != -1 )
			return make_pair(start,last);
	}
	return make_pair(-1,-1);
}


Coord getCOM( vector<Token*>& tokens ){
	Coord expr = getEXPR(tokens, 0, tokens.size()-1);
	if( expr.first != -1)
		return expr;
	
	Coord igualdad = getIGUALDAD(tokens, 0, tokens.size()-1);
	if ( igualdad.first != -1 )
		return igualdad;
	
	return make_pair(-1,-1);
}



int main(int argc, char *argv[]) {
	char buffer[] = "temp = Temp1+_Tempp2 2";
	vector<Token*> tokens = analizadorLexico(buffer);
	
	for(int i = 0; i<tokens.size(); ++i)
		cout << *(tokens[i]->data) << " ";
	cout << endl;
	
	if(getCOM(tokens).first != -1) cout << "Gramatica reconocida" << endl;
	else cout << "No se pudo reconocer la gramática" << endl;
	
	return 0;
}















