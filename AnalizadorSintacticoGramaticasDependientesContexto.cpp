#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <map>
using namespace std;

typedef map<string,string>::iterator iter;
	
void print(vector<vector<string>> toPrint){
	cout << endl << "Producciones: " << endl;
	for(int i = 0; i < toPrint.size(); ++i){
		for(int j = 0; j < toPrint[i].size(); ++j){
			cout << toPrint[i][j] << "\t";
		}
		cout << endl;
	}
}


class ProdContexto {
public:
	string nombre;
	map<string,string> contexto;
	ProdContexto(string& nombre_, map<string,string>& contexto_):nombre(nombre_), contexto(contexto_){}
};
/*
ProdContexto getContexto(string izq){
	size_t pos1 = izq.find("[");
	size_t pos2 = izq.find("=");
	size_t pos3 = izq.find("]");
	
	string nombre = izq.substr(0,pos1);
	pos1+=1;
	string firstMap = izq.substr(pos1,pos2-pos1);
	pos2+=1;
	string SecondMap = izq.substr(pos2, pos3-pos2);
	
	map<string,string> mapita;
	mapita[firstMap]=SecondMap;
	
	return  ProdContexto(nombre,mapita);
}
*/
ProdContexto getContexto(string izq){
	map<string,string> mapita;
	size_t pos1, pos2, pos3;
		
	pos1 = pos3 = izq.find("[");
	
	string nombre = izq.substr(0,pos1);
	
	cout << endl << "GramIzq: " << izq << endl;
	cout << "Nombre: " << nombre << endl;
	
	while(++pos3 < izq.size()){
		pos1 = pos3;
		pos2 = izq.find("=",pos3)+1;
		pos3 = izq.find(",",pos3);
		if(pos3>izq.size()) 
			pos3 = izq.find("]");
		
		string firstMap = izq.substr(pos1,pos2-pos1-1);
		string SecondMap = izq.substr(pos2,pos3-pos2);
		
		mapita[firstMap]=SecondMap;
		cout << "Contexto: " << firstMap << "->" << SecondMap << endl;
	}
	
	return  ProdContexto(nombre,mapita);
}


class Produccion{
public:
	ProdContexto izq;
	vector<string> der;
	Produccion(ProdContexto izq_, vector<string> der_): izq(izq_), der(der_){}
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
	ProdContexto contexto_izq = getContexto(izq);
	
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
				result.push_back(producciones[i].der);
		}
			
	}
	return result;
}

void Gramatica::read(string texto){	
	stringstream ss(texto);
	string izq,igual,aux;
	
	ss >> izq;
	ProdContexto contexto = getContexto(izq);
	
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
			producciones.push_back(Produccion(contexto,der));
			der.clear();
		}
	}
	producciones.push_back(Produccion(contexto,der));
}


int main(int argc, char *argv[]) {
	Gramatica gram;
	gram.read("Sustantivo[gen=f] := Det[gen=?g] Sustantivo[gen=?g]");
	gram.read("Det[gen=f] := la");
	gram.read("Det[gen=m] := el");
	gram.read("Sustantivo[gen=f] := ninha");
	gram.read("Sustantivo[gen=m,numero=plural] := ninhos");
	gram.read("Sustantivo[gen=m,numero=singular] := ninho");
	print(gram.getProduccion("Sustantivo[gen=m,numero=plural]"));
	
	return 0;
}

