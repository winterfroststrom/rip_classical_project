import heapq
from collections import deque
from variables import *
from heuristics import *
from algorithms_util import *
from random import choice

iterations = 0

def dbfs(smap, goals, player, blocks, ds, addDs):
	global iterations
	start = (player, blocks, [])
	addDs(start)
	visited = set([])
	vadd = visited.add
	dead = findDeadSpots(smap, goals)
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
			if deadSpotHeuristic(successor[SBLOCKS], dead):
				continue
			addDs(successor)

def bfs(initial_state, goals, player, blocks):
	ds = deque([])
	append = ds.appendleft
	return dbfs(initial_state, goals, player, list(blocks), ds, append)


def dfs(initial_state, goals, player, blocks):
	ds = []
	return dbfs(initial_state, goals, player, list(blocks), ds, ds.append)

def rbfs(initial_state, goals, player, blocks):
	ds = deque([])
	append = ds.appendleft
	return rdbfs(initial_state, goals, player, list(blocks), ds, append)

def rdfs(initial_state, goals, player, blocks):
	ds = []
	return rdbfs(initial_state, goals, player, list(blocks), ds, ds.append)

def rdbfs(smap, blocks, player, goals, ds, dsadd):
	global iterations
	start = (player, list(blocks), [])
	dspop = ds.pop
	dsadd(start)
	visited = set([])
	vadd = visited.add
	while ds:
		state = dspop()
		visit = (state[SPLAYER], tuple(sorted(state[SBLOCKS])))
		if visit in visited:
			continue
		iterations = iterations + 1
		vadd(visit)
		if goalsMet(state[SBLOCKS], goals) and player == state[SPLAYER]:
			state[SACTIONS].reverse()
			return state
		succs = rsuccessors(DIRECTIONS, smap, *state)
		for successor in succs:
			dsadd(successor)

def h0Heuristic(smap, goals, player, blocks):
	global iterations
	h = []
	it = iterations
	for block in blocks:
		sol = bfs(smap, goals, player, [block])
		if sol != None:
			h.append(len(sol[SACTIONS]))
	iterations = it
	if len(h) == 0:
		return 10000
	return sum(h)

def h1Heuristic(smap, goals, player, blocks):
	global iterations
	it = iterations
	h = -1
	if goalsMet(blocks, goals):
		return 0
	for block in blocks:
		if not block in goals:
			sol = bfs(smap, goals, player, [block])
			if sol != None:
				h = max(len(sol[SACTIONS]), h)
	iterations = it
	if h == -1:
		return 10000
	return h

def h2Heuristic(smap, goals, player, blocks):
	global iterations
	it = iterations
	h = -1
	if goalsMet(blocks, goals):
		return 0
	for block1 in blocks:
		for block2 in blocks:
			if block1 != block2:
				sol = bfs(smap, goals, player, [block1, block2])
				if sol != None:
					h = max(len(sol[SACTIONS]), h)
	iterations = it
	if h == -1:
		return 10000
	return h



def astar(smap, goals, player, blocks):
	global iterations
	start = (player, list(blocks), [])
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
			if deadSpotHeuristic(successor[SBLOCKS], dead):	
				continue
			#h = 0 
			#h = h0Heuristic(smap, goals, successor[SPLAYER], successor[SBLOCKS])
			#h = h1Heuristic(smap, goals, successor[SPLAYER], successor[SBLOCKS])
			#h = h2Heuristic(smap, goals, successor[SPLAYER], successor[SBLOCKS])
			h = blockDistanceHeuristic(successor[SPLAYER], successor[SBLOCKS])
			#h = deadSpotHeuristic(successor[SBLOCKS], dead)
			#h = h + mstHeuristic(state[SPLAYER], state[SBLOCKS], (()))
			#h = minGoalHeuristic(state, goals)
			#h = nearestPairHeuristic(successor[SBLOCKS], goals)
			#h = deadAndNearestHeuristic(successor[SBLOCKS], dead, goals)
			f = g + h
			dsadd(ds, (f, successor))

