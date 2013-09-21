import argparse
from collections import deque
from time import time

parser = argparse.ArgumentParser(description='Solve Sokoban with A*.')
parser.add_argument('problem', help='problem file for sokoban')
parser.add_argument('-frames', help='show frames', action="store_true")

args = parser.parse_args()

def parseProblem(problem):
	parsed_problem = []
	goals = []
	for i in range(len(problem)):
		parsed_problem.append([])
		for j in range(len(problem[i])):
			if problem[i][j] == '?':
				parsed_problem[i].append(' ')
				goals.append((i, j))
			elif problem[i][j] == '@':
				parsed_problem[i].append('@')
				player = (i, j)
			else:
				parsed_problem[i].append(problem[i][j])
	return Successor(State(parsed_problem), player, []), tuple(goals)

class State(object):
	def __init__(self, state):
		self.state = tuple(map(lambda x: tuple(x), state))
	
	def __str__(self):
		return ''.join(map(lambda x : ''.join(x) + '\n', self.state)).rstrip()

	def __eq__(self, other):
		return self.state == other.state
	
	def __hash__(self):
		return hash(self.state)

	def __getitem__(self, key):
		if type(key) is Vector or type(key) is tuple:
			return self.state[key[0]][key[1]]
		return self.state[key]

	def copyAsList(self):
		copy = []
		for i in range(len(self.state)):
			copy.append([])
			for j in range(len(self.state[i])):
				copy[i].append(self.state[i][j])
		return copy

class ActionType(object):

	def __init__(self, action_type):
		self.action_type = action_type

	def __str__(self):
		if self.__eq__(ActionType.MOVE):
			return 'MOVE'
		elif self.__eq__(ActionType.PUSH):
			return 'PUSH'
	
	def __eq__(self, other):
		return self.action_type == other.action_type

ActionType.MOVE = ActionType(0)
ActionType.PUSH = ActionType(1)
		
class Vector(object):


	def __init__(self, drow, dcol, name = "VECTOR"):
		self.vector = (drow, dcol)
		self.mem_add = {}
		self.name = name

	def __add__(self, other):
		if type(other) is tuple:
			return Vector(self.vector[0] + other[0], self.vector[1] + other[1])
		elif other in self.mem_add:
			return self.mem_add[other]
		else:
			self.mem_add[other] = Vector(self.vector[0] + other.vector[0], self.vector[1] + other.vector[1])
			return self.mem_add[other]

	def __eq__(self, other):
		return self.vector == other.vector
	
	def __hash__(self):
		return hash(self.vector)

	def allBut(self):
		return Vector.ALLBUT[self]
	
	def __getitem__(self, key):
		return self.vector[key]
	
	def __str__(self):
		return self.name
	
	def reverse(self):
		if self in Vector.REVERSE:
			return Vector.REVERSE[self]
		else:
			Vector.REVERSE[self] = Vector(-self.vector[0], -self.vector[1])
			return Vector.REVERSE[self]
Vector.NORTH = Vector(-1, 0, "NORTH")
Vector.SOUTH = Vector(1, 0, "SOUTH")
Vector.EAST = Vector(0, 1, "EAST")
Vector.WEST = Vector(0, -1, "WEST")
Vector.DIRECTIONS = [Vector.NORTH, Vector.SOUTH, Vector.EAST, Vector.WEST]
Vector.ALLBUT = {Vector.NORTH : (Vector.SOUTH, Vector.EAST, Vector.WEST), Vector.SOUTH : (Vector.NORTH, Vector.EAST, Vector.WEST), Vector.EAST : (Vector.NORTH, Vector.SOUTH, Vector.WEST), Vector.WEST : (Vector.NORTH, Vector.SOUTH, Vector.EAST)}
Vector.REVERSE = {Vector.NORTH : Vector.SOUTH, Vector.EAST : Vector.WEST, Vector.SOUTH : Vector.NORTH, Vector.WEST : Vector.EAST}
	
def setDList(state, vector, item):
	state[vector[0]][vector[1]] = item

class Action:
	def __init__(self, action_type, vector):
		self.action_type = action_type
		self.vector = vector
	
	def __str__(self):
		return '(' + str(self.action_type) + ',' + str(self.vector) + ')'


class Successor:
	def __init__(self, state, player, actions):
		self.state = state
		self.player = player
		self.actions = actions

	def __eq__(self, other):
		return isinstance(other, self.__class__) and self.successor[0] == other.successor[0]

	def __ne__(self, other):
		return not self.__eq__(other)
	
	def __hash__(self):
		return hash(self.state)
	
	def __str__(self):
		return 'ACTIONS ('+str(len(self.actions)) + '): '+''.join(map(lambda x: str(x), self.actions))+' STATE: \n'+str(self.state)
	
	def successor(self, action):
		new_state = self.state.copyAsList()
		setDList(new_state, self.player, ' ')
		new_player = action.vector + self.player
		if action.action_type == ActionType.MOVE:
			setDList(new_state, action.vector + self.player, '@')
		elif action.action_type == ActionType.PUSH:
			setDList(new_state, new_player, '@')
			setDList(new_state, action.vector + action.vector + self.player, '*')
		return Successor(State(new_state), new_player, self.actions + [action])

	def successors(self):
		successors = []
		for direction in Vector.DIRECTIONS:
			space = self.state[direction + self.player] 
			if clear(space):
				successors.append(self.successor(Action(ActionType.MOVE, direction)))
			elif block(space):
				if clear(self.state[direction + direction + self.player]):
					successors.append(self.successor(Action(ActionType.PUSH, direction)))
		return successors


def clear(ch):
	return ch == ' '

def block(ch):
	return ch == '*'


def goalsMet(state, goals):
	for goal in goals:
		if state[goal] != '*':
			return False
	return True

def bfs(start, goals):
	ds = deque([start])
	visited = set([])
	while ds:
		current = ds.pop()
		if current.state in visited:
			continue
		visited.add(current.state)
		if goalsMet(current.state, goals):
			return current
		succs = current.successors()
		for successor in succs:
			ds.appendleft(successor)

def astar(state, goals):
	pass

with open(args.problem, 'r') as problem_file:
	problem = map(lambda x: list(x),problem_file.read().split('\n'))

initial_problem, goals = parseProblem(problem)

import cProfile
cProfile.run('bfs(initial_problem, goals)', 'bfs.profile')

import pstats
stats = pstats.Stats('bfs.profile')
stats.strip_dirs().sort_stats('time').print_stats()


startTime = time()
solution = bfs(initial_problem, goals)
print("Time (s): " + str(time() - startTime))
if args.frames:
	state = initial_problem
	for action in solution.actions:
		state = state.successor(action)
		print(state.action + ':')
		print(state.state)
else:
	print(solution)

