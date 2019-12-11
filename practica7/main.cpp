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
#include "estadoCompilador.cpp"

using namespace std;



int main(int argc, char *argv[]) {
	Gramatica gram;
	gram.read("Sustantivo := Det[gen=?] Sustantivo[gen=?]");
	gram.read("Det[gen=f] := la");
	gram.read("Det[gen=m] := el");
	gram.read("Sustantivo[gen=f] := ninha | djdjd");
	gram.read("Sustantivo[gen=m,numero=plural] := ninhos");
	gram.read("Sustantivo[gen=m] := ninho");
	print(gram.terminales);
	print(gram.noterminales);
	return 0;
}
