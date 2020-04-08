// Submitted by Gennady.Korotkevich. Comments added.
// https://codingcompetitions.withgoogle.com/codejam/submissions/0000000000051635/R2VubmFkeS5Lb3JvdGtldmljaA

/**
 *    author:  tourist
 *    created: 31.03.2018 11:41:48      
**/
#include <bits/stdc++.h> //import every standard library

using namespace std;

int main() {
  ios::sync_with_stdio(false); //allow c++ streams to buffer I/O independently from C streams
  cin.tie(0);     //does not flush cout before accepting from cin
  mt19937 rng(5);   //Mersenne Twister pseudo-random generator
  vector<int> prec[22][22];   //resultant vector
  for (int h = 2; h <= 20; h++) {   //loop all possible row numbers from 2 to 20
    for (int w = 2; w <= 20; w++) {   //loop all possible column numbers from 2 to 20
      vector<vector<int>> g(h * w);   //create a grid that holds row * column integers
      for (int i = 0; i < h; i++) {   //loop over each row
        for (int j = 0; j < w; j++) {   //loop over each column               //the four loops (no pun intended) generate 2 separate cells
          for (int ii = 0; ii < h; ii++) {  //loop over each row again
            for (int jj = 0; jj < w; jj++) {    //loop over each column again
              if (i != ii && j != jj && i - j != ii - jj && i + j != ii + jj) {  //if the two cells are not in the same row, column, or diagonal
                g[i * w + j].push_back(ii * w + jj);        //add the second cell to the list of cells to which the first cell can jump
              }
            }
          }
        }
      }
      for (int i = 0; i < h * w; i++) {   //iterate through all cells in the grid
        shuffle(g[i].begin(), g[i].end(), rng); //randomly shuffle vector of jumpable cells
      }
      vector<int> cur; //empty "current" vector
      vector<int> res;  //empty "result" vector
      vector<int> was(h * w, 0); //initialize vector with the size of g where all values are 0 -- represents "was this cell visited?"
      function<void(int, int)> dfs = [&](int cnt, int v) {  //define a depth-first search function
        if (!res.empty()) {   //If res vector has something in it, we are done
          return;
        }
        cur.push_back(v);   //otherwise, add the cell to the end of our jump path
        was[v] = 1;   //note that we have visited this cell
        if (cnt == h * w) {   //if we have added enough cells to the cur vector to fill g, then we are done
          res = cur;  //set res to cur so that we exit on the next iteration of dfs
        }
        for (int u : g[v]) {  //iterate through every jumpable cell in cell v
          if (!was[u]) {  //if we have not been to that cell yet (was[u]=0)
            dfs(cnt + 1, u);  //jump to that cell
          }
        }
        cur.pop_back();   //if we have tried to jump to all jumpable cells and could not complete a path,
        was[v] = 0;       //remove this cell from the path and mark the cell as unvisited
      };
      for (int i = 0; i < h * w; i++) { //iterate through the grid starting at each cell in order to find a path
        dfs(1, i);
      }
      prec[h][w] = res;   //add the successful (or unsuccessful) path the prec
//      cerr << h << " " << w << " done, res.size() = " << res.size() << '\n';
    }
  }
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {   //  for each test case, read in the height and width,
    cout << "Case #" << qq << ": ";    //  then search the prec vector.
    int h, w;                          //  if that node is empty, then there is no possible path. 
    cin >> h >> w;                     //  if prec is not empty, then we can print out the sequence of cells 
    if (prec[h][w].empty()) {          //  that represents a possible solution.
      cout << "IMPOSSIBLE" << '\n';
    } else {
      cout << "POSSIBLE" << '\n';
      for (int x : prec[h][w]) {
        cout << x / w + 1 << " " << x % w + 1 << '\n';
      }
    }
  }
  return 0;
}
