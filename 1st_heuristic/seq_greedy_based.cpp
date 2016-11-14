/*
  @author: guzpenha@dcc.ufmg.br
  Gustavo Penha
*/


#include <iostream>
#include <string>
#include "SequentialGreedyHeuristic.h"

#define PVF(X) for(int x=0;x<X.size();x++){printf("%f ",X[x]);}printf("\n");
#define SZ(X) ((int)(X).size())
#define REP(I, N) for (int I = 0; I < (N); ++I)
#define REPP(I, A, B) for (int I = (A); I < (B); ++I)
#define REPM(I, N) for(auto I = (N.begin()); I != N.end();I++)
#define MP make_pair
#define PB push_back
#define F first
#define S second
 
using namespace std;

int main(int argc, char** argv){
	string filename = argv[1];	
			
	SequentialGreedyHeuristic * sg = new SequentialGreedyHeuristic();
	sg->readGraph(filename);
	cout<<filename<<","<<sg->sequentialHeuristic()<<endl;

	return 0;
}
