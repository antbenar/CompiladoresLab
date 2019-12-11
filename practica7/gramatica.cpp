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

using namespace std;

typedef map<string,string>::iterator iter;

//------------------------Producciones-------------------------------------------------------------//
class ProdContexto {
public:
	string nombre;
	map<string,string> contexto;
	ProdContexto();
	ProdContexto(string& nombre_, map<string,string>& contexto_):nombre(nombre_), contexto(contexto_){}
	ProdContexto(string nombre_):nombre(nombre_){}
};

ProdContexto setGetContexto(string izq){
	map<string,string> mapita;
	size_t pos1, pos2, pos3;
	
	pos1 = pos3 = izq.find("[");
	if(pos1 > izq.size())
		return ProdContexto(izq,mapita);
	
	string nombre = izq.substr(0,pos1);
	
	//cout << endl << "GramIzq: " << izq << endl;
	//cout << "Nombre: " << nombre << endl;
	
	while(++pos3 < izq.size()){
		pos1 = pos3;
		pos2 = izq.find("=",pos3)+1;
		pos3 = izq.find(",",pos3);
		if(pos3>izq.size())
			pos3 = izq.find("]");
		
		string firstMap = izq.substr(pos1,pos2-pos1-1);
		string SecondMap = izq.substr(pos2,pos3-pos2);
		
		mapita[firstMap]=SecondMap;
		//cout << "Contexto: " << firstMap << "->" << SecondMap << endl;
	}
	
	return ProdContexto(nombre,mapita);
}


class Produccion{
public:
	ProdContexto izq;
	vector<string> der;
	Produccion(ProdContexto izq_, vector<string> der_): izq(izq_), der(der_){}
	
	Produccion(ProdContexto izq_, string der_): izq(izq_){der.push_back(der_);}
};


//------------------------Gramatica-------------------------------------------------------------//

class Gramatica{
public:
	vector<Produccion> producciones;
	vector<string> terminales;
	vector<string> noterminales;
	
	vector<Produccion> getProduccion(string);
	void read(string);
	
	map<string,string> getContexto(string izq, string palabra);
	void addNoTerminal(string);
	void addTerminal(string);
	bool isTerminal(string);
};



vector<Produccion> Gramatica::getProduccion(string izq){
	vector<Produccion> result;
	ProdContexto contexto_izq = setGetContexto(izq);
	
	for(int i = 0; i < producciones.size(); ++i){
		if(producciones[i].izq.nombre == contexto_izq.nombre){
			map<string, string> map1 = producciones[i].izq.contexto;
			map<string, string> map2 = contexto_izq.contexto;
			bool valido;
			
			for (iter it2 = map2.begin(); it2!=map2.end(); ++it2){
				
				valido = false;
				for (iter it = map1.begin(); it!=map1.end(); ++it){
					if( it->first == it2->first && it->second == it2->second){
						valido = true;
					}
				}
				if(!valido) break;
			}
			
			if(valido)
				result.push_back(producciones[i]);
		}
		
	}
	return result;
}



void Gramatica::read(string texto){
	stringstream ss(texto);
	string izq,igual,aux;
	
	ss >> izq;
	ProdContexto contexto = setGetContexto(izq);
	addNoTerminal(contexto.nombre);
	
	ss >> igual;
	if(igual != ":=") {
		cout << "Error al reconocer la gramatica" << endl;
		return;
	}
	
	vector<string> der;
	while (ss >> aux)
	{
		ProdContexto contexto2 = setGetContexto(aux);//obtener el nomrbe del contexto
		der.push_back(contexto2.nombre);
		addTerminal(contexto2.nombre);//agregar el nuevo terminal
		
		if(aux == "|"){
			producciones.push_back(Produccion(contexto,der));
			der.clear();
		}
	}
	producciones.push_back(Produccion(contexto,der));
}


map<string,string> Gramatica::getContexto(string izq, string palabra){
	vector<Produccion> prod = getProduccion(izq);
	map<string,string> contextos;
	
	for(int i=0; prod.size(); ++i){
		for(int j=0; prod[i].der.size(); ++j){
			if(prod[i].der[j] == palabra)
				return prod[i].izq.contexto;
		}
	}
}



void Gramatica::addNoTerminal(string newNoTerminal){
	for(int i =0; i<noterminales.size(); ++i){
		if(noterminales[i] == newNoTerminal)
			return;
	}
	
	noterminales.push_back(newNoTerminal);
	
	//verificar que el nuevo no terminal no se encuentre en los terminales
	for (vector<string>::iterator it = terminales.begin() ; it != terminales.end(); ++it){
		if(*it == newNoTerminal){
			terminales.erase(it);
			return;
		}
	}
}



void Gramatica::addTerminal(string newTerminal){
	for(int i =0; i<terminales.size(); ++i){
		if(terminales[i] == newTerminal)
			return;
	}
	
	for(int i =0; i<noterminales.size(); ++i){
		if(noterminales[i] == newTerminal)
			return;
	}
	
	terminales.push_back(newTerminal);
}



bool Gramatica::isTerminal(string nombre){
	for(int i =0; i<terminales.size(); ++i){
		if(terminales[i] == nombre)
			return true;
	}
	return false;
}

	

//------------------Funciones Imprimir---------------------------------------------//
void print(vector<vector<string>> toPrint){
	for(int i = 0; i < toPrint.size(); ++i){
		for(int j = 0; j < toPrint[i].size(); ++j){
			cout << toPrint[i][j] << "\t";
		}
		cout << endl;
	}
}

void print(vector<string> toPrint){
	for(int i = 0; i < toPrint.size(); ++i){
		cout << toPrint[i] << "\t";
	}
	cout << endl;
}


