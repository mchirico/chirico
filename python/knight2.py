#!/usr/bin/env python

# Reference: http://ttsiodras.googlepages.com/knight2.py

import sys

sys.setrecursionlimit(12000)

g_sqSize = -1	# the board size, passed at runtime
g_board = []	# the board will be constructed as a list of lists

def main():
    global g_sqSize
    if len(sys.argv) != 2:
	g_sqSize = 8  # Default: Fill the normal 8x8 chess board
    else:
	try: g_sqSize = int(sys.argv[1]) # or, the NxN the user wants
	except:
	    print "Usage: " + sys.argv[0] + " <squareSize>"
	    sys.exit(1)
    for i in xrange(0, g_sqSize):
	g_board.append(g_sqSize*[0])  # Fill the board with zeroes
    Fill(0,0,1)    # Start the recursion with a 1 in the upper left
    print "No solution found"  # if the recursion returns, it failed

def InRangeAndEmpty(ty,tx):  # check if coordinates are within the board
    return ty>=0 and tx>=0 and ty<g_sqSize and tx<g_sqSize \
	and g_board[ty][tx] == 0 # and the square is empty

def Fill(y,x,counter): # The recursive function that fills the board
    assert g_board[y][x] == 0
    g_board[y][x] = counter          # Fill the square
    if counter == g_sqSize*g_sqSize: # Was this the last empty square?
	PrintBoard()                 # Yes, print the board...
	sys.exit(1)                  # ...and exit

    emptyNeighbours = []  # find our empty neighbours for the recursion
    jumps = ((-2,1),(-1,2),(1,2),(2,1),(2,-1),(1,-2),(-1,-2),(-2,-1))
    for jump in jumps:
	ty,tx = y + jump[0], x + jump[1]
	if InRangeAndEmpty(ty,tx):
	    emptyNeighbours.append([ty,tx])

    # recurse using our neighbours, trying first the ones with the 
    # least amount of free neighbours, i.e. the "loners"
    for ty,tx in sorted(emptyNeighbours, key=lambda c: reduce(
	lambda x,y: x+y, 
	map(lambda j: InRangeAndEmpty(c[0]+j[0], c[1]+j[1]) and 1 or 0, 
	    jumps))):
	Fill(ty,tx,counter+1)

    g_board[y][x] = 0 # if we get here, all the neighbours failed,
                      # so reset the square and return

def PrintBoard(): # print the board using nice ASCII art ('+' and '-')
    scale = len(str(g_sqSize*g_sqSize))
    print g_sqSize*("+" + scale*"-") + "+"
    for line in g_board:
	for elem in line:
	    sys.stdout.write("|%*d" % (scale,elem))
	print "|\n"+g_sqSize*("+" + scale*"-") + "+"

if __name__ == "__main__":
    main()
