#include <iostream>

using namespace std;

bool esVocal(char& a){
	if(a == 'a' or a == 'e' or a == 'i' or a == 'o' or a == 'u') return true;
	return false;
}


void resolve(string& a, string& b){
	string aux = "";
	
	if( a.substr(a.size()-2) == "ar" ){
		aux = a.substr(0,a.size()-2) + "ando";
	}
	if( esVocal(a[a.size()-3]) ){	//verificar si es focal la antepenultima letra
		if( a.substr(a.size()-2) == "er" or a.substr(a.size()-2) == "ir" ){
			aux = a.substr(0,a.size()-2) + "yendo";
	}
	else if( a.substr(a.size()-2) == "er" or a.substr(a.size()-2) == "ir"){
		aux = a.substr(0,a.size()-2) + "iendo";
	}
	
	//casos especiales
	if(a == "reir") aux = "riendo";
	
	if(aux == b) cout << "SI" << endl;
	else cout << "NO" << endl;
}

int main(){	
	string a, b;
	while(true){
		cin >> a >> b;
		resolve(a, b);
	}
	
    return 0;
}
