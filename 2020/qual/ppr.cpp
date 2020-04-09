//Solution submitted by xiaowuc1. Comments added by MattyFen.
//Link to solution set: https://codingcompetitions.withgoogle.com/codejam/submissions/000000000019fd27/eGlhb3d1YzE

//Parenting Partnering Returns can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/000000000020bdf9

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
#define rep(i, a, b) for(int i = a; i < (b); ++i) //unused
#define trav(a, x) for(auto& a : x) //unused
#define all(x) x.begin(), x.end() //unused
#define sz(x) (int)(x).size() //returns the size of a container (string, queue, etc.)
typedef vector<int> vi;  //unused
// END NO SAD

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> matrix;
typedef pair<ll, ll> pll;

// remember you may need to reset state
int lhs[1005]; //holds the start times of each activity
int rhs[1005]; //holds the end times of each activity
int dp[1005];
bool g[1005][1005]; //determines which activities overlap with each other

//solves each test case
void rsolve() {
  int n; //number of activities
  cin >> n; //read in number of activities
  for(int i = 0; i < n; i++) cin >> lhs[i] >> rhs[i]; //read in each activity and save it as a start time (left-hand side) or end time (right-hand side)
  for(int i = 0; i < n; i++) { //for each activity:
    dp[i] = 0; //set the activity to 0
    for(int j = 0; j < n; j++) { //for each activity
      if(i == j) continue; //ignore cases where we are talking about the same activity
      g[i][j] = false; //activities i and j do not overlap
      if(lhs[j] >= rhs[i]) continue; //activity j begins when or after activity i ends
      if(lhs[i] >= rhs[j]) continue; //activity i begins when or after activity j ends
      g[i][j] = true; //activities i and j overlap
    }
  }
  queue<int> q; //queue to hold activity numbers
  string ret = ""; //string to be returned. is either empty or IMPOSSIBLE.

  /******
  * This loop is the bread and butter. What happens here is that, for a given activity, if it has not yet been assigned, we assign it to Cameron.
  * We then find all activities that overlap this activity and, if they have not yet been assigned, assign them Jamie, and add those to the queue.
  * The process continues until one of two things happen:
  * 1) We have assigned all activities to one of the two partners and have verified that no activity assigned to a partner overlaps with another
  *    activity assigned to the partner.
  * 2) There is an activity in the queue that overlaps with an activity assigned to Cameron and with an activity assigend to Jamie. In this case,
  *    solving the test case is IMPOSSIBLE.
  ******/
  for(int i = 0; sz(ret) == 0 && i < n; i++) { //break if we have handled all activities or if deemed IMPOSSIBLE
    if(dp[i]) continue; //all dp[i] are 0, so this will fail to start
    dp[i] = 1; //change the value of dp[i] to 1
    q.push(i); //add the activity to the queue
    while(sz(ret) == 0 && sz(q)) { //while not IMPOSSIBLE and there is an activity in the queue:
      int curr = q.front(); q.pop(); //remove the next activity from the queue
      for(int a = 0; a < n; a++) { //for all other activities:
        if(g[curr][a]) { //if this activity and activity a overlap:
          if(dp[a] == dp[curr]) { //if both activities have been assigned the same value:
            ret = "IMPOSSIBLE"; //the case is IMPOSSIBLE
            break; //we are done
          }
          if(dp[a] == 0) { //if we have not yet assigned activity a:
            dp[a] = -dp[curr]; //assign activity a to the person not assigned to the current activity
            q.push(a); //add activity a to the queue
          }
        }
      }
    }
  }
  //the test case is IMPOSSIBLE
  if(sz(ret)) {
    cout << ret << "\n"; //print IMPOSSIBLE
    return;
  }
  //the test case is possible
  for(int i = 0; i < n; i++) { //for each activity:
    if(dp[i] == 1) cout << 'C'; //all activities assigned a 1 are Cameron's
    else cout << 'J'; //all activities assigned a -1 are Jamie's
  } cout << "\n";
}

//takes care of output formatting
void solve() {
  int t; //number of test cases  
  cin >> t; //read in number of test cases
  for(int casenum = 1; casenum <= t; casenum++) {  //for each test case:
    cout << "Case #" << casenum << ": "; //format output
    rsolve(); //solve this test case
  }
}

int main() {
  ios_base::sync_with_stdio(false); //C I/O streams operate independently from C++ streams
  cin.tie(NULL); cout.tie(NULL); //cin does not wait for cout to flush before reading
  solve(); //begin solution
}
