from variables import *

MAN_MEMO = {} 

def absManDist(d1, d2):
	key = (d1, d2)
	if key in MAN_MEMO:
		return MAN_MEMO[key]
	x = d1[0] - d2[0]
	y =d1[1] - d2[1]
	if x < 0:
		x = -x
	if y < 0:
		y = -y
	ret = x + y
	MAN_MEMO[key] = ret
	return ret

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
	for i in range(1, len(smap) - 1):
		for j in range(1, len(smap[i]) - 1):
			if (i, j) in goals or smap[i][j] != CLEAR: 
				continue
			x = False
			y = False
			if smap[i + 1][j] != CLEAR:
				x = True
			if smap[i - 1][j] != CLEAR:
				x = True
			if smap[i][j + 1] != CLEAR:
				y = True
			if smap[i][j - 1] != CLEAR:
				y = True
			if x and y:
				append((i, j))
	return tuple(dead)

def deadSpotHeuristic(blocks, dead):
	for block in blocks:
		if block in dead:
			return 10000
	return 0

def blockDistanceHeuristic(player, blocks):
	h = 0
	for block in blocks:
		h = h + absManDist(player, block)
	return h

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

def mstHeuristic(player, blocks, goals):
	pointsList = list(goals) + blocks
	pointsList.append(player)
	points = set(pointsList)
	target = len(points)
	ds = [(0, player)]
	dsadd = heapq.heappush
	dspop = heapq.heappop
	visited = set([])
	vadd = visited.add
	premove = points.remove
	h = 0
	while ds:
		p, current = dspop(ds)
		if current in visited:
			continue
		vadd(current)
		h = h + p
		if len(visited) == target:
			return h
		premove(current)
		for point in points:
			e = absManDist(current, point)
			dsadd(ds, (e, point))
