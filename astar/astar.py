import argparse
from collections import deque
from time import time

parser = argparse.ArgumentParser(description='Solve Sokoban with A*.')
parser.add_argument('problem', help='problem file for sokoban')
parser.add_argument('-algorithm', help='BFS|DFS')
parser.add_argument('-frames', help='show frames', action="store_true")
args = parser.parse_args()


def list2tuple(l):
	return tuple(map(tuple, l))

def parseProblem(problem):
	parsed_problem = []
	goals = []
	append1 = parsed_problem.append
	appendg = goals.append
	for i in range(len(problem)):
		append1([])
		append2 = parsed_problem[i].append
		for j in range(len(problem[i])):
			if problem[i][j] == '?':
				append2(' ')
				appendg((i, j))
			elif problem[i][j] == '@':
				append2('@')
				player = (i, j)
			else:
				append2(problem[i][j])
	return list2tuple(parsed_problem), tuple(goals), player

def strState(problem):
	return ''.join(map(lambda x : ''.join(x) + '\n', problem)).rstrip()

class ACTIONS:
	MOVE = 0
	PUSH = 1
	
	@staticmethod
	def string(action):
		if action == ACTIONS.MOVE:
			return 'MOVE'
		elif action == ACTIONS.PUSH:
			return 'PUSH'

class DIRECTIONS:
	NORTH = (-1, 0)
	SOUTH = (1, 0)
	EAST = (0, 1)
	WEST = (0, -1)
	ALLDIRECTIONS = [NORTH, SOUTH, EAST, WEST]
	ALLBUT = {NORTH : (SOUTH, EAST, WEST),SOUTH : (NORTH, EAST, WEST),EAST : (NORTH, SOUTH, WEST),WEST : (NORTH, SOUTH, EAST) }

	@staticmethod
	def allBut(direction):
		return DIRECTIONS.ALLBUT[direction]
	
	@staticmethod
	def string(direction):
		if direction == DIRECTIONS.NORTH:
			return "NORTH"
		elif direction == DIRECTIONS.SOUTH:
			return "SOUTH"
		elif direction == DIRECTIONS.EAST:
			return "EAST"
		elif direction == DIRECTIONS.WEST:
			return "WEST"

def reverseOf(direction):
	return (-direction[0], -direction[1])


def directionOf(problem, position, direction):
	return problem[position[0] + direction[0]][position[1] + direction[1]]

def setDirectionOf(problem, position, direction, item):
	problem[position[0] + direction[0]][position[1] + direction[1]] = item

def composeDirection(direction1, direction2):
	return (direction1[0] + direction2[0], direction1[1] + direction2[1])

def clear(ch):
	return ch == ' '

def block(ch):
	return ch == '*';

def copyState(state):
	return list(map(list, state))

def createSuccessor(state, player, actions, action):
	successor = copyState(state)
	p0 = player[0]
	p1 = player[1]
	a1 = action[1]
	aa0 = a1[0]
	aa1 = a1[1]
	successor[p0][p1] = ' '
	x1 = p0 + aa0
	y1 = p1 + aa1
	successor[x1][y1] = '@'
	if action[0] == ACTIONS.PUSH:
		successor[x1 + aa0][y1 + aa1] = '*'
	act = actions[:]
	act.append(action)
	return (list2tuple(successor), (x1, y1), act)


def successors(state, player, actions):
	successors = []
	append = successors.append
	for direction in DIRECTIONS.ALLDIRECTIONS:
		space = directionOf(state, player, direction) 
		if clear(space):
			action = (ACTIONS.MOVE, direction)
			append((createSuccessor(state, player, actions, action)))
		elif block(space):
			if clear(directionOf(state, player, composeDirection(direction, direction))):
				action = (ACTIONS.PUSH, direction)
				append(createSuccessor(state, player, actions, action))
	return successors


def strAction(action):
	return '(' + ACTIONS.string(action[0]) + ',' + DIRECTIONS.string(action[1]) + ')'

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

def bdfs(initial_state, goals, player, ds, addDs):
	global iterations
	start = (initial_state, player, [])
	addDs(start)
	visited = set([])
	vadd = visited.add
	while ds:
		state = ds.pop()
		if Successor(state) in visited:
			continue
		iterations = iterations + 1
		vadd(Successor(state))
		if goalsMet(state[0], goals):
			return state
		succs = successors(*state)
		for successor in succs:
			addDs(successor)

def bfs(initial_state, goals, player):
	ds = deque([])
	append = ds.appendleft
	return bdfs(initial_state, goals, player,ds, append)


def dfs(initial_state, goals, player):
	ds = []
	return bdfs(initial_state, goals, player, ds, ds.append)



def astar(state, goals):
	pass

with open(args.problem, 'r') as problem_file:
	problem = map(lambda x: list(x),problem_file.read().split('\n'))

problem, goals, player = parseProblem(problem)
"""
import cProfile
cProfile.run('bfs(problem, goals, player)', 'bfs.profile')

import pstats
stats = pstats.Stats('bfs.profile')
stats.strip_dirs().sort_stats('time').print_stats()
"""

if args.algorithm == 'DFS':
	startTime = time()
	solution = dfs(problem, goals, player)
else:
	startTime = time()
	solution = bfs(problem, goals, player)
	
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
