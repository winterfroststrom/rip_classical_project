Please run this command at least once before using the script:
python astar.py -h

Example of usage:
python astar.py problem1.txt -algorithm bdfs

To change astar heuristics (this will not affect bastar), go into the algorithms.py file and edit the commented code in the astar function.

Note, the lazy implementation of reversed and bidirectional searches start the search in the initial position, which means they aren't complete or optimal.
