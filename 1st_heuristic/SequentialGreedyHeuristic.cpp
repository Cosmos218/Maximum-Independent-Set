/*
  @author: guzpenha@dcc.ufmg.br
  Gustavo Penha
*/


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
 
//--------------------------------------------------------------------------------------//
//    =>     Constructor and destructor                                                 //
//                                                                                      //
//--------------------------------------------------------------------------------------//
SequentialGreedyHeuristic::SequentialGreedyHeuristic(){

}

SequentialGreedyHeuristic::~SequentialGreedyHeuristic(){}

//--------------------------------------------------------------------------------------//
//    =>     Reading input                                                              //
//                                                                                      //
//--------------------------------------------------------------------------------------//

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
  internal.push_back(tok);
  }
  
  return internal;
}

void SequentialGreedyHeuristic::readGraph(string filename){       
  int u,v;
  edgesSize =0;

  string line;
  ifstream f(filename);

  // Read graph in DIMACS format
  while(getline(f,line)){      
    if(line[0]!='c'){
       if(line[0] == 'p'){         
         vector<string> splitted = split(line,' ');         
         nodesSize = std::stoi(splitted[2]);         
         nodes.resize(nodesSize+1);
         for (int k = 1; k <= nodesSize; ++k) {
          nodes[k] = g.addNode();
         }
       }else if(line[0]=='e'){         
         vector<string> splitted = split(line,' ');
         u = stoi(splitted[1]);
         v = stoi(splitted[2]);         
         e = g.addEdge(nodes[u],nodes[v]);
        }
    }  
  }

  // Prints nodes and edges:
 //  cout<<"nodes"<<endl;
 //  for (ListGraph::NodeIt n(g); n != INVALID; ++n)
 //  	cout << g.id(n) << ";";
 //  cout<<endl;

 //  cout<<"edges"<<endl;  
 //  for (ListGraph::EdgeIt e(g); e != INVALID; ++e)    
	// cout << "(" << g.id(g.u(e)) << ", " << g.id(g.v(e)) << ");";
 //  cout<<endl;
}

//--------------------------------------------------------------------------------------//
//    =>     Heuristic                                                                  //
//                                                                                      //
//--------------------------------------------------------------------------------------//

bool SequentialGreedyHeuristic::isValidSolution(set<int> S){
	return false;
}

int SequentialGreedyHeuristic::choseNextNode(){
	int min_degree = 100000000;
	int min_index = 0;

	unordered_map<int,int> degrees;
	// Choosing by degree
	for (ListGraph::NodeIt n(g); n != INVALID; ++n){
		int degree=0;
		for(Graph::IncEdgeIt e(g, n); e!=INVALID; ++e) {			
			degree++;
		}
		if(degree<min_degree){
			min_degree = degree;
			min_index = g.id(n);
		}
		degrees[g.id(n)] = degree;
	}

	REPM(it,degrees){
		cout<<(*it).F<<"->"<<(*it).S<<endl;
	}

	cout<<"min:"<<min_degree<<endl;
	cout<<"index:"<<min_index<<endl<<endl;

	return min_index;
}

int SequentialGreedyHeuristic::updateGraph(int nodeIndex){
	int removed = 0;
	Node node = nodes[nodeIndex];	
		
	cout<<"removing "<<g.id(node)<<endl;

	vector<Node> nodesToRemove;
	nodesToRemove.PB(node);

 	for(Graph::IncEdgeIt e(g, node); e!=INVALID; ++e) {
		Node oppositeNode(g.oppositeNode(node, e) );		
		nodesToRemove.PB(oppositeNode);
	}	
	REP(i,nodesToRemove.size()){
 		g.erase(nodesToRemove[i]);
 	}	
 	nodes = vector<Node>(0);
 	for (ListGraph::NodeIt n(g); n != INVALID; ++n){
 		nodes.PB(n);
 	}

 	cout<<"removed "<<nodesToRemove.size()<<" nodes"<<endl;
	return nodesToRemove.size();
}

int SequentialGreedyHeuristic::sequentialHeuristic(){
	set<int> S;	
	int countRemoved = nodesSize;
	cout<<nodesSize<<" nodes graph."<<endl;
	while(countRemoved>0){
		int nextNode = choseNextNode();
		S.insert(nextNode);
		countRemoved -=updateGraph(nextNode);
		// break;
	}

	return S.size();
}