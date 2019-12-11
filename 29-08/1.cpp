#include <iostream>
#include <stack> 

using namespace std;

void resolve(string& a){
	stack <char> s;
	
	for(int i =0; i<a.size() ; ++i){
		if(s.empty()) s.push(a[i++]);
		
		if(s.top() == '[' and a[i] == ']'){
			s.pop();
		}
		else if(s.top() == '(' and a[i] == ')'){
			s.pop();
		}
		else s.push(a[i]);
	}
	if(s.empty()) cout << "SI" << endl;
	else cout << "NO" << endl;
}


int main(){
	string a;
	while(true){
		cin >> a;
		resolve(a);
	}

    return 0;
}
