/*************************************************
*
*	INTEGRANTES:
*
*	ANTHONY BENAVIDES ARCE
*	FABIO SOTO MEJIA
*
*
*
***************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "EstadoCompilador.cpp"
using namespace std;

typedef map<string,string>::iterator iter;

class Analizador{
public:	
	vector<EstadoCompilador*> chart;
	
	Analizador(){}
	
	vector<EstadoCompilador*> run(EstadoCompilador* S, Gramatica* gram ,string entrada){
		
	}	
};









