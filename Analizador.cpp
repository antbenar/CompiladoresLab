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

void printChart(vector<EstadoCompilador*>& chart){
	cout << "|Indice\t|EstadoChart\t\t\t|EstadoReferencia\t\t|Operacion|" << endl;
	for(int i = 0; i<chart.size(); ++i){
		cout << "|" << i << "\t|";
		chart[i]->produccionRef->print(chart[i]->posAsterico); cout << "\t|";
		if(chart[i]->origen) {chart[i]->origen->produccionRef->print(0); cout << "\t|";}
		else cout << "\t\t\t|";
		cout << chart[i]->operacion << "\t|";
		cout << endl;
	}
}



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
		
		cout << "dummy aplico" << endl;
		printChart(chart);
		while(indiceChart < chart.size()){
			EstadoActual = chart[indiceChart];
			//Condicion de parada				
			if(EstadoActual->posPalabra == entrada.size() && EstadoActual->posAsterico == EstadoActual->produccionRef->der.size() && EstadoActual == S){
				cout << "cerro bucle" << endl;
				break;
			}
			cout << "va a entrar expandir" << endl;
			if(expand.sePuedeAplicar(EstadoActual,entrada)){
				cout << "expandir" << endl;
				expand.aplica(EstadoActual, chart,entrada,contexto);
				cout << "expandir aplico" << endl;
			}
			cout << "a" << endl;
			if(unificar.sePuedeAplicar(EstadoActual,entrada)){
				cout << "unificar" << endl;
				unificar.aplica(EstadoActual, chart,entrada,contexto);
				cout << "unificar acabo" << endl;
			}
			cout << "b" << endl;
			if(aceptar.sePuedeAplicar(EstadoActual,entrada)){
				cout << "aceptar" << endl;
				aceptar.aplica(EstadoActual, chart,entrada,contexto);
				cout << "aplica acabo" << endl;
			}
			++indiceChart;
			printChart(chart);
		}
		
		//verificar si es que hay esa oracion en la gramatica
		if(indiceChart >= chart.size()){//si no se encontro
			chart.clear();
		}

		return chart;
	}	
};









