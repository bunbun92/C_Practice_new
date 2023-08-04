#include <stdio.h>
#include <vector>
#include "file.h"
#include <string.h>

using namespace std;

#define RIF(x) if((x) == 0) { puts(""#x); return 0; }

class IDSet{

	vector<char*> L;

public:

	void clear(){
		int size = L.size();
		for(int i= 0; i < size; i++)
			delete L[i];
		L.clear();
	}

	bool open(char* path){		
		File f;		
		RIF(f.open(path));
		char buf[128];		

		while(f.readLine(buf)){


			L.push_back(_strdup(buf));
		}
		
		f.close();

		return 1;
	}


	bool has(IDSet* a, IDSet* b){
		int aSize = a->L.size();
		int bSize = b->L.size();
		
		for(int i= 0; i< aSize; i++){
			for(int j= 0; j< bSize; j++){

			}
		}
	}
// 
// 	char* tok(char* a){
// 		strtok(a, " ");
// 		strtok()
// 	}

};