from variables import *

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

