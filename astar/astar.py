import argparse, heapq
from collections import deque
from time import time

parser = argparse.ArgumentParser(description='Solve Sokoban with A*.')
parser.add_argument('problem', help='problem file for sokoban')
parser.add_argument('-algorithm', help='algorithm to use', choices=['astar', 'bfs', 'dfs'], default='astar')
parser.add_argument('-frames', help='show frames', action="store_true")
parser.add_argument('-perf', help='show performance data', action='store_true')
args = parser.parse_args()

CLEAR = ' '
BLOCK = '*'
PLAYER = '@'
GOAL = '?'
MOVE = 0
PUSH = 1
NORTH = (-1, 0, (-2, 0))
SOUTH = (1, 0, (2, 0))
EAST = (0, 1, (0, 2))
WEST = (0, -1, (0, -2))
DIRECTIONS = (NORTH, SOUTH, EAST, WEST)
ALL_DIRECTIONS_BUT = {NORTH : (SOUTH, EAST, WEST),SOUTH : (NORTH, EAST, WEST),EAST : (NORTH, SOUTH, WEST),WEST : (NORTH, SOUTH, EAST) }


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
				append2(PLAYER)
				player = (i, j)
			elif space == BLOCK:
				appendb((i, j))
				append2(space)
			else:
				append2(space)
	return list2tuple(parsed_problem), tuple(goals), player, blocks

def copyState(state):
	return list(map(list, state))

def createSuccessor(state, player, actions, action):
	successor = copyState(state)
	p0 = player[0]
	p1 = player[1]
	a1 = action[1]
	aa0 = a1[0]
	aa1 = a1[1]
	successor[p0][p1] = CLEAR
	x1 = p0 + aa0
	y1 = p1 + aa1
	successor[x1][y1] = PLAYER
	if action[0]:#PUSH is 1, which evals to True
		successor[x1 + aa0][y1 + aa1] = BLOCK
	act = actions[:]
	act.append(action)
	return (list2tuple(successor), (x1, y1), act)


def successors(state, player, actions):
	successors = []
	append = successors.append
	px = player[0]
	py = player[1]
	for direction in DIRECTIONS:
		space = state[px + direction[0]][py + direction[1]]
		if space == CLEAR:
			action = (MOVE, direction)
			append((createSuccessor(state, player, actions, action)))
		elif space == BLOCK:
			if state[px + direction[2][0]][py + direction[2][1]] == CLEAR:
				action = (PUSH, direction)
				append(createSuccessor(state, player, actions, action))
	return successors

def strState(problem):
	return ''.join(map(lambda x : ''.join(x) + '\n', problem)).rstrip()


def stringA(action):
	if action == MOVE:
		return 'MOVE'
	elif action == PUSH:
		return 'PUSH'

def stringD(direction):
	if direction == NORTH:
		return "NORTH"
	elif direction == SOUTH:
		return "SOUTH"
	elif direction == EAST:
		return "EAST"
	elif direction == WEST:
		return "WEST"

def strAction(action):
	return '(' + stringA(action[0]) + ',' + stringD(action[1]) + ')'

def strSuccessor(successor):
	return 'ACTIONS (' + str(len(successor[2])) + '): ' + ''.join(map(lambda x: strAction(x), successor[2])) + ' STATE: \n' + strState(successor[0])

def goalsMet(state, goals):
	for goal in goals:
		if state[goal[0]][goal[1]] != '*':
			return False
	return True

class Successor:
	def __init__(self, successor):
		self.successor = successor

	def __eq__(self, other):
		return self.successor[0] == other.successor[0]

	def __ne__(self, other):
		return not self.__eq__(other)
	
	def __hash__(self):
		return hash(self.successor[0])
	
	def __str__(self):
		return strSuccessor(self.successor)

iterations = 0

def bdfs(initial_state, goals, player, blocks, ds, addDs):
	global iterations
	start = (initial_state, player, [])
	addDs(start)
	visited = set([])
	vadd = visited.add
	while ds:
		state = ds.pop()
		visit = Successor(state)
		if visit in visited:
			continue
		iterations = iterations + 1
		vadd(visit)
		if goalsMet(state[0], goals):
			return state
		succs = successors(*state)
		for successor in succs:
			addDs(successor)

def bfs(initial_state, goals, player, blocks):
	ds = deque([])
	append = ds.appendleft
	return bdfs(initial_state, goals, player, blocks, ds, append)


def dfs(initial_state, goals, player, blocks):
	ds = []
	return bdfs(initial_state, goals, player, blocks, ds, ds.append)

def absManDist(d1, d2):
	x = d1[0] - d2[0]
	y =d1[1] - d2[1]
	if x < 0:
		x = -x
	if y < 0:
		y = -y
	return x + y

def minGoalHeuristic(state, goals):
	player = state[1]
	h = 10000
	for goal in goals:
		th = absManDist(player, goal)
		if th < h:
			h = th
	return h

def astar(initial_state, goals, player, blocks):
	global iterations
	start = (initial_state, player, [])
	ds = []
	dsadd = heapq.heappush
	dspop = heapq.heappop
	dsadd(ds, (0, start))
	visited = set([])
	vadd = visited.add
	while ds:
		_, state = dspop(ds)
		visit = Successor(state)
		if visit in visited:
			continue
		iterations = iterations + 1
		vadd(visit)
		if goalsMet(state[0], goals):
			return state
		succs = successors(*state)
		g = len(state[2]) + 1
		for successor in succs:
			player = successor[1]
			h = minGoalHeuristic(state, goals)
			f = g + h
			dsadd(ds, (f, successor))

with open(args.problem, 'r') as problem_file:
	problem = list(map(lambda x: list(x),problem_file.read().split('\n')))

problem, goals, player, blocks = parseProblem(problem)
if args.perf:
	import cProfile
	command = args.algorithm + '(problem, goals, player, blocks)'
	cProfile.run(command, 'algo.profile')

	import pstats
	stats = pstats.Stats('algo.profile')
	stats.strip_dirs().sort_stats('time').print_stats()
else:
	if args.algorithm == 'bfs':
		startTime = time()
		solution = bfs(problem, goals, player, blocks)
	elif args.algorithm == 'dfs':
		startTime = time()
		solution = dfs(problem, goals, player, blocks)
	else:
		startTime = time()
		solution = astar(problem, goals, player, blocks)
	
	print('time(s):' + str(time() - startTime))
	print('states:' + str(iterations))
	if args.frames:
		state = problem
		for action in solution[2]:
			state, player, _ = createSuccessor(state, player, [], action)
			print(strAction(action) + ':')
			print(strState(state))
	else:
		print(strSuccessor(solution))

