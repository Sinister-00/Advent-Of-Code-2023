import sys
from collections import defaultdict, deque
from contextlib import suppress
from math import prod
from pathlib import Path


def parse(lines):
    res = {}
    for line in lines:
        k, d = line.split(" -> ")
        d = d.split(", ")
        match k[0]:
            case "%":
                res[k[1:]] = [0, d]
            case "&":
                res[k[1:]] = [defaultdict(int), d]
            case "b":
                res[k] = (d,)
    for k in res:
        d = res[k][-1]
        for d in d:
            with suppress(TypeError, KeyError):
                res[d][0][k] = 0
    return res


def solve(res, button_presses, tt=None):
    low, high = 0, 0
    for i in range(1, button_presses + 1):
        pulses = deque(["broadcaster"])
        while pulses and (cursor := pulses.popleft()) and (k := res[cursor]):
            match k:
                case (int(), list()):  # %
                    signal = k[0]
                case (dict(), list()):  # &
                    signal = [1, 0][all(k[0].values())]
                case (list(),):  
                    signal = 0
            for destination in k[-1]:
                high += signal
                low += not signal
                try:
                    res[destination][0][cursor] = signal
                    pulses.append(destination)
                except TypeError:
                    if not signal:
                        res[destination][0] = [1, 0][res[destination][0]]
                        pulses.append(destination)
                except KeyError:
                    ...  
            with suppress(TypeError, KeyError):
                if not tt[cursor] and signal:
                    tt[cursor] = i
    return (button_presses + low) * high


def partOne():
    res = parse(Path(sys.argv[1]).read_text().splitlines())
    return solve(res, 1000)


def partTwo():
    res = parse(Path(sys.argv[1]).read_text().splitlines())
    ff = next(filter(lambda n: "rx" in res[n][-1], res))
    tt = list(filter(lambda n: ff in res[n][-1], res))
    tt = {t: 0 for t in tt}
    solve(res, 10000, tt)
    return prod(tt.values())


if __name__ == "__main__":
    print("Part 1:", partOne())
    print("Part 2:", partTwo())