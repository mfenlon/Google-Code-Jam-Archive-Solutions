#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;

int main(int argc, char* argv[]){
	//Variable declarations
	unsigned int T,N,B,F,sectionLimit,zeroOrOne,counter,workingIndex;
	string T_str,N_str,B_str,F_str,newCommString,expectedReturnString,brokenStringReturn,workingStringReturn,verdict;
	vector<string> commStrings,brokenStrings,workingStrings;

	//Read number of cases
	cin >> T_str;
	T = atoi(T_str.c_str());

	//Handle cases
	for (unsigned int i=0;i<T;i++){

		//Read and process test case information
		cin >> N_str >> B_str >> F_str;

		N = atoi(N_str.c_str());
		B = atoi(B_str.c_str());
		F = atoi(F_str.c_str());

		vector<string> expectedReturn; //Holds what the judge will return if all computers are working

		//Create 4 communication strings of N length

		for(unsigned int i=0;i<4;i++){
			switch(i){
				case 0:
					sectionLimit = 16;
					zeroOrOne = 8;
					break;
				case 1:
					sectionLimit = 8;
					zeroOrOne = 4;
					break;
				case 2:
					sectionLimit = 4;
					zeroOrOne = 2;
					break;
				default:
					sectionLimit = 2;
					zeroOrOne = 1;
			}
			counter = 0;

			for (unsigned int j=0;j<N;j++){
				if(counter<zeroOrOne) newCommString += "0";
				else newCommString += "1";
				counter++;
				if(counter == sectionLimit) counter = 0;
			}
			commStrings.push_back(newCommString);
			newCommString.clear();
		}

		//Populate expectedReturn vector
		for(unsigned int i=0;i<N;i++){
			for(unsigned int j=0;j<4;j++){
				expectedReturnString+=commStrings[j][i];
			}
			expectedReturn.push_back(expectedReturnString);
			expectedReturnString.clear();
		}

		//Send and receive information to/from the judge
		for(unsigned int i=0;i<4;i++){
			cout << commStrings[i] << endl;
			cout << flush;
			cin >> brokenStringReturn;
			brokenStrings.push_back(brokenStringReturn);
		}

		//Create list of working computers
		for(unsigned int i=0;i<N;i++){
			for(unsigned int j=0;j<4;j++){
				workingStringReturn+=brokenStrings[j][i];
			}
			workingStrings.push_back(workingStringReturn);
			workingStringReturn.clear();
		}

		//Check working computers against all computers. Save missing indices.
		workingIndex = 0;

		for(unsigned int i=0;i<N;i++){
			if(expectedReturn[i]==workingStrings[workingIndex]){
				workingIndex++;
			}
			else{
				cout << i << ' ';
			}
		}

		cout << '\n';
		cout << flush;

		//Receive verdict
		cin >> verdict;
		if(verdict=="-1") return 0;

		//Clear vectors for next go-round
		commStrings.clear();
		workingStrings.clear();
		expectedReturn.clear();
		brokenStrings.clear();
	}

	return 0;
}
