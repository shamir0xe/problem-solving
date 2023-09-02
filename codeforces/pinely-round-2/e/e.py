from __future__ import annotations
from collections import Counter
from types import GeneratorType
# import sys
import os
import io
# from typing import Generic, TypeVar

# sys.setrecursionlimit(10**5)
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem E (5/9)
## codeforces, Pinely-Round-2
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


# define variables
n: int = 0
m: int
k: int
hs: list[int]
adj: list[list[int]]
rev: list[list[int]]
edges: list[tuple[int, int]]
color: list[bool]
value: list[int]
rights: list[int]
fvalue: list[int]


# define other functions here
@bootstrap
def dfs(u: int):
    color[u] = True
    # print(f"from {u + 1}")
    for v in adj[u]:
        # print(f"{u + 1}->{v + 1}")
        if not color[v]:
            yield dfs(v)
        temp = 0
        if hs[v] > hs[u]:
            temp = 1
        value[u] = max(value[u], value[v] + temp)
    # print(f"value[{u + 1}] = {value[u]}")
    yield


def get_max(u) -> int:
    color[u] = True
    ans = value[u] * k + hs[u]
    for v in [*adj[u], *rev[u]]:
        if not color[v]:
            ans = max(get_max(v), ans)
    return ans


@bootstrap
def farthest_delayed(u: int):
    if color[u]:
        yield fvalue[u]
    color[u] = True
    cur_v = (value[u] + 1) * k + hs[u]
    # print(f"{u + 1}, cur_days: {value[u]} cur_v: {cur_v}")
    ans = cur_v
    for v in rev[u]:
        child_v = value[v] * k + hs[v]
        if cur_v > child_v:
            yield farthest_delayed(v)
            ans = max(ans, fvalue[v])
    fvalue[u] = ans
    yield


class Mediator:
    def __init__(self) -> None:
        self.outputs: list[str] = []

    def read_input(self) -> Mediator:
        global n, m, k, hs, edges

        n, m, k = tuple(map(int, input().rstrip().split()))
        hs = list(map(int, input().rstrip().split()))
        edges = []
        for _ in range(m):
            u, v = tuple(map(int, input().rstrip().split()))
            u, v = u - 1, v - 1
            edges += [(u, v)]
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global n, m, k, hs, edges, color, adj, value, rev, fvalue
        adj = [[] for _ in range(n)]
        rev = [[] for _ in range(n)]
        for u, v in edges:
            adj[v] += [u]
            rev[u] += [v]
        value = [0] * n
        color = [False] * n
        total: list[tuple[int, int, int]] = []
        for u in range(n):
            if not color[u]:
                dfs(u)
        color = [False] * n
        fvalue = [0] * n
        # for u in range(n):
        #     print(f"{u + 1} farthest_delayed: {farthest_delayed(u)}")
        right = -1

        for u in range(n):
            # print("~", u + 1, value[u], hs[u])
            # right = max(right, value[u] * k + hs[u])
            if value[u] == 0:
                farthest_delayed(u)
                total += [(hs[u], fvalue[u], u)]
            right = max(right, value[u] * k + hs[u])
        total = sorted(total)
        ans = int(1e19)
        for le, shifted, u in total:
            # print(f"[{u + 1}] {le}, {shifted} -- {right}")
            ans = min(ans, right - le)
            right = max(right, shifted)

        self.ans = ans
        return self

    def print_output(self) -> None:
        print(self.ans)
        # self.outputs += [str(self.ans)]


def main(test_case: bool = False):
    med = Mediator()

    def main_part():
        med.read_input().solve().print_output()

    if test_case:
        t = int(input())
        for _ in range(t):
            main_part()
        # print("\n".join(med.outputs))
    else:
        main_part()


if __name__ == "__main__":
    main(True)
