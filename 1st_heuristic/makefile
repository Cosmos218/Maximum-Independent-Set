all: HEURISTIC1

HEURISTIC1: 
	g++ -o heuristic-1 seq_greedy_based.cpp SequentialGreedyHeuristic.cpp -lemon -std=c++11 -O3	

clean:
	rm -rf *.o
run:
	g++ -o heuristic-1 seq_greedy_based.cpp SequentialGreedyHeuristic.cpp -lemon -std=c++11 -O3	
	./heuristic-1 ../data/DIMACS_all_ascii/C125.9.clq