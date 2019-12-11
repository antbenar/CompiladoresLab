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
#include <stack>
#include <vector>
#include "gramatica.cpp"

using namespace std;

class EstadoCompilador {
public:
	Produccion *produccionRef;
	int posAsterico;
	int posPalabra;
	EstadoCompilador *origen;
	
	EstadoCompilador(Produccion *produccionRef_, int posAsterico_, int posPalabra_, EstadoCompilador *origen_){
		produccionRef = produccionRef_;
		posAsterico = posAsterico_;
		posPalabra = posPalabra_;
		origen = origen_;
	}
};

class Accion {
public:
	Gramatica *gram;
	virtual bool sePuedeAplicar(EstadoCompilador *estado) = 0;
	virtual bool aplica(EstadoCompilador *estado, vector<EstadoCompilador*> &chart) = 0;
	
	Accion(Gramatica *gram_): gram(gram_){}
};

class Dummy : public Accion{
	
	bool sePuedeAplicar(EstadoCompilador *estado){return true;}
	
	bool aplica(EstadoCompilador *estado, vector<EstadoCompilador*> &chart){
		//crear origen de la gramatica
		ProdContexto newContexto("S");
		string prodDerecha = gram->producciones[0].izq.nombre; 
		Produccion *pr_temp = new Produccion(newContexto, prodDerecha);
		
		//Inicializar estado
		estado = new EstadoCompilador(pr_temp,0,0,nullptr);
		
		//anadir al chart
		chart.push_back(estado);
	}
};

class Expandir : public Accion{
	
	bool sePuedeAplicar(EstadoCompilador *estado){
		int pos = estado->posAsterico;
		return !gram->isTerminal( estado->produccionRef->der[pos] );
	}
	
	bool aplica(EstadoCompilador *estado, vector<EstadoCompilador*> &chart){
		
		string izq = estado->produccionRef->der[estado->posAsterico];
		vector<Produccion> producciones= gram->getProduccion(izq);
		
		for(int i = 0; i< producciones.size(); ++i){
			EstadoCompilador *temp = new EstadoCompilador(&producciones[i], 0, estado->posPalabra, estado);
			chart.push_back(temp);
		}
	}
};



class Unificar : public Accion
{
	Unificar(Gramatica *gram_): gram(gram_){}
	
	bool sePuedeAplicar(EstadoCompilador *estado, vector<string> entrada){
		int pos = estado->posAsterico;
		return estado->produccionRef->der[pos] == entrada[estado->posPalabra];
	}
	
	bool aplica(EstadoCompilador *estado, vector<EstadoCompilador*> &chart, vector<string> entrada, map<string,string> contexto){
		string izq = estado->produccionRef[estado->posAsterico].izq.nombre;
		string palabra = entrada[estado->posPalabra];
		
		map<string,string> contextPalabra = gram->getContexto(izq,palabra);
		
		for( const auto &p : contextPalabra){
			if(contexto.find(p.first) == contexto.end()){
				contexto[p.first] = p.second;
			}
			else{
				if(contexto[p.first] == p.second){
					return true;
				}
				else{
					return false;
				}
			}
		}
		return true;
	}
};




class Aceptar : public Accion{
	
	bool sePuedeAplicar(EstadoCompilador *estado){
		int pos = estado->posAsterico;
		return gram->isTerminal( estado->produccionRef->der[pos] );
	}
	
	bool aplica(EstadoCompilador *estado, vector<EstadoCompilador*> &chart, string entrada, map<string,string> contexto){
		Unificar uni(gram);
		if(uni.sePuedeAplicar() && uni.aplica(estado, chart,entrada,contexto)){
			estado->posAsterico++;
			estado->posPalabra++;
		}
	}
};