def bastar(smap, goals, player, blocks):
	global iterations
	a_start = (player, list(blocks), [])
	a_ds = []
	a_dsadd = heapq.heappush
	a_dspop = heapq.heappop
	a_dsadd(a_ds, (0, a_start))
	a_visited = {}
	a_goals = goals
	dead = findDeadSpots(smap, a_goals)
	b_start = (player, list(goals), [])
	b_ds = deque([])
	b_dsadd = b_ds.appendleft
	b_dspop = b_ds.pop
	b_dsadd(b_start)
	b_visited = {}
	b_goals = blocks
	while a_ds and b_ds:
		_, a_state = a_dspop(a_ds)
		a_visit = (a_state[SPLAYER], tuple(sorted(a_state[SBLOCKS])))
		if a_visit in a_visited:
			continue
		iterations = iterations + 1
		a_visited[a_visit] = a_state
		if a_visit in b_visited:
			b_state = b_visited[a_visit]
			b_state[SACTIONS].reverse()
			return (player, b_goals, a_state[SACTIONS] + b_state[SACTIONS])
		if goalsMet(a_state[SBLOCKS], a_goals):
			return a_state
		a_succs = successors(DIRECTIONS, smap, *a_state)
		g = len(a_state[SACTIONS]) + 1
		for successor in a_succs:
			if deadSpotHeuristic(successor[SBLOCKS], dead):
				continue
			h = blockDistanceHeuristic(successor[SPLAYER], successor[SBLOCKS])
			f = g + h
			a_dsadd(a_ds, (f, successor))
		b_state = b_dspop()
		b_visit = (b_state[SPLAYER], tuple(sorted(b_state[SBLOCKS])))
		if b_visit in b_visited:
			continue
		iterations = iterations + 1
		b_visited[b_visit] = b_state
		if b_visit in a_visited:
			a_state = a_visited[b_visit]
			b_state[SACTIONS].reverse()
			return (player, b_goals, a_state[SACTIONS] + b_state[SACTIONS])
		if goalsMet(b_state[SBLOCKS], b_goals) and player == b_state[SPLAYER]:
			b_state[SACTIONS].reverse()
			return b_state
		b_succs = rsuccessors(DIRECTIONS, smap, *b_state)
		for successor in b_succs:
			b_dsadd(successor)

def bbfs(smap, goals, player, blocks):
	a_ds = deque([])
	a_dsadd = a_ds.appendleft
	b_ds = deque([])
	b_dsadd = b_ds.appendleft
	return bdbfs(smap, goals, player, blocks, a_ds, a_dsadd, b_ds, b_dsadd)

def bdfs(smap, goals, player, blocks):
	a_ds = []
	a_dsadd = a_ds.append
	b_ds = []
	b_dsadd = b_ds.append
	return bdbfs(smap, goals, player, blocks, a_ds, a_dsadd, b_ds, b_dsadd)


def bdbfs(smap, goals, player, blocks, a_ds, a_dsadd, b_ds, b_dsadd):
	global iterations
	a_start = (player, list(blocks), [])
	a_dspop = a_ds.pop
	a_dsadd(a_start)
	a_visited = {}
	a_goals = goals
	dead = findDeadSpots(smap, a_goals)
	b_start = (player, list(goals), [])
	b_dspop = b_ds.pop
	b_dsadd(b_start)
	b_visited = {}
	b_goals = blocks
	while a_ds and b_ds:
		a_state = a_dspop()
		a_visit = (a_state[SPLAYER], tuple(sorted(a_state[SBLOCKS])))
		if a_visit in a_visited:
			continue
		iterations = iterations + 1
		a_visited[a_visit] = a_state
		if a_visit in b_visited:
			b_state = b_visited[a_visit]
			b_state[SACTIONS].reverse()
			return (player, b_goals, a_state[SACTIONS] + b_state[SACTIONS])
		if goalsMet(a_state[SBLOCKS], a_goals):
			return a_state
		a_succs = successors(DIRECTIONS, smap, *a_state)
		g = len(a_state[SACTIONS]) + 1
		for successor in a_succs:
			if deadSpotHeuristic(successor[SBLOCKS], dead):
				continue
			a_dsadd(successor)
		b_state = b_dspop()
		b_visit = (b_state[SPLAYER], tuple(sorted(b_state[SBLOCKS])))
		if b_visit in b_visited:
			continue
		iterations = iterations + 1
		b_visited[b_visit] = b_state
		if b_visit in a_visited:
			a_state = a_visited[b_visit]
			b_state[SACTIONS].reverse()
			return (player, b_goals, a_state[SACTIONS] + b_state[SACTIONS])
		if goalsMet(b_state[SBLOCKS], b_goals) and player == b_state[SPLAYER]:
			b_state[SACTIONS].reverse()
			return b_state
		b_succs = rsuccessors(DIRECTIONS, smap, *b_state)
		for successor in b_succs:
			b_dsadd(successor)

