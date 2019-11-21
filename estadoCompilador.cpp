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
	string operacion;
	
	EstadoCompilador(Produccion *produccionRef_, int posAsterico_, int posPalabra_, EstadoCompilador *origen_, string operacion_){
		produccionRef = produccionRef_;
		posAsterico = posAsterico_;
		posPalabra = posPalabra_;
		origen = origen_;
		operacion = operacion_;
	}
};

class Accion {
public:
	Gramatica *gram;
	virtual bool sePuedeAplicar(EstadoCompilador *estado, vector<string> entrada) = 0;
	virtual bool aplica(EstadoCompilador *estado, vector<EstadoCompilador*> &chart, vector<string> entrada, map<string,string> contexto) = 0;
	
	Accion(Gramatica *gram_): gram(gram_){}
};

class Dummy : public Accion{
public:
	Dummy(Gramatica *gram_):Accion(gram_){}
	
	bool sePuedeAplicar(EstadoCompilador *estado, vector<string> entrada){return true;}
	
	bool aplica(EstadoCompilador *estado, vector<EstadoCompilador*> &chart, vector<string> entrada, map<string,string> contexto){
		//crear origen de la gramatica
		ProdContexto newContexto("S");
		string prodDerecha = gram->producciones[0].izq.nombre; 
		Produccion *pr_temp = new Produccion(newContexto, prodDerecha);
		
		//Inicializar estado
		estado = new EstadoCompilador(pr_temp,0,0,nullptr,"Dummy");
		
		//anadir al chart
		chart.push_back(estado);
	}
};

class Expandir : public Accion{
public:
	Expandir(Gramatica *gram_):Accion(gram_){}
	
	bool sePuedeAplicar(EstadoCompilador *estado, vector<string> entrada){
		int pos = estado->posAsterico;
		if(estado->produccionRef)estado->produccionRef->print();
		else cout << "nulooo" << endl;
		return !gram->isTerminal( estado->produccionRef->der[pos] );
	}
	
	bool aplica(EstadoCompilador *estado, vector<EstadoCompilador*> &chart, vector<string> entrada, map<string,string> contexto){
		
		string izq = estado->produccionRef->der[estado->posAsterico];
		vector<Produccion*> producciones= gram->getProduccion(izq);
		for(int i = 0; i< producciones.size(); ++i){
			EstadoCompilador *temp = new EstadoCompilador(producciones[i], 0, estado->posPalabra, estado, "Expandir");
			chart.push_back(temp);
		}
	}
};



class Unificar : public Accion
{
public:
	Unificar(Gramatica *gram_): Accion(gram_){}
	
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
public:
	Aceptar(Gramatica *gram_): Accion(gram_){}
	
	bool sePuedeAplicar(EstadoCompilador *estado, vector<string> entrada){
		int pos = estado->posAsterico;
		return gram->isTerminal( estado->produccionRef->der[pos] );
	}
	
	bool aplica(EstadoCompilador *estado, vector<EstadoCompilador*> &chart, vector<string> entrada, map<string,string> contexto){
		Unificar uni(gram);
		if(uni.sePuedeAplicar(estado, entrada) && uni.aplica(estado, chart,entrada,contexto)){
			estado->posAsterico++;
			estado->posPalabra++;
		}
	}
};








