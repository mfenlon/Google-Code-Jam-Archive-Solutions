//Nesting Depth can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/0000000000209a9f

#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);  //allows C++ i/o streams to buffer independently from C streams
  cin.tie(0); //cin does not wait for cout to flush
  int t; cin >> t; //read number of test cases
  for(int i=0;i<t;++i){ //for each test case:
  	string s; cin >> s; //read in the string of digits
  	int d=0; int l=0; //d is the difference between two adjacent digits. l is the last digit that we read in.
  	string sp; //we will construct our output string as we process the input string
  	for(int i=0;i<s.length();++i){ //for each digit in the input string:
  	  int x=(int)s[i]-48; //convert the char to an int
  	  d=l-x; //find the difference between the current digit and the previous digit
  	  l=x; //set the current digit to be the previous digit to prepare for the next iteration of the loop
  	  while(d<0){ //add open parentheses to the output string if we need to create a deeper nest
  	  	sp=sp+"(";
  	  	++d;
  	  }
  	  while(d>0){ //add close parentheses to the output string if we need to create a shallower nest
  	  	sp=sp+")";
		    --d;
  	  }
  	  sp=sp+s[i]; //add the digit to the output string
  	}
  	while(l>0){ //at the end of the input string, if we need to close the nest, do so
  	  sp=sp+")";
	    --l;
  	}
  	cout << "Case #" << i+1 << ": " << sp << '\n'; //output formatting
  }
}