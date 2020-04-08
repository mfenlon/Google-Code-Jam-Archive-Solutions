//Solution submitted by xiaowuc1. Comments added.
//Link to solution set: https://codingcompetitions.withgoogle.com/codejam/submissions/000000000019fd27/eGlhb3d1YzE

//Indicium can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/0000000000209aa0

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// BEGIN NO SAD
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size() //determines the number of values in a container
typedef vector<int> vi;
// END NO SAD

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> matrix;
typedef pair<ll, ll> pll;

// remember you may need to reset state

int taken[100];

/*******
* dfs will determine if construction of a Latin square is possible given the dimension and the trace.
* It initially takes in an empty vector v, the dimension of the Latin square, and the desired trace.
* If determined to be possible, the trace will have been saved in v (choices in rsolve).
* taken determines how many 1s, 2s, and so on that we used in the trace.
*******/
bool dfs(vector<int>& v, int szneed, int totleft) {

  //not possible if the remaining trace is so small that inserting 1s into each remaining cell in the trace
  //sums too high
  if(totleft < szneed - sz(v)) return false;

  //not possible if the remaining trace is so large that inserting the greatest number possible (n) into each remaining cell
  //in the trace does not sum high enough
  if(totleft > (szneed - sz(v)) * szneed) return false;

  //if our trace is full, check to make sure that we have not used n-1 of any number.
  //if we have, then the only possible location for the nth instance of that number is also in the trace.
  if(sz(v) == szneed) {
    for(int a = 1; a <= szneed; a++) if(taken[a] == szneed-1) return false;
    return true;
  }

  /**
  * This loop begins by filling each row in the trace with a 1 and recursing through dfs. Once this method does not satisfy our base cases,
  * we increment the last value in the trace until it does, then we add another 1. Ultimately, this loop (and the entirety of dfs)
  * produces a trace that looks like this: [1,1,1,...,n,n,n] with 1s on the lhs, n's on the rhs, and any variance in the middle to
  * account for any changes we need to make in order to match the trace. Edge cases include small traces where there are no n's, only 1's
  * and values smaller than n, and large traces where there are no 1's, only n's and values greater than 1. All cases are covered by this loop.
  **/
  for(int i = 1; i <= szneed; i++) {
    taken[i]++;
    v.push_back(i);
    if(dfs(v, szneed, totleft - i)) return true;
    v.pop_back();
    taken[i]--;
  }
  return false;
}

//defining vectors and grids so that we do not have to keep typing this nonsense
typedef vector<int> VI;
typedef vector<VI> VVI;


/******
* This is brilliant. FindMatch takes our grid of possibilities w and two vectors: mr, mc, and seen. mr is a vector in which each index represents
* a single row. The value in the index represents the column in that row in which a is to be stored. mc is the opposite; its indices represent
* columns, and the inner values represent the row in that column in which a will be stored. The combination of the two create order pairs
* of all the cells in which a will be stored in the grid. The third vector, seen, tells us, for this iteration, which columns already store
* a and are, therefore, not candidates for our next storage of a. Here's how it works:
* - For a given row, we find a cell in which we can store a based on w
* - We verify in mc that we have not yet stored a in that column
* - If we have, we jump to the row in which a was first stored in that column and find a new column in which to store a
* The key is in the trace. When we created w, for any value a that exists in the trace, we denoted the corresponding cell in w with a 1 and
* left all other values in the corresponding row to be 0. When we recurse through FindMatch and begin moving values from row to row and from
* column to column, all values have the ability to move with the exception of the values in the trace. This is due to the fact that all cells
* in row in which our trace value exist (except for the trace cell) are 0, meaning that w[i][j] will always fail.
******/
bool FindMatch(int i, const VVI &w, VI &mr, VI &mc, VI &seen) {
  for (int j = 0; j < w[i].size(); j++) { //for each index in a row:
    if (w[i][j] && !seen[j]) { //if it is possible for us to put a in cell (i,j), and if we have not yet seen a in column j:
      seen[j] = true; //mark that we have seen a in column j
      if (mc[j] < 0 || FindMatch(mc[j], w, mr, mc, seen)) { //if we have not yet added a to column j or if we can find another match for a in row i
        mr[i] = j; //save the column in the row
        mc[j] = i; //save the row in the column
        return true; //state that we found a match
      }
    }
  }
  return false;
}


