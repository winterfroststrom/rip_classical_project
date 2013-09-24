import os

ALGORITHMS = ["bfs", "dfs", "astar", "bastar", "rbfs", "rdfs", "bbfs", "bdfs"]
PROBLEMS = ["problem1.txt", "problem2.txt", "problem3.txt", "problem4.txt"]

for problem in PROBLEMS:
	for algorithm in ALGORITHMS:
		os.system("python astar.py " + problem + " -algorithm " + algorithm + " -min")

