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
	
	vector<EstadoCompilador*> run(EstadoCompilador* S, Gramatica* gram ,vector<string> entrada){
		vector<EstadoCompilador*> chart;
		map<string,string> contexto;
		int indiceChart = 0;
		EstadoCompilador* EstadoActual;
		
		//Inicializar Acciones
		Dummy dum(gram);
		Expandir expand(gram);
		Unificar unificar(gram);
		Aceptar aceptar(gram);
		
		//Accion Dummy, no se usa ni entrada ni contexto(estan solo por el metodo virtual de Accion)		
		dum.aplica(S, chart,entrada,contexto);
		
		
		
		while(indiceChart < chart.size()){
			EstadoActual = chart[indiceChart];
			
			//Condicion de parada				
			if(EstadoActual->posPalabra == entrada.size() && EstadoActual->posAsterico == EstadoActual->produccionRef->der.size() && EstadoActual == S){
				break;
			}
			
			if(expand.sePuedeAplicar(EstadoActual,entrada)){
				expand.aplica(EstadoActual, chart,entrada,contexto);
			}
			if(unificar.sePuedeAplicar(EstadoActual,entrada)){
				unificar.aplica(EstadoActual, chart,entrada,contexto);
			}
			if(aceptar.sePuedeAplicar(EstadoActual,entrada)){
				aceptar.aplica(EstadoActual, chart,entrada,contexto);
			}
		}
		
		if(indiceChart >= chart.size()){
			chart.clear();
		}
		return chart;
	}	
};









