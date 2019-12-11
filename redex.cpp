/************************************************
*
*			HECHO POR ANTHONY BENAVIDES ARCE
*
***************************************************/


#include <iostream>
#include <string>
#include <regex>

using namespace std;

void reconocerIp(string& cadena){
	regex r("([1-2]?[0-9]{1,2}\\.){3}[1-2]?[0-9]{1,3}");
	if( regex_match(cadena, r) )
		cout << "ES UN IP" << endl;
	else
		cout << "NO ES UN IP" << endl;
}

void reconocerVariable(string& cadena){
	regex r("_?[a-zA-Z][a-zA-Z0-9_]*");
	if( regex_match(cadena, r) )
		cout << "ES UNA VARIABLE" << endl;
	else
		cout << "NO ES UNA VARIABLE" << endl;
}


int main() {
	//string cadena("492.168.152.8");
	//reconocerIp(cadena);
	
	string cadena("_ab34cfg");
	reconocerVariable(cadena);
	
	
	
	
	return 0;
}
