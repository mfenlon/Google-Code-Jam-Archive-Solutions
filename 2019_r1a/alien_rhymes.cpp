//Sumbitted by Gennady.Korotkevich. Comments added.
//https://codingcompetitions.withgoogle.com/codejam/submissions/0000000000051635/R2VubmFkeS5Lb3JvdGtldmljaA

//Alien Rhymes can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104e05

/**
 *    author:  tourist
 *    created: 31.03.2018 11:41:48       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false); //allows C++ streams to buffer I/O independently from C streams
  cin.tie(0); //does not flush cout before accepting from cin
  int tt;   //num test cases
  cin >> tt;  //read num test cases
  for (int qq = 1; qq <= tt; qq++) {  //execute num test cases
    cout << "Case #" << qq << ": ";   //prepare output
    int n;    //num words in test cases
    cin >> n; //read num words
    const int ALPHA = 26; //used for emplacing vectors in a vector   ////////This is some cool stuff. push_back (and other insert functions for that matter)
    vector<vector<int>> trie;  //trie representation                       //generally require the use of copies (or moves). emplace_back is a variadic function
    trie.emplace_back(ALPHA, -1);  //adds a vector of 26 -1's to trie      //that takes a list of arguments and uses it to create an object that can be directly
    vector<int> visits(1, 0);  //tracks number of visits to each node      //inserted into a container.
    vector<int> pv(1, -1);   //paths up the trie from each leaf to root    //
    while (n--) {    //loop over num words                                 //tl;dr
      string s;     //individual word                                      //he creates a vector without creating a vector
      cin >> s;     //read word
      int t = 0;  //tracks current node
      for (char c : string(s.rbegin(), s.rend())) { //for each character in the reversed word
        int d = (int) (c - 'A');  //change char to int ranging from 0-25
        if (trie[t][d] == -1) {   //if this node has not been created yet
          trie[t][d] = (int) trie.size();  //this will be the nth node
          trie.emplace_back(ALPHA, -1);   //add another level to the trie
          visits.push_back(0);  //add the new node to visits
          pv.push_back(t);  //add the new node to our path
        }
        t = trie[t][d]; //this is the trie[t][d]th node
        visits[t]++;    //we have visited this node another time
      }
    }
    int ans = 0;  //tracks pairs
    for (int i = (int) trie.size() - 1; i >= 0; i--) { //iterate over nodes starting from last-added word
      if (visits[i] < 2) {  //move if only node corresponds to only one unmatched word
        continue;
      }
      ans++;  //we have found an unmatched pair! add it to the total.
      int v = i; //v is our current node
      while (v != -1) {  //as long as we are not at the root
        visits[v] -= 2;  //remove 2 visits from the current node
        v = pv[v];   //v is now the parent of our former v node
      }
    }
    cout << 2 * ans << '\n';  //ans holds the number of pairs, so double it
  }
  return 0;
}