/*****
* BipartiteMatching finds an (i,j) pair for all i and j such that ix!=i(x+1) and jy!=j(y-1) for all x such that 0<=x<= N-1 and 0<=y<=N-1.
* See FindMatch for how the matching works.
*****/
int BipartiteMatching(const VVI &w, VI &mr, VI &mc) {
  mr = VI(w.size(), -1); //row of size n containing indices filled with -1
  mc = VI(w[0].size(), -1); //column of size n of the same manner

  int ct = 0; //counter
  for (int i = 0; i < w.size(); i++) { //for each row in the grid:
    VI seen(w[0].size()); //create an empty vector of size n
    if (FindMatch(i, w, mr, mc, seen)) ct++; //if we find a match, increment our counter
  }
  return ct; //return the number of rows for which we found a column placement for a
}

int ret[55][55]; //Latin square grid

//takes care of solving a single test case
void rsolve() {
  int n, k; //dimension and trace of Latin square
  cin >> n >> k; //read in dimension and trace
  vector<int> choices; //choices vector
  memset(taken, 0, sizeof(taken)); //sets all values of taken to 0
  if(!dfs(choices, n, k)) { //if there is no valid trace:
    cout << "IMPOSSIBLE\n"; //then this test case has no solution
    return; //move to the next test case
  }
  set<int> present; //a set of integers
  for(int out: choices) present.insert(out); //present now holds each unique value in the trace
  assert(sz(choices) == n); //make sure that we have filled each cell in thet trace, no more or fewer
  memset(ret, -1, sizeof(ret)); //set each cell in the Latin square to -1
  for(int i = 0; i < n; i++) { //for each row in the square:
    ret[i][i] = choices[i]; //insert the appropriate trace value
  }
  for(int a = 1; a <= n; a++) { //for each possible cell value:
    if(!present.count(a)) continue; //ignore the values that we have not yet used
    vector<vector<int>> m;  //grid of possibilities

    /**
    * The following loop is super neat. What it does is that it observes each cell in our Latin square and determines
    * if value a can be added to that index. At the end of the loop, we have a grid m of rows of cells populated in one of 2 ways:
    * 1) A row contains N-1 0s and one '1' which shows us that we found a at this particular index of the row
    * 2) A row contains zero or more 0s and one or more 1s which shows us that we did not find a in the row, but we can place a in any one of these indices
    **/

    for(int i = 0; i < n; i++) { //for each row:
      vector<int> can(n, 0); //instantiate a new vector of size n, and set all indices to 0
      int found = -1; //not found
      for(int j = 0; j < n; j++) { //for each index in that row:
        if(ret[i][j] == a) found = j; //if we have found a in the grid, then save the index in which a lives
      }
      if(found >= 0) { //if we found a:
        can[found] = 1; //specify the index (column) in which we found it
      }
      else { //if we did not find a:
        for(int j = 0; j < n; j++) { //for each column:
          if(ret[i][j] < 0) can[j] = 1; //if there is nothing in a given index, note that we can add a to that index
        }
      }
      m.push_back(can); //add the vector of possible locations for a to our grid m
    }

    vector<int> lhs, rhs; //vectors used in matching
    assert(BipartiteMatching(m, lhs, rhs) == n); //assert that we have found a bipartite matching for our value a
    for(int i = 0; i < n; i++) { //for each row:
      ret[i][lhs[i]] = a; //insert a into the corresponding column
    }
  }

  /*******
  * This loop functions in the exact same way as the previous loop. The only change is that we are now focusing on a
  * for all a not in the trace. It is important to handle integers in the trace first because we have less flexibility
  * with integers in the trace given that, in certain rows, we are unable to shift their position.
  *******/
  for(int a = 1; a <= n; a++) {
    vector<vector<int>> m;
    for(int i = 0; i < n; i++) {
      vector<int> can(n, 0);
      int found = -1;
      for(int j = 0; j < n; j++) {
        if(ret[i][j] == a) found = j;
      }
      if(found >= 0) {
        can[found] = 1;
      }
      else {
        for(int j = 0; j < n; j++) {
          if(ret[i][j] < 0) can[j] = 1;
        }
      }
      m.push_back(can);
    }
    vector<int> lhs, rhs;
    assert(BipartiteMatching(m, lhs, rhs) == n);
    for(int i = 0; i < n; i++) {
      ret[i][lhs[i]] = a;
    }
  }
  //Handle output and formatting
  cout << "POSSIBLE\n";
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(j) cout << " ";
      cout << ret[i][j];
    }
    cout << "\n";
  }
}

//formats output for each test case
void solve() {
  int t; //number of test cases
  cin >> t; //read in number of test cases
  for(int casenum = 1; casenum <= t; casenum++) { //for each test case:
    cout << "Case #" << casenum << ": "; //format output
    rsolve(); //solve this test case
  }
}

//program entry point
int main() {
  ios_base::sync_with_stdio(false); //C I/O streams buffer independently from C++ streams
  cin.tie(NULL); cout.tie(NULL); //cin does not wait for cout to flush before reading input
  solve(); //solve the problem
}