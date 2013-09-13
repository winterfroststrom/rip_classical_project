#! /usr/bin/env python

import os.path

def summarize_log(text):
    blocks = text.split("\n\n")
    for block in blocks:
        if block.strip():
            report_info(block.splitlines())

def summarize_log(filename):
    block = list(open(filename))
    problem_file = os.path.basename(filename)
    problem_file = os.path.splitext(problem_file)[0]
    search_time = None
    for line in block:
        if line.startswith("Abstraction size limit:"):
            abstraction_size = int(line.split()[3])
        elif line.startswith("Done initializing Finkbeiner/Draeger heuristic"):
            h_time = float(line.split("[")[1].split("s")[0])
        elif line.startswith("initial h value:"):
            init_h = int(line.split()[3])
        elif line.startswith("Actual search time:"):
            search_time = float(line.split()[3][:-1])
            total_time = h_time+search_time
        elif line.startswith("Plan length:"):
            plan_length = int(line.split()[2])
        elif line.startswith("Expanded") and len(line.split()) == 3:
            expanded = int(line.split()[1])
        elif line.startswith("Expanded until last jump:"):
            expanded_before_last = int(line.split()[4])
        elif line.startswith("Search time:") and search_time is None:
            search_time = float(line.split()[2][:-1]) - h_time
            total_time = h_time+search_time
    try:
        print "%-20s %8d %3d %3d %7.2f %8d %8d %7.2f %7.2f" % (
            problem_file, abstraction_size, plan_length, init_h, h_time,
            expanded_before_last, expanded, search_time, total_time)
    except:
        try:
            print "%-20s %8d %3d %7.2f failed in search" % (
                problem_file, abstraction_size, init_h, h_time)
        except NameError:
            try:
                print "%-20s %8d failed in h fn construction" % (problem_file, abstraction_size)
            except NameError:
                # This probably means that the abstraction_size is not yet
                # included in the log file.
                pass
            
if __name__ == "__main__":
    import sys
    args = sys.argv[1:]
    if args:
        for filename in args:
            summarize_log(filename)
    else:
        summarize_log(sys.stdin.read())
