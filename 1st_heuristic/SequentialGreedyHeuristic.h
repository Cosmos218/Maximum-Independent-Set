/*
  @author: guzpenha@dcc.ufmg.br
  Gustavo Penha
*/

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <lemon/list_graph.h>
#include <lemon/grosso_locatelli_pullan_mc.h>

using namespace std;
using namespace lemon;

typedef ListGraph Graph;
typedef Graph::Node Node;
typedef Graph::Edge Edge;

class SequentialGreedyHeuristic {
    public:
        explicit SequentialGreedyHeuristic();
        virtual ~SequentialGreedyHeuristic();

        void readGraph(string filename);
        bool isValidSolution(set<int> S);
        int choseNextNode();
        int sequentialHeuristic();

    private:
        ListGraph g;
        Edge e ;
        vector<Node> nodes;
};