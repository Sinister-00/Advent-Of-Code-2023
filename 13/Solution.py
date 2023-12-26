# /// This is giving WA for some reason :(
# // will debug later
# // You can use python code for the meantime in the same folder
# // run it with
# // python3 13.py input.txt
# /// Thanks!


import sys
from pathlib import Path


def find(pttr, tol=0):
    for i in range(1, len(pttr)):
        if tol == sum(
            c != d
            for a, b in zip(pttr[i - 1 :: -1], pttr[i:])
            for c, d in zip(a, b)
        ):
            return i
    return False


def solve(k, t=0):
    return sum((100 * find(p, t)) or find(list(zip(*p)), t) for p in k)


if __name__ == "__main__":
    k = list(map(str.split, Path(sys.argv[1]).read_text().split("\n\n")))
    print("Part 1:", solve(k))
    print("Part 2:", solve(k, 1))