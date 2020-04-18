//Pascal Walk can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b1353

/**************
* The solution to Pascal Walk uses a unique property of Pascal's Triangle. The property is
* as follows (from the top of the triangle, down):
* 
* Sum of the elements in Row 1: 1
* Sum of the elements in Row 2: 2
* Sum of the elements in Row 3: 4
* Sum of the elements in Row 4: 8
* Sum of the elements in Row 5: 16
* ...
*
* Noticing a pattern? The sum of the elements in Row i is equal to 2^(i-1). We can use this
* information in combination with our knowledge about bits of a number written in binary
* form to say the following:
*
* If we can find a binary representation of N, rows for which the corresponding bit is a 1
* are included in our walk. Take 19 for example. Written in binary, 19 is 10011. If we look
* up to our triangel, we can see that the rows that correspond to the 1 bits, from least
* significant to most significant, are Rows 1, 2, and 5. The corresponding sums are 1, 2, and
* 16. 1 + 2 + 16 = 19.
*
* However, we must be careful. Our walk must be continuous, meaning it is outside the constraints
* to jump from Row 2 to Row 5, so we must walk from Row 2 to Row 5. The best way to do this
* is along the edge of the triangle where the value of the hex is 1, but we still not to
* account for the 1 in our sum. So what do we do? Well, we notice that the greatest value for
* N that we will receive is 10^9. We can use the knowledge that 2^30 > 10^9 to say that we
* will never use more than 30 rows of the triangle. Even if we did use all 30 rows, we would
* traverse at most 465 hexes which is within our constraint. So what we will do to account
* for the skipped rows is this:
*
* - Before beginning the walk, subtract 30 from our N (provided that N>30)
* - Converter N' to binary, and walk the triangle according to its 0 bits and 1 bits
* - While walking, keep track of the number of rows that we skipped (0 bits)
* - At the end of the walk, we still need to account for the 30 that we took from N
*   to start. We have already accounted for some of the 30 with our skipped rows, so
*   walk the edge of the triangle for 30-#skipped hexes
*
* With respect to our constraints, we have maintained a continuous walk, and our walk will
* have traversed at most 495 hexes.
**************/

#include <bits/stdc++.h> //import every standard library

using namespace std;

//Finish summing to N by walking the 1s on the right or left edge of the triangle
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

//Trim the binary string so that there are no leading 0s
string trim(string bstring){
	for(int i=0;i<1000;++i){
		if(bstring[0]=='0') bstring=bstring.substr(1);
		else return bstring;
	}
	return bstring;
}

//Solve each test case
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

//Output formatting
void solve(){
  int t; cin>>t;
  for(int i=0;i<t;++i){
  	cout << "Case #" << i+1 << ":" << '\n';
  	tsolve();
  }
}

//Program entry
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}