//Pattern Matching can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b3034

/*************
* The problem of Pattern Matching deals with strings of patterns, and asks for a string
* in return in which each one of the patterns appears. Patterns consist of only uppercase
* English letters and asterisks (*). Asterisks represent any string, including the empty
* string. For the sake of development, we will discuss solutions to each of the test sets.
* For an explanation of the final solution, jump to Test Set 3.
* 
* Test Set 1
* Set 1 consists of patterns in which there is only 1 asterisk in each pattern, and that
* asterisk appears at the beginning of the pattern. We will call the beginning of each
* pattern the prefix and the end of each pattern the suffix. In this case, the prefix can
* be anything, so as long as each pattern is contained in the final suffix, we have found
* a matching pattern. We do this by, first, reading in each pattern and adding it to our 
* vector of suffixes. Along the way, we find the longest suffix by comparing the size of
* the pattern in which we have just received to the longest pattern that we have seen
* so far. When we have read in all patterns and have found the longest pattern, we iterate
* through our suffix vector, verify that each suffix is contained in our longest suffix.
* If each suffix appears in our longest suffix, then we have found a pattern match.
*
* A note regarding optimization:
* We can do without a suffix vector (and later, a prefix vector). Comparisons of characters
* in our longest suffix and our current suffix can be done as we read in patterns. Albeit
* negligible in this problem, this saves us from unnecessary memory usage with respect to
* a suffix vector, and saves us on runtime as we only need to look at each pattern once
* instead of twice. Again, this optimization is negligible given the problems constraints.
*
*
* Test Set 2
* Set 2, like Set 1, consists of patterns for which there is only 1 asterisk in each pattern.
* The asterisk appears at the beginning of the pattern, making the pattern a suffix, OR at
* the end of the pattern, making the pattern a prefix. We employ the same algorithm on
* this test set as we did in Test Set 1, however, instead of simply checking suffixes against
* suffixes, we check prefixes against prefixes. Once we have found our longest suffix and
* our longest prefix in which all other suffixes and prefixes are contained, we concatenate
* the two to form our matching pattern.
*
* Test Set 3
* Set 3 consists of patterns in which there is AT LEAST one asterisk in each pattern, and
* the asterisk(s) may appear anywhere in the pattern. For this set, we must continue to
* check our suffixes and prefixes as we do for Test Set 2. We must also ensure that the
* characters between the prefix and the suffix appear in our matching pattern, so we save
* those, in order, as well. Again, once we have found our longest suffix and our longest
* prefix in which all other suffixes and prefixes are contained, we concatenate in the
* following manner: prefix + middleChars + suffix.
*
*
* A thought:
* Consider the following test input:
*
* *HELLO
* HELLO*
*
* Our program will produce HELLOHELLO as output. Given the problem's constraints, our
* program works fine. Even when we consider the constraints of Test Set 3, the maximum
* size string that our program outputs is still within the bounds. However, HELLO
* would also pass the test input, and it is shorter than our output. If we were asked
* to return the SHORTEST matching pattern, we would need to verify that there is no
* overlap between patterns/subpatterns in the middle characters of our final matching
* pattern. I don't know how to do that. Again, this is just a thought, and I have other
* code to comment. Cheers.
*************/

#include <bits/stdc++.h> //import every standard library

using namespace std;

typedef vector<string> VS;

//Add our most recently read suffix to our suffix vector
//and check to see if this suffix is the longest we have
//read so far.
void addToSuffixVec(VS& sv,string& ls,int& ss,string& s){
  if(s.length()>ss){
    ls=s;
    ss=s.length();
  }
  sv.push_back(s);
}

//Add our most recently read prefix to our prefix vector
//and check to see if this prefix is the longest we have
//read so far.
void addToPrefixVec(VS& pv,string& lp,int& ps,string& s){
  if(s.length()>ps){
    lp=s;
    ps=s.length();
  }
  pv.push_back(s);
}

//Return the longest prefix in which we have found all
//other prefixes. Otherwise, report a mismatch.
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

//Return the longest suffix in which we have found all
//other suffixes. Otherwise, report a mismatch.
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

//Solves individual test sets
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

//Output formatting
void solve(){
  int t; cin>>t;
  for(int i=0;i<t;++i){
  	cout << "Case #" << i+1 << ": ";
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