#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]){
	//Variable declarations
	unsigned int T,N_size;
	string N_str, N_size_str, T_string, myPath;

	//Read number of cases
	cin >> T_string;
	T = atoi(T_string.c_str());

	//Handle cases
	for (unsigned int i=0;i<T;i++){

		//Read dimensions of grid (We will not use this information)
		cin >> N_size_str;

		//Read Lydia's path
		cin >> N_str;
		N_size = N_str.size();

		//Handle each case
		for (unsigned int j=0;j<N_size;j++){
			if(N_str[j] == 'E') myPath += 'S';
			else myPath += 'E';
		}

		//Print myPath
		cout << "Case #" << i+1 << ": " << myPath << endl;

		//Reset myPath for next case
		myPath = "";
	}
}