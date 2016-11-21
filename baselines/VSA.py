# Created By Gustavo Penha : guzpenha10@gmail.com

from IPython import embed
import networkx as nx
from networkx.algorithms.approximation import independent_set
import operator
import matplotlib.pyplot as plt
from itertools import chain
from os import listdir
from os.path import isfile, join
import progressbar
from tqdm import tqdm

def isValid(mis,graph):
    mis_set = set(mis)
    for node in mis:
        for neighbor in graph.neighbors(node):
            if neighbor in mis_set:
                print("This set is not valid because the following nodes are neighbors: ("+ node+","+neighbor+")")                
                return False
    return True

def calculate_nodes_support(graph,graph_centrality_measure):
    support = {}
    for node in graph.nodes():
        support[node] = 0
        for neighbor in graph.neighbors(node):        
            support[node]+= graph_centrality_measure[neighbor]
    return support

# VSA
def choose_next_node(graph,nodes_support):
    nodes_sorted_by_support = sorted(nodes_support.items(),key=operator.itemgetter(1),reverse=True)
    max_support_value = nodes_sorted_by_support[0][1]

    nodes_with_max_support =  [x[0] for x in nodes_sorted_by_support if x[1]==max_support_value]
    nodes_degrees = {}
    for node in nodes_with_max_support:
        nodes_degrees[node] = graph.degree(node)

    vertex_chosen = None        
    nodes_wmaxsup_sorted_by_degree = sorted(nodes_degrees.items(),key=operator.itemgetter(1),reverse=True)
    # print(nodes_wmaxsup_sorted_by_degree)
    vertex_chosen = nodes_wmaxsup_sorted_by_degree[0][0]                    
    return vertex_chosen

# AVSA
def choose_next_node_2(graph,nodes_support):
    nodes_sorted_by_support = sorted(nodes_support.items(),key=operator.itemgetter(1))    
    min_support_value = nodes_sorted_by_support[0][1]

    nodes_with_min_support =  [x[0] for x in nodes_sorted_by_support if x[1]==min_support_value]    
    neighbrs = set(list(chain.from_iterable([graph[node] for node in nodes_with_min_support])))

    if(len(neighbrs)>0):
        neighbors_support = {}
        for n in neighbrs:
            neighbors_support[n]= nodes_support[n]
        
        neighbors_sorted_by_support = sorted(neighbors_support.items(),key=operator.itemgetter(1),reverse=True)
        vertex_chosen = neighbors_sorted_by_support[0][0]
    else:        
        vertex_chosen = nodes_sorted_by_support[-1][0]

    return vertex_chosen


def greedy_heuristic(graph, choose_type = "VCA"):    
    graph_nodes_original = set(graph.nodes())    
    vertex_cover = set()    

    edges_total = len(graph.edges())    
    with tqdm(total=edges_total) as pbar:
        last = edges_total
        while len(graph.edges())>0:

            # chose node by max support, in case of tie chose max degree        
            if(choose_type == "VSA"):
                nodes_support = calculate_nodes_support(graph)
                vertex_chosen = choose_next_node(graph,nodes_support)
            elif (choose_type == "AVSA"):
                nodes_support = calculate_nodes_support(graph)
                vertex_chosen = choose_next_node_2(graph,nodes_support)            
            elif(choose_type == "VCA"):
                try:            
                    # centrality_measure = nx.algorithms.centrality.closeness_centrality(graph)    
                    # centrality_measure = nx.algorithms.centrality.betweenness_centrality(graph,k=len(graph.nodes())/2)
                    centrality_measure = nx.algorithms.centrality.eigenvector_centrality_numpy(graph)                                    
                    nodes_support = calculate_nodes_support(graph,centrality_measure)
                except:
                    centrality_measure = nx.algorithms.centrality.degree_centrality(graph)
                    print("exception :p")
                    nodes_support = calculate_nodes_support(graph,centrality_measure)

                # embed()
                vertex_chosen = choose_next_node(graph,nodes_support)

            # removing him from the graph
            graph.remove_node(vertex_chosen)

            # this vertex is now included in the solution
            vertex_cover.add(vertex_chosen)                    
            
            # updating bar
            pbar.update(last - len(graph.edges()))           
            last = len(graph.edges())
    return graph_nodes_original - (vertex_cover)    

if __name__ == "__main__":
    f_results = open('results_VSA.csv', 'w')
    mypath = "../data/DIMACS_all_ascii/"
    onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]
    for file_name in onlyfiles:
        # print(file_name)    
        graph = nx.Graph()
        with open(mypath+file_name) as f:
            for line in f.readlines():
                if line[0] == 'e':
                    u = line.split(" ")[1].strip()
                    v = line.split(" ")[2].strip()
                    graph.add_edge(u,v)
        
        mis = greedy_heuristic(nx.complement(graph))        
        print(file_name.split("/")[-1] + " : "+ str(len(mis))) 
        f_results.write(file_name.split("/")[-1] + ","+ str(len(mis))+"\n")
        # break
    f_results.close()