//Incomplete

#include <bits/stdc++.h> //import every standard library

using namespace std;

void tsolve(){
  int r,c; cin>>r>>c;
  int f[r][c];
  for(int i=0;i<r;++i){
  	for(int j=0;j<c;++j){
  		cin>>f[i][j];
  		sum+=f[i][j];
  	}
  }
  bool another=true;
  while(another){
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
