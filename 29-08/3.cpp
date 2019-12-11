#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

map<char, char> diccionario;

double convert( string a, char prefix){
	double num = atof(a.c_str());
	
	if(prefix == 'M'){
		num = num * 1000000;
	}
	if(prefix == 'k'){
		num = num * 1000;
	}
	if(prefix == 'm'){
		num = num * 0.001;
	}
	
	return num;
}

void resolve(string& a, int numProblem){
	map<char, double> variables;
	variables['P'] = 0;
	variables['I'] = 0;
	variables['U'] = 0;	
	
	string aux;
	char prefix;
	
	for(int i=0; i<a.size() ; ++i){
		aux = "";
		if(a[i] == '='){
			int j = i+1;
			while(a[j]!= diccionario[a[i-1]]){
				aux += a[j++];
			}
			
			if((int)aux[aux.size()-1]<58 && (int)aux[aux.size()-1]>47)
				prefix = 'p';
			else{
				prefix = aux[aux.size()-1];
				aux = aux.substr(0, aux.size()-1);
			}
			variables[a[i-1]] = convert(aux, prefix);
		}
	}
	
	
	cout << "Problem #" << numProblem << endl;
	
	cout << fixed;
	cout << setprecision(2);
	if(variables['P'] == 0)
		cout << variables['U'] * variables['I'] << diccionario['P'] << endl;
	if(variables['U'] == 0)
		cout << variables['P'] / variables['I'] << diccionario['U'] << endl;
	if(variables['I'] == 0)
		cout << variables['P'] / variables['U'] << diccionario['I'] << endl;
}

int main(){	
	diccionario['P'] = 'W';
	diccionario['I'] = 'A';
	diccionario['U'] = 'V';	
	
	string problem;
	int n;
	cin >> n;
	for (int i=1; i <= n; ++i){
		getline(cin, problem);
		resolve(problem, i);
	}
	
    return 0;
}



