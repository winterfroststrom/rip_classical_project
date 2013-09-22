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
NORTH = (-1, 0)
SOUTH = (1, 0)
EAST = (0, 1)
WEST = (0, -1)
DIRECTIONS = (NORTH, SOUTH, EAST, WEST)
ALL_DIRECTIONS_BUT = {NORTH : (SOUTH, EAST, WEST),SOUTH : (NORTH, EAST, WEST),EAST : (NORTH, SOUTH, WEST),WEST : (NORTH, SOUTH, EAST) }
SPLAYER = 0
SBLOCKS = 1
SACTIONS = 2
ATYPE = 0
ADIRECTION = 1

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
	return list2tuple(parsed_problem), tuple(goals), player, blocks

def successors(directions, smap, player, blocks, actions):
	successors = []
	append = successors.append
	px = player[0]
	py = player[1]
	for direction in directions:
		dx = direction[0]
		dy = direction[1]
		nx = px + dx
		ny = py + dy
		nextPlayer = (nx, ny)
		if nextPlayer in blocks:
			nnx = nx + dx
			nny = ny + dy
			nextBlock = (nnx, nny)
			if smap[nnx][nny] == CLEAR and not nextBlock in blocks:
				actionsCopy = actions[:]
				actionsCopy.append((PUSH, direction))
				newBlocks = [block for block in blocks if block != nextPlayer]
				newBlocks.append(nextBlock)
				append((nextPlayer, newBlocks, actionsCopy))
		elif smap[nx][ny] == CLEAR:
			actionsCopy = actions[:]
			actionsCopy.append((MOVE, direction))
			append((nextPlayer, blocks, actionsCopy))
	return successors

def strState(smap, splayer, sblocks):
	string = ''
	for i in range(len(smap)):
		for j in range(len(smap[i])):
			if (i, j) == splayer:
				string = string + PLAYER
			elif (i, j) in sblocks:
				string = string + BLOCK
			else:
				string = string + smap[i][j]
		string = string + '\n'
	return string.rstrip()


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
	return '(' + stringA(action[ATYPE]) + ',' + stringD(action[ADIRECTION]) + ')'

def strNode(smap, successor):
	return 'ACTIONS (' + str(len(successor[SACTIONS])) + '): ' + ''.join(map(lambda x: strAction(x), successor[SACTIONS])) + ' STATE: \n' + strState(smap, successor[SPLAYER], successor[SBLOCKS])

def goalsMet(blocks, goals):
	for block in blocks:
		if not block in goals:
			return False
	return True

iterations = 0

def bdfs(smap, goals, player, blocks, ds, addDs):
	global iterations
	start = (player, blocks, [])
	addDs(start)
	visited = set([])
	vadd = visited.add
	while ds:
		state = ds.pop()
		visit = (state[SPLAYER], tuple(sorted(state[SBLOCKS])))
		if visit in visited:
			continue
		iterations = iterations + 1
		vadd(visit)
		if goalsMet(state[SBLOCKS], goals):
			return state
		succs = successors(DIRECTIONS, smap, *state)
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
	player = state[SPLAYER]
	h = 10000
	for goal in goals:
		th = absManDist(player, goal)
		if th < h:
			h = th
	return h

def findDeadSpots(smap, goals):
	dead = []
	append = dead.append
	for i in range(len(smap) - 2, 1):
		for j in range(len(smap) - 2, 1):
			if smap[i][j] in goals: 
				continue
			walls = 0
			if smap[i + 1][j] != CLEAR and smap[i][j + 1] in goals:
				walls = walls + 1
			if smap[i - 1][j] != CLEAR and smap[i][j + 1] in goals:
				walls = walls + 1
			if smap[i][j + 1] != CLEAR and smap[i - 1][j] in goals:
				walls = walls + 1
			if smap[i][j - 1] != CLEAR and smap[i - 1][j] in goals:
				walls = walls + 1
			if walls > 1:
				append((i, j))
	return tuple(dead)

def deadSpotHeuristic(blocks, dead):
	for block in blocks:
		if block in dead:
			return 10000
	return 0

def nearestPairHeuristic(blocks, goals):
	h = 0
	for block in blocks:
		min_dist = 10000
		for goal in goals:
			d = absManDist(block, goal)
			if d < min_dist:
				min_dist = d
		h = h + min_dist
	return h

def deadAndNearestHeuristic(blocks, dead, goals):
	return deadSpotHeuristic(blocks, dead) + nearestPairHeuristic(blocks, goals)

def astar(smap, goals, player, blocks):
	global iterations
	start = (player, blocks, [])
	ds = []
	dsadd = heapq.heappush
	dspop = heapq.heappop
	dsadd(ds, (0, start))
	visited = set([])
	vadd = visited.add
	dead = findDeadSpots(smap, goals)
	while ds:
		_, state = dspop(ds)
		visit = (state[SPLAYER], tuple(sorted(state[SBLOCKS])))
		if visit in visited:
			continue
		iterations = iterations + 1
		vadd(visit)
		if goalsMet(state[SBLOCKS], goals):
			return state
		succs = successors(DIRECTIONS, smap, *state)
		g = len(state[SACTIONS]) + 1
		for successor in succs:
			h = deadSpotHeuristic(successor[SBLOCKS], dead)
			#h = minGoalHeuristic(state, goals)
			#h = nearestPairHeuristic(successor[SBLOCKS], goals)
			#h = deadAndNearestHeuristic(successor[SBLOCKS], dead, goals)
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
	if solution == None:
		print("No solution")
	elif args.frames:
		for action in solution[SACTIONS]:
			player, blocks, _ = successors([action[ADIRECTION]], problem, player, blocks, [])[0]
			print(strAction(action) + ':')
			print(strState(problem, player, blocks))
	else:
		print(strNode(problem, solution))

