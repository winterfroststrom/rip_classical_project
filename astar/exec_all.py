import os

ALGORITHMS = sorted(["bfs", "dfs", "astar", "bastar", "rbfs", "rdfs", "bbfs", "bdfs"])
PROBLEMS = ["problem1.txt", "problem2.txt", "problem3.txt", "problem4.txt"]

for algorithm in ALGORITHMS:
	for problem in PROBLEMS:
		os.system("python astar.py " + problem + " -algorithm " + algorithm + " -min")

