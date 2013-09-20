import argparse

parser = argparse.ArgumentParser(description='Solve Sokoban with A*.')
parser.add_argument('problem', help='problem file for sokoban')
parser.add_argument('-frames', help='show frames', action="store_true")
args = parser.parse_args()


def list2tuple(l):
	return tuple(map(lambda x: tuple(x), l))

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
	DIRECTIONS = [NORTH, SOUTH, EAST, WEST]
	
	@staticmethod
	def allBut(direction):
		return [x for x in DIRECTIONS if x != direction]
	
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
	copy = []
	for i in range(len(state)):
		copy.append([])
		for j in range(len(state[i])):
			copy[i].append(state[i][j])
	return copy

def createSuccessor(state, player, actions, action):
	successor = copyState(state)
	successor[player[0]][player[1]] = ' '
	if action[0] == ACTIONS.MOVE:
		setDirectionOf(successor, player, action[1], '@')
	elif action[0] == ACTIONS.PUSH:
		setDirectionOf(successor, player, action[1], '@')
		setDirectionOf(successor, player, composeDirection(action[1], action[1]), '*')
	return (list2tuple(successor), composeDirection(player, action[1]), actions + [action])

def successors(state, player, actions):
	successors = []
	for direction in DIRECTIONS.DIRECTIONS:
		space = directionOf(state, player, direction) 
		if clear(space):
			action = (ACTIONS.MOVE, direction)
			successors.append((createSuccessor(state, player, actions, action)))
		elif block(space):
			if clear(directionOf(state, player, composeDirection(direction, direction))):
				action = (ACTIONS.PUSH, direction)
				successors.append(createSuccessor(state, player, actions, action))
	return successors


def strAction(action):
	return '(' + ACTIONS.string(action[0]) + ',' + DIRECTIONS.string(action[1]) + ')'

def strSuccessor(successor):
	return 'ACTIONS: '+ ''.join(map(lambda x: strAction(x), successor[2])) + ' STATE: \n' + strState(successor[0])

def goalsMet(state, goals):
	for goal in goals:
		if state[goal[0]][goal[1]] != '*':
			return False
	return True

class Successor:
	def __init__(self, successor):
		self.successor = successor

	def __eq__(self, other):
		return isinstance(other, self.__class__) and self.successor[0] == other.successor[0]

	def __ne__(self, other):
		return not self.__eq__(other)
	
	def __hash__(self):
		return hash(self.successor[0])
	
	def __str__(self):
		return strSuccessor(self.successor)

def bfs(initial_state, goals, player):
	start = (initial_state, player, [])
	ds = [start]
	visited = set([])
	while ds:
		state = ds.pop()
		if Successor(state) in visited:
			continue
		visited = visited | set([Successor(state)])
		if goalsMet(state[0], goals):
			return state
		succs = successors(*state)
		for successor in succs:
			ds.append(successor)

def astar(state, goals):
	pass

with open(args.problem, 'r') as problem_file:
	problem = map(lambda x: list(x),problem_file.read().split('\n'))

problem, goals, player = parseProblem(problem)




print(strState(problem))
#print(player)
#ss = successors(problem, player, [])
#for s in ss:
#	print(strSuccessor(s))
solution = bfs(problem, goals, player)

if args.frames:
	state = problem
	for action in solution[2]:
		state, player, _ = createSuccessor(state, player, [], action)
		print(strAction(action) + ':')
		print(strState(state))
else:
	print(strSuccessor(solution))
