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
#include "Analizador.cpp"

using namespace std;

vector<string> reconocerEntrada(string s){
	vector<string> result;
	string aux;
	stringstream ss(s);
	
	while (ss >> aux)
	{
		result.push_back(aux);
	}
	return result;
}


int main(int argc, char *argv[]) {
	vector<string> entrada;
	string s;
	
	//---------crear Gramatica
	Gramatica* gram = new Gramatica;
	gram->read("Sustantivo := Det[gen=?] Sustantivo[gen=?]");
	gram->read("Det[gen=f] := la");
	gram->read("Det[gen=m] := el");
	gram->read("Sustantivo[gen=f] := ninha");
	gram->read("Sustantivo[gen=m] := ninho");
	//gram->read("Sustantivo[gen=m,numero=plural] := ninhos");
	//print(gram->terminales);
	//print(gram->noterminales);
	
	
	//----------reconocer oracion
	s = "el ninho";
	entrada = reconocerEntrada(s);
	//print(entrada);
	
	//----------crear analizador
	
	Analizador analizador;
	EstadoCompilador* estado = new EstadoCompilador(nullptr,0,0,nullptr,"");
	analizador.run(estado, gram, entrada);
	
	return 0;
}
