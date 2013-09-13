begin_version
3
end_version
begin_metric
0
end_metric
8
begin_variable
var0
-1
2
Atom clear(d2)
NegatedAtom clear(d2)
end_variable
begin_variable
var1
-1
2
Atom clear(d3)
NegatedAtom clear(d3)
end_variable
begin_variable
var2
-1
2
Atom clear(p1)
NegatedAtom clear(p1)
end_variable
begin_variable
var3
-1
2
Atom clear(p2)
NegatedAtom clear(p2)
end_variable
begin_variable
var4
-1
2
Atom clear(p3)
NegatedAtom clear(p3)
end_variable
begin_variable
var5
-1
5
Atom on(d1, d2)
Atom on(d1, d3)
Atom on(d1, p1)
Atom on(d1, p2)
Atom on(d1, p3)
end_variable
begin_variable
var6
-1
4
Atom on(d2, d3)
Atom on(d2, p1)
Atom on(d2, p2)
Atom on(d2, p3)
end_variable
begin_variable
var7
-1
3
Atom on(d3, p1)
Atom on(d3, p2)
Atom on(d3, p3)
end_variable
8
begin_mutex_group
2
0 0
5 0
end_mutex_group
begin_mutex_group
3
1 0
5 1
6 0
end_mutex_group
begin_mutex_group
4
2 0
5 2
6 1
7 0
end_mutex_group
begin_mutex_group
4
3 0
5 3
6 2
7 1
end_mutex_group
begin_mutex_group
4
4 0
5 4
6 3
7 2
end_mutex_group
begin_mutex_group
5
5 0
5 1
5 2
5 3
5 4
end_mutex_group
begin_mutex_group
4
6 0
6 1
6 2
6 3
end_mutex_group
begin_mutex_group
3
7 0
7 1
7 2
end_mutex_group
begin_state
1
1
0
0
1
0
0
2
end_state
begin_goal
3
5 0
6 0
7 0
end_goal
38
begin_operator
move-disk d1 d2 d3
0
3
0 0 -1 0
0 1 0 1
0 5 0 1
0
end_operator
begin_operator
move-disk d1 d2 p1
0
3
0 0 -1 0
0 2 0 1
0 5 0 2
0
end_operator
begin_operator
move-disk d1 d2 p2
0
3
0 0 -1 0
0 3 0 1
0 5 0 3
0
end_operator
begin_operator
move-disk d1 d2 p3
0
3
0 0 -1 0
0 4 0 1
0 5 0 4
0
end_operator
begin_operator
move-disk d1 d3 d2
0
3
0 0 0 1
0 1 -1 0
0 5 1 0
0
end_operator
begin_operator
move-disk d1 d3 p1
0
3
0 1 -1 0
0 2 0 1
0 5 1 2
0
end_operator
begin_operator
move-disk d1 d3 p2
0
3
0 1 -1 0
0 3 0 1
0 5 1 3
0
end_operator
begin_operator
move-disk d1 d3 p3
0
3
0 1 -1 0
0 4 0 1
0 5 1 4
0
end_operator
begin_operator
move-disk d1 p1 d2
0
3
0 0 0 1
0 2 -1 0
0 5 2 0
0
end_operator
begin_operator
move-disk d1 p1 d3
0
3
0 1 0 1
0 2 -1 0
0 5 2 1
0
end_operator
begin_operator
move-disk d1 p1 p2
0
3
0 2 -1 0
0 3 0 1
0 5 2 3
0
end_operator
begin_operator
move-disk d1 p1 p3
0
3
0 2 -1 0
0 4 0 1
0 5 2 4
0
end_operator
begin_operator
move-disk d1 p2 d2
0
3
0 0 0 1
0 3 -1 0
0 5 3 0
0
end_operator
begin_operator
move-disk d1 p2 d3
0
3
0 1 0 1
0 3 -1 0
0 5 3 1
0
end_operator
begin_operator
move-disk d1 p2 p1
0
3
0 2 0 1
0 3 -1 0
0 5 3 2
0
end_operator
begin_operator
move-disk d1 p2 p3
0
3
0 3 -1 0
0 4 0 1
0 5 3 4
0
end_operator
begin_operator
move-disk d1 p3 d2
0
3
0 0 0 1
0 4 -1 0
0 5 4 0
0
end_operator
begin_operator
move-disk d1 p3 d3
0
3
0 1 0 1
0 4 -1 0
0 5 4 1
0
end_operator
begin_operator
move-disk d1 p3 p1
0
3
0 2 0 1
0 4 -1 0
0 5 4 2
0
end_operator
begin_operator
move-disk d1 p3 p2
0
3
0 3 0 1
0 4 -1 0
0 5 4 3
0
end_operator
begin_operator
move-disk d2 d3 p1
1
0 0
3
0 1 -1 0
0 2 0 1
0 6 0 1
0
end_operator
begin_operator
move-disk d2 d3 p2
1
0 0
3
0 1 -1 0
0 3 0 1
0 6 0 2
0
end_operator
begin_operator
move-disk d2 d3 p3
1
0 0
3
0 1 -1 0
0 4 0 1
0 6 0 3
0
end_operator
begin_operator
move-disk d2 p1 d3
1
0 0
3
0 1 0 1
0 2 -1 0
0 6 1 0
0
end_operator
begin_operator
move-disk d2 p1 p2
1
0 0
3
0 2 -1 0
0 3 0 1
0 6 1 2
0
end_operator
begin_operator
move-disk d2 p1 p3
1
0 0
3
0 2 -1 0
0 4 0 1
0 6 1 3
0
end_operator
begin_operator
move-disk d2 p2 d3
1
0 0
3
0 1 0 1
0 3 -1 0
0 6 2 0
0
end_operator
begin_operator
move-disk d2 p2 p1
1
0 0
3
0 2 0 1
0 3 -1 0
0 6 2 1
0
end_operator
begin_operator
move-disk d2 p2 p3
1
0 0
3
0 3 -1 0
0 4 0 1
0 6 2 3
0
end_operator
begin_operator
move-disk d2 p3 d3
1
0 0
3
0 1 0 1
0 4 -1 0
0 6 3 0
0
end_operator
begin_operator
move-disk d2 p3 p1
1
0 0
3
0 2 0 1
0 4 -1 0
0 6 3 1
0
end_operator
begin_operator
move-disk d2 p3 p2
1
0 0
3
0 3 0 1
0 4 -1 0
0 6 3 2
0
end_operator
begin_operator
move-disk d3 p1 p2
1
1 0
3
0 2 -1 0
0 3 0 1
0 7 0 1
0
end_operator
begin_operator
move-disk d3 p1 p3
1
1 0
3
0 2 -1 0
0 4 0 1
0 7 0 2
0
end_operator
begin_operator
move-disk d3 p2 p1
1
1 0
3
0 2 0 1
0 3 -1 0
0 7 1 0
0
end_operator
begin_operator
move-disk d3 p2 p3
1
1 0
3
0 3 -1 0
0 4 0 1
0 7 1 2
0
end_operator
begin_operator
move-disk d3 p3 p1
1
1 0
3
0 2 0 1
0 4 -1 0
0 7 2 0
0
end_operator
begin_operator
move-disk d3 p3 p2
1
1 0
3
0 3 0 1
0 4 -1 0
0 7 2 1
0
end_operator
0
