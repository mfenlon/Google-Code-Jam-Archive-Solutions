//Adapted from Gennady Korotkevich's solution at:
//https://codingcompetitions.withgoogle.com/codejam/submissions/000000000019fd74/R2VubmFkeS5Lb3JvdGtldmljaA

//Look into 2 1 1 2

#include <bits/stdc++.h> //import every standard library

using namespace std;

typedef vector<int> VI;
typedef vector<vector<int>> VVI;

void tsolve(){
  int h,w; cin >> h >> w;
  VVI f(h,VI(w));
  for(int i=0;i<h;++i){
    for(int j=0;j<w;++j){
      cin >> f[i][j];
    }
  }
  VVI when(h,VI(w,-1));
  VVI up(h,VI(w));
  VVI down(h,VI(w));
  VVI left(h,VI(w));
  VVI right(h,VI(w));
  set<pair<int,int>> check;

  for(int i=0;i<h;++i){
    for(int j=0;j<w;++j){
      up[i][j]=i-1;
      down[i][j]=i+1;
      left[i][j]=j-1;
      right[i][j]=j+1;
      check.insert(make_pair(i,j));
    }
  }
  int rd=0;
  while(check.size()!=0){
    set<pair<int,int>> new_check=check;
    check.clear();
    ++rd;
    for(auto& p : new_check){
      int r=p.first, c=p.second;
      int neighbors=0;
      int totskill=0;
      float avgskill=0;
      if(up[r][c]!=-1) {totskill+=f[up[r][c]][c]; ++neighbors;}
      if(down[r][c]!=h) {totskill+=f[down[r][c]][c]; ++neighbors;}
      if(left[r][c]!=-1) {totskill+=f[r][left[r][c]]; ++neighbors;}
      if(right[r][c]!=w) {totskill+=f[r][right[r][c]]; ++neighbors;}
      if(neighbors>0) avgskill=(float)totskill/(float)neighbors;
      if(avgskill>(float)f[r][c]){
        when[r][c]=rd;
        if(right[r][c]!=w) left[r][right[r][c]]=left[r][c];
        if(left[r][c]!=-1) right[r][left[r][c]]=right[r][c];
        if(down[r][c]!=h) up[down[r][c]][c]=up[r][c];
        if(up[r][c]!=-1) down[up[r][c]][c]=down[r][c];
        if(up[r][c]!=-1) check.insert(make_pair(up[r][c],c));
        if(down[r][c]!=h) check.insert(make_pair(down[r][c],c));
        if(left[r][c]!=-1) check.insert(make_pair(r,left[r][c]));
        if(right[r][c]!=w) check.insert(make_pair(r,right[r][c]));
      }
    }
  }
  long long total=0;
  for(int i=0;i<h;++i){
    for(int j=0;j<w;++j){
      if(when[i][j]==-1) when[i][j]=rd;
      total+=f[i][j]*when[i][j];
    }
  }
  cout << total << '\n';
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
