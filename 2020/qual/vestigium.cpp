//Vestigium can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/000000000020993c

#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);  //allows C++ i/o streams to buffer independently from C streams
  cin.tie(0); //cin does not wait for cout to flush
  int t; cin >> t; //read number of test cases
  for(int i=0;i<t;++i){ //for each test case:
  	map<int,set<int>> rows; //rows and cols maps will track which integers are in each row
  	map<int,set<int>> cols; //and in each column
  	int n; cin >> n; //read in the dimensions of the grid
  	int trace=0; //initialize the trace to 0. we will increment as necessary
  	for(int j=0;j<n;++j){ //for each row:
  		for(int k=0;k<n;++k){ //for each column:
  			int m; cin >> m; //read in the value at the cell (j,k)
  			if(j==k) trace+=m; //increment the trace by m if we are on the trace diagonal
  			rows[j].insert(m); //add m to the set at row j
  			cols[k].insert(m); //add m to the set at col k
  		}
  	}
  	int r=0; int c=0; //r and c will hold the number of rows and columns in which we found repeated values
  	for(int j=0;j<n;++j){ //for each row/column:
  		if(rows[j].size()<n) r+=1; //the set at row or column j will have exactly n integers in it if each
  		if(cols[j].size()<n) c+=1; //value in the row or column is unique. if there are fewer, then one or more values repeated
  	}
  	cout << "Case #" << i+1 << ": " << trace << ' ' << r << ' ' << c << '\n'; //output formatting
  }
}