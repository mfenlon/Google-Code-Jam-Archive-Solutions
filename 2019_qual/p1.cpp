#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]) {
	//Variable declarations
	unsigned int T;
	string T_string,N,firstCheck,secondCheck;

	//Read in number of cases
	cin >> T_string;
	T = atoi(T_string.c_str());

	//Handle cases
	for(unsigned int i=0;i<T;i++){
		cin >> N;

		//Handle each case
		for(unsigned int j=0;j<N.size();j++){

			//Handle 4's
			if(N[j]=='4'){
				firstCheck += '3';
				secondCheck += '1';
			}

			//Handle all other numbers
			else{
				firstCheck += N[j];
				if (secondCheck != "") secondCheck += '0';
			}
		}

		//Print
		cout << "Case #" << i+1 << ": " << firstCheck << " " << secondCheck << endl;
		
		//Reset checks for next case
		firstCheck = secondCheck = "";
	}
}