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
import os

if __name__ == "__main__":
    f_results = open('results.csv', 'w')
    mypath = "../data/DIMACS_all_ascii/"
    onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]
    for file_name in onlyfiles:        
        graph = nx.Graph()
        os.system("./grosso "+mypath+file_name)        
    f_results.close()