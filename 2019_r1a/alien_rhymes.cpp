#include <bits/stdc++.h> //import every standard library

using namespace std;

int main() {
  //ios::sync_with_stdio(false); //allow c++ streams to buffer I/O independently from C streams
  //cin.tie(0);
  int T; cin >> T;
  for(int i=0;i<T;i++){
  	int n; cin >> n;
  	string word;
  	map<string,set<string>> m;
  	set<string> keys;
  	for(int j=0;j<n;j++){
  		cin >> word;
  		char c = word[word.length()-1];
  		string l(1,c);
  		keys.insert(l);
  		m[l].insert(word);
  	}
  	while(!keys.empty()){
  		set<string>::iterator it = keys.begin();
  		string next_key = *it;
  		set<string> eraseMe;
  		if(m[next_key].size()>1){
  			for(auto w1 : m[next_key]){
	  			for(auto w2 : m[next_key]){
	  				if(w1!=w2 && w1[w1.length()-next_key.length()-1]==w2[w2.length()-next_key.length()-1]){
	  					string new_key = w1[w1.length()-next_key.length()-1] + next_key;
	  					if(m[new_key].find(w1)==m[new_key].end() && m[new_key].find(w2)==m[new_key].end()){
		  					m[new_key].insert(w1);
		  					m[new_key].insert(w2);
		  					eraseMe.insert(w1);
		  					eraseMe.insert(w2);
		  					keys.insert(new_key);
		  				}
	  				}
	  			}
	  		}
	  	}
  		keys.erase(next_key);
  		for(auto e : eraseMe) m[next_key].erase(e);
  	}
  	int r=0;
  	map<string,set<string>>::iterator it=m.begin();
  	while(it!=m.end()){
  		set<string> s=it->second;
  		if(s.size()>1) r+=2;
  		++it;
  	}
  	cout << "Case #" << i+1 << ": " << r << endl;
  }
}

//currently failing on the larger test set
