#include <bits/stdc++.h> //import every standard library

using namespace std;

typedef vector<string> VS;

void tsolve(){
  int n; cin>>n;
  string sol="*";
  for(int i=0;i<n;++i){
  	string p; cin>>p;
  	string tmp="";
  	VS pieces;
  	for(int i=0;i<p.length();++i){
  	  if(p[i]!='*') tmp+= p[i];
  	  else {pieces.push_back(tmp); tmp="";}
  	}
  }
}

void solve(){
  int t; cin>>t;
  for(int i=0;i<t;++t){
  	cout << "Case #" << i+1 << ": ";
  	tsolve();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}