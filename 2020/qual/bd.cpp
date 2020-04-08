//ESAb ATAd can be found at:
//https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/0000000000209a9e

#include <bits/stdc++.h>

using namespace std;

char getBit(int b){
	cout << b << endl;
	char c;
	cin >> c;
	return c;
}

bool isValid(char& c){
	if(c=='N') return 0;
	else return 1;
}

void checkPairs(int& same, int& diff,char& ls,char& rs,int& l){
	if(!same && ls==rs) same=l-1;
	else if(!diff && ls!=rs) diff=l-1;
}

void comp(string& a1,string& a2){
	for(int i=0;i<a1.length();++i){
		if(a1[i]=='0') a1[i]='1';
		else a1[i]= '0';
		if(a2[i]=='0') a2[i]='1';
		else a2[i]='0';
	}
}

void swap(string& a1,string& a2){
	for(int i=0;i<a1.length();++i){
		char tmp=a1[i];
		a1[i]=a2[a2.length()-1-i];
		a2[a2.length()-1-i]=tmp;
	}
}

int main() {
  ios::sync_with_stdio(false);  //allows C++ i/o streams to buffer independently from C streams
  cin.tie(0); //cin does not wait for cout to flush
  int t,b; cin >> t >> b; //read number of test cases and number of bits
  for(int i=0;i<t;++i){
  	
  	//strings to hold the left and right sides of answer
  	string a1,a2; a1 = a2 = "";
  	
  	//ints to track where we are in the left and rights sides of answer
    int l,r; l=1;r=b;

    //pairs of indices indicating same and different bits
    int same,diff; same=diff=0;
    char same_char,diff_char;
    
    //input chars from the left and right sides of answer
    char ls,rs;
  	
    //track number of exchanges
    int ex=1;

  	//begin exchanges

    /*******
    * The algorithm works in the following way:
    * Given the fact that we can gather little information from our exchanges with the judge, we must choose our selections wisely.
    * Let's first make 10 exchanges with the judge knowing that the string of bits will not change during the first 10 exchanges. But which bits?
    * Let's keep it simple. We have a string of 4 bits. Then, we applied one of the four effects to the string and received another 4 bits.
    * Here are some examples:
    * 1) 0100 -> 1101
    * 2) 0100 -> 0010
    * 3) 0100 -> 0100
    * 4) 0100 -> 1011
    *
    * What happened in each of the 4 cases? You can probably tell that the effects occurred in the following way:
    * 1) Swap and Complement
    * 2) Swap
    * 3) Nothing
    * 4) Complement
    *
    * Easy, right? Now, if you look closely, the selection of starting bits is important. Notice first that each example begins with the
    * same combination and order of bits: 0100. Next, you will notice that each effect occurred exactly one time. Finally, you will notice
    * that each effect produced a unique result. So here is what we do:
    *
    * We make our first 10 exchanges with the judge. The bits will consist of the first 5 bits and the last 5 bits of the string. It is
    * important to choose bits on opposite ends of the string so that we can evaluate our swaps. While we are making our exchanges, we
    * will note when we receive a set of opposite bits (bits 1 and N, 2 and N-1, etc.) for which the return value is the same (0 and 0 or
    * 1 and 1) and save their locations (we really only need to save the location on the lhs. We will call this bit S). We will also note
    * when we receive a set of opposite bits for which the return values are opposite (1 and 0 or 0 and 1) and save their locations
    * (again, we really only need the lhs. We will call this bit D). Now for the fun part. On the 11th exchange, we grab S. On the 12th exchange,
    * we grab D. We now take S and D up to our examples above and determine, based on the unique output, which effect occurred! Don't worry
    * if you initial string was not 0100. Any combination of like bits and unlike bits will do. When we have determined which effect occurred,
    * we alter bits 1-5 and (N-4)-N that we received in the prior 10 exchanges. Now our partial string matches the judge's partial string, and
    * we have 8 more exchanges before the judge adds another effect. So, we will grab bits 6-9 and (N-8)-(N-5), add them to our partial strings,
    * and repeat the process. We continue until we have received each bit from the judge one time. Then, we send the result.
    *******/
  	while(l<=r){
  	  if(ex>10 && ex%10==1){
  	  	if(same) same_char=getBit(same);
		if(diff) diff_char=getBit(diff);
		if(same && diff){
			if(a1[same-1]!=same_char && a1[diff-1]!=diff_char) comp(a1,a2);
			else if(a1[same-1]==same_char && a1[diff-1]!=diff_char) swap(a1,a2);
			else if(a1[same-1]!=same_char && a1[diff-1]==diff_char) {comp(a1,a2); swap(a1,a2);}
		}
		else if(same){
			same_char=getBit(same);
			if(a1[same-1]!=same_char) comp(a1,a2);
		}
		else if(diff){
			diff_char=getBit(diff);
			if(a1[diff-1]!=diff_char) comp(a1,a2);
		}
		else{
			same_char=getBit(1);
			same_char=getBit(1);
		}
  	  	++ex; ++ex;
  	  }
  	  else if(ex%2==1){
  	  	ls=getBit(l);
  	  	if(!isValid(ls)) return -1;
  	  	a1=a1+ls;
  	  	++ex; ++l;
  	  }
  	  else{
  	  	rs=getBit(r);
  	  	if(!isValid(rs)) return -1;
  	  	a2=rs+a2;
  	  	++ex; --r;
  	  	checkPairs(same,diff,ls,rs,l);
  	  }
  	}
  	string ans=a1+a2;
  	cout << ans << endl;

  	char res;
  	cin >> res;
  	if(!isValid(res)) return -1;
  }
}