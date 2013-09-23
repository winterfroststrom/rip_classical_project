from variables import *

def goalsMet(blocks, goals):
	for block in blocks:
		if not block in goals:
			return False
	return True

def rsuccessors(directions, smap, player, blocks, actions):
	successors = []
	append = successors.append
	px = player[0]
	py = player[1]
	for direction in directions:
		dx = direction[0]
		dy = direction[1]
		nx = px - dx
		ny = py - dy
		nextPlayer = (nx, ny)
		if smap[nx][ny] == CLEAR and not nextPlayer in blocks:
			actionsCopy = actions[:]
			actionsCopy.append((MOVE, direction))
			append((nextPlayer, blocks, actionsCopy))
			prevBlock = (px + dx, py + dy)
			if prevBlock in blocks:
				actionsCopy = actions[:]
				actionsCopy.append((PUSH, direction))
				newBlocks = [block for block in blocks if block != prevBlock]
				newBlocks.append(player)
				append((nextPlayer, newBlocks, actionsCopy))
	return successors

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
