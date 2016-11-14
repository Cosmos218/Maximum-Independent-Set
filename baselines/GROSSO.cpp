// Created By Gustavo Penha : guzpenha10@gmail.com

#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/dimacs.h>
#include <lemon/grosso_locatelli_pullan_mc.h>
#include <string>

using namespace lemon;
using namespace std;

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
  internal.push_back(tok);
  }
  
  return internal;
}

int main(int argc, char** argv){
  typedef ListGraph Graph;
  typedef Graph::Node Node;
  typedef Graph::Edge Edge;
  typedef Graph::EdgeMap<int> LengthMap;
 
  Graph g;
  Edge e ;
  vector<Node> nodes;
  int nodesSize,edgesSize;
  int u,v;

  string filename = argv[1];
  string line;
  std::ifstream f(filename);


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

  // Run grosso algorithm
  GrossoLocatelliPullanMc<Graph> mc(g);
  mc.run();
  cout<<filename<<","<< mc.cliqueSize()<<endl;

  return 0;
}
