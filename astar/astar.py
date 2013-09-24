import argparse
from time import time
from variables import *
from heuristics import *
from algorithms import *
from string_util import *
import algorithms

parser = argparse.ArgumentParser(description='Solve Sokoban with A*.')
parser.add_argument('problem', help='problem file for sokoban')
parser.add_argument('-algorithm', help='algorithm to use', choices=['astar', 'bfs', 'dfs', 'rbfs', 'bastar', 'bbfs', 'bdfs', 'rdfs'], default='astar')
parser.add_argument('-frames', help='show frames', action="store_true")
parser.add_argument('-perf', help='show performance data', action='store_true')
parser.add_argument('-min', help='show only time, states, and number of steps', action='store_true')
args = parser.parse_args()

def list2tuple(l):
	return tuple(map(tuple, l))

def parseProblem(problem):
	parsed_problem = []
	goals = []
	blocks = []
	append1 = parsed_problem.append
	appendb = blocks.append
	appendg = goals.append
	for i in range(len(problem)):
		append1([])
		append2 = parsed_problem[i].append
		for j in range(len(problem[i])):
			space = problem[i][j]
			if space == GOAL:
				append2(CLEAR)
				appendg((i, j))
			elif space == PLAYER:
				append2(CLEAR)
				player = (i, j)
			elif space == BLOCK:
				appendb((i, j))
				append2(CLEAR)
			else:
				append2(space)
	return list2tuple(parsed_problem), tuple(goals), player, tuple(blocks)
	
with open(args.problem, 'r') as problem_file:
	problem = list(map(lambda x: list(x),problem_file.read().split('\n')))[:-1]

problem, goals, player, blocks = parseProblem(problem)

if args.perf:
	import cProfile
	command = args.algorithm + '(problem, goals, player, blocks)'
	cProfile.run(command, 'algo.profile')

	import pstats
	stats = pstats.Stats('algo.profile')
	stats.strip_dirs().sort_stats('time').print_stats()
else:
	startTime = time()
	if args.algorithm == 'bfs':
		solution = bfs(problem, goals, player, blocks)
	elif args.algorithm == 'dfs':
		solution = dfs(problem, goals, player, blocks)
	elif args.algorithm == 'rbfs':
		solution = rbfs(problem, goals, player, blocks)
	elif args.algorithm =='rdfs':
		solution = rdfs(problem, goals, player, blocks)
	elif args.algorithm == 'bbfs':
		solution = bbfs(problem, goals, player, blocks)
	elif args.algorithm == 'bdfs':
		solution = bdfs(problem, goals, player, blocks)
	elif args.algorithm == 'bastar':
		solution = bastar(problem, goals, player, blocks)
	else:
		solution = astar(problem, goals, player, blocks)
	time_info ='time(s):' + str(time() - startTime)
	state_info ='states:' + str(algorithms.iterations) 
	step_info = "steps:" + str(len(solution[SACTIONS])) 
	if args.min:
		if solution == None:
			print("No solution")
		else:
			print(args.algorithm + ':' + args.problem + ', ' + time_info + ', ' + state_info + ', ' + step_info)
	else:
		print(time_info)
		print(state_info)
		if solution == None:
			print("No solution")
		elif args.frames:
			for action in solution[SACTIONS]:
				player, blocks, _ = successors([action[ADIRECTION]], problem, player, blocks, [])[0]
				print(strAction(action) + ':')
				print(strState(problem, player, blocks))
		else:
			print(strNode(problem, solution))

