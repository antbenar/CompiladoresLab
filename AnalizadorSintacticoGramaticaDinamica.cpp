#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
using namespace std;

void print(vector<vector<string>> toPrint){
	for(int i = 0; i < toPrint.size(); ++i){
		for(int j = 0; j < toPrint[i].size(); ++j){
			cout << toPrint[i][j] << "\t";
		}
		cout << endl;
	}
}


class Produccion{
public:
	string izq;
	vector<string> der;
	Produccion(string izq_, vector<string> der_): izq(izq_), der(der_){}
};

class Gramatica{
public:
	vector<Produccion> producciones;
	set<string> terminales;
	set<string> noterminales;
	
	vector<vector<string>> getProduccion(string);
	void read(string);
};

vector<vector<string>> Gramatica::getProduccion(string izq){
	vector<vector<string>> result;
	for(int i = 0; i < producciones.size(); ++i){
		if(producciones[i].izq == izq)
			result.push_back(producciones[i].der);
	}
	return result;
}

void Gramatica::read(string texto){	
	stringstream ss(texto);
	string izq,igual,aux;
	
	ss >> izq;
	ss >> igual;
	if(igual != ":=") {
		cout << "error al reconocer la gramatica" << endl;
		return;
	}
	
	vector<string> der;
	while (ss >> aux) 
	{
		der.push_back(aux);
		if(aux == "|"){
			producciones.push_back(Produccion(izq,der));
			der.clear();
		}
	}
	producciones.push_back(Produccion(izq,der));
}


int main(int argc, char *argv[]) {
	Gramatica gram;
	gram.read("Ep := + T Ep");
	gram.read("Ep := - T Ep");
	gram.read("Ep := lambda");
	print(gram.getProduccion("Ep"));
	return 0;
}

