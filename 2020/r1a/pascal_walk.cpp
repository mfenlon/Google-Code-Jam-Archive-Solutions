//Runtime Error

#include <bits/stdc++.h> //import every standard library

using namespace std;

void walkTheEdges(int n,int row,bool left){
  if(left){
	  for(int i=0;i<n;++i){
	  	cout << row << " 1" << '\n';
	  	++row;
	  }
  }
  else{
  	for(int i=0;i<n;++i){
  	  cout << row << ' ' << row << '\n';
  	  ++row;
  	}
  }
  cout << flush;
}

string trim(string bstring){
	for(int i=0;i<1000;++i){
		if(bstring[i]=='0') bstring=bstring.substr(i+1);
		else return bstring;
	}
	return bstring;
}

void tsolve(){
  int n; cin>>n;
  if(n<=30){
  	walkTheEdges(n,1,true);
  	return;
  }
  int tmpn=n-30;
  bitset<32> b(tmpn);
  string bstring=b.to_string();
  bool left=true;
  bstring=trim(bstring);
  int skip=0;
  int row=1;
  for(int i=bstring.length()-1;i>=0;--i){
  	if(bstring[i]=='0') {
  		if(left) cout << row << " 1" << '\n';
  		else cout << row << ' ' << row << '\n';
  		++skip;
  		++row;
  	}
  	else{
  	  if(left){
	    for(int i=0;i<row;++i) cout << row << ' ' << i+1 << '\n';
	    left=false;
  	  }
  	  else{
  	    for(int i=row;i>0;--i){
  	      cout << row << ' ' << i << '\n';
  	    }
  	    left=true;
  	  }
  	  ++row;
  	}
  }
  walkTheEdges(30-skip,row,left);
}

void solve(){
  int t; cin>>t;
  for(int i=0;i<t;++i){
  	cout << "Case #" << i+1 << ":" << '\n';
  	tsolve();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}
