
//Adapted from Gennady Korotkevich's solution at:
//https://codingcompetitions.withgoogle.com/codejam/submissions/000000000019fd74/R2VubmFkeS5Lb3JvdGtldmljaA

//Square Dance can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b1355

/**********
* Square Dance relies on repeatedly checking contestants to determine if they have been eliminated each round.
* However, for larger test sets, checking each square on the dance floor each round becomes too slow
* to meet the time constraints. Instead, we follow this logic:
*
* - We first must determine which contestants are going to be eliminated in Round 1. This takes O(N) time.
* - For every round after Round 1, we only check contestants adjacent to those who were eliminated in the
*   previous round
*
* The reason for the second point is as follows: if a contestant is not eliminated during a round, and none
* of their cardinal neighbors gets eliminated during that round, then the average skill level at the contestant's
* location does not change. Therefore, contestant will not be eliminated in the following round.
*
* In order to solve the problem, we need to create several grids:
* 1) Floor - Each square on the floor will tell us the contestant's skill level
* 2) When - Each square in When will tell us the round in which the corresponding contestant is eliminated
* 3-4) Up/Down - Each square in Up/Down will tell us in which row the adjacent contestant resides
* 5-6) Left/Right - Each square in Left/Right will tell us in which column the adjacent contestant resides
*
* Now that we have our structures set, running the rounds is simple. We check if each contestant of interest
* will be eliminated in the coming round. If they are, then we update their neighbors' adjacent contestants
* and add the neighbors to our list of contestants that we will check in the following round. If, at the
* beginning of a round, there are no contestants to check, then we have reached the end of our contest.
* We use our Floor and our When grids to then calculate the total interest of the contest.
**********/

#include <bits/stdc++.h> //import every standard library

using namespace std;

typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef long long ll;

void tsolve(){              //Solve each test case
  int h,w; cin >> h >> w;
  VVI f(h,VI(w));
  for(int i=0;i<h;++i){
    for(int j=0;j<w;++j){
      cin >> f[i][j];       //Populate our Floor grid with skill levels
    }
  }
  VVI when(h,VI(w,-1));            //Set up appropriate grids
  VVI up(h,VI(w));
  VVI down(h,VI(w));
  VVI left(h,VI(w));
  VVI right(h,VI(w));
  set<pair<int,int>> check;

  for(int i=0;i<h;++i){           //Populate grids
    for(int j=0;j<w;++j){
      up[i][j]=i-1;
      down[i][j]=i+1;
      left[i][j]=j-1;
      right[i][j]=j+1;
      check.insert(make_pair(i,j));
    }
  }
  int rd=0;
  while(check.size()!=0){            //For all rounds after Round 1, check every contestant that is 
    set<pair<int,int>> elims;        //next to a contestant who got eliminated in the previous round
    set<pair<int,int>> new_check=check;
    check.clear();
    ++rd;
    for(auto& p : new_check){
      int r=p.first, c=p.second;
      int neighbors=0;
      int totskill=0;
      float avgskill=0;
      if(up[r][c]!=-1) {totskill+=f[up[r][c]][c]; ++neighbors;}             //Calculate the average total skill of adjacent contestants
      if(down[r][c]!=h) {totskill+=f[down[r][c]][c]; ++neighbors;}
      if(left[r][c]!=-1) {totskill+=f[r][left[r][c]]; ++neighbors;}
      if(right[r][c]!=w) {totskill+=f[r][right[r][c]]; ++neighbors;}
      if(totskill>f[r][c]*neighbors){
        when[r][c]=rd;
        elims.insert(make_pair(r,c));
      }
    }
    for(auto& a : elims){                       //Remove any contestants from our next check if they were eliminated this round
      int r=a.first, c=a.second;
      if(right[r][c]!=w) {left[r][right[r][c]]=left[r][c]; check.insert(make_pair(r,right[r][c]));}
      if(left[r][c]!=-1) {right[r][left[r][c]]=right[r][c]; check.insert(make_pair(r,left[r][c]));}
      if(down[r][c]!=h) {up[down[r][c]][c]=up[r][c]; check.insert(make_pair(down[r][c],c));}
      if(up[r][c]!=-1) {down[up[r][c]][c]=down[r][c]; check.insert(make_pair(up[r][c],c));}
    }
    for(auto& b : elims) check.erase(b);
  }
  long long total=0;
  for(int i=0;i<h;++i){                   //Calculate the total skill level of the contest
    for(int j=0;j<w;++j){
      if(when[i][j]==-1) when[i][j]=rd;
      total+=1ll*f[i][j]*when[i][j];
    }
  }
  cout << total << '\n';
}

void solve(){                //Output formatting
  int t; cin>>t;
  for(int i=0;i<t;++i){
  	cout << "Case #" << i+1 << ": ";
  	tsolve();
  }
}

int main() {                        //Program entry
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}