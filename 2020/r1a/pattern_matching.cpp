//Pattern Matching can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b3034

#include <bits/stdc++.h> //import every standard library

using namespace std;

typedef vector<string> VS;

void addToSuffixVec(VS& sv,string& ls,int& ss,string& s){
  if(s.length()>ss){
    ls=s;
    ss=s.length();
  }
  sv.push_back(s);
}

void addToPrefixVec(VS& pv,string& lp,int& ps,string& s){
  if(s.length()>ps){
    lp=s;
    ps=s.length();
  }
  pv.push_back(s);
}

string getPrefix(VS& pv,string& lp){
  for(int i=0;i<pv.size();++i){
    string pre=pv[i];
    for(int j=0,k=0;j<pre.length();++j,++k){
      if(pre[j]=='*') break;
      else if(pre[j]!=lp[k]) return "0";
    }
  }
  return lp;
}

string getSuffix(VS& sv,string& ls,int& ss){
  for(int i=0;i<sv.size();++i){
    string suf=sv[i];
    for(int j=suf.length()-1,k=ss-1;j>=0;--j,--k){
      if(suf[j]=='*') break;
      else if(suf[j]!=ls[k]) return "0";
    }
  }
  return ls;
}

void tsolve(){
  int n; cin>>n;
  VS sv;
  VS pv;
  int ss=0,ps=0;
  string ls="",lp="",middleWord="";
  for(int i=0;i<n;++i){
    string s; cin>>s;
    int j=0,k=s.length()-1;
    while(s[j]!='*') ++j;
    string pres=s.substr(0,j+1);
    addToPrefixVec(pv,lp,ps,pres);
    while(s[k]!='*') --k;
    string sufs=s.substr(k,s.length()-k);
    addToSuffixVec(sv,ls,ss,sufs);
    for(;j<k;++j){
      if(s[j]!='*') middleWord+=s[j];
    }
  }
  string prefix=getPrefix(pv,lp);
  string suffix=getSuffix(sv,ls,ss);
  if(prefix=="0" || suffix=="0") cout << '*' << '\n';
  else cout << prefix.substr(0,prefix.length()-1) << middleWord << suffix.substr(1) << '\n';
}

void solve(){
  int t; cin>>t;
  for(int i=0;i<t;++i){
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