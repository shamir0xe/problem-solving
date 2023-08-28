from __future__ import annotations

import sys
import io
import os

sys.setrecursionlimit(10**5)
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem E (5/6)
## codeforces, 836-div2
## author: @shamir0xe
## verdict: [AC]


# define variables
n: int = 0
board: list[list[int]]
m: int
h: int
adj: list[list[tuple[int, int]]]
taken: list[int]
mod: int = 10**9 + 7
outputs: list[int]
values: list[int]
par: list[int]

#
debug: bool = False


def union(u: int, v: int):
    u = find_par(u)
    v = find_par(v)
    if u == v:
        return
    if u > v:
        u, v = v, u
    par[v] = u


def find_par(u: int) -> int:
    if u == par[u]:
        return u
    par[u] = find_par(par[u])
    return par[u]


# define other functions here
def dfs(u: int) -> bool:
    taken[u] = 1
    for v, cost in adj[u]:
        temp = (2 * h - values[u] - cost) % h
        if taken[v] == 0:
            if cost != -1:
                values[v] = temp
            bl = dfs(v)
            if not bl:
                return False
        else:
            if cost != -1 and temp != values[v]:
                return False
    return True


def add_edge(i: int, j: int, cost: int):
    # print(f"adding edge {i + 1} -> {j + 1}, {cost}")
    union(i, j + n)
    adj[i] += [(n + j, cost)]
    adj[n + j] += [(i, cost)]


def mul(a: int, b: int) -> int:
    return (a * b) % mod


class Mediator:
    def __init__(self) -> None:
        self.outputs: list[int] = []

    def read_input(self) -> Mediator:
        global n, m, h, board, debug
        # readline = sys.stdin.readline

        n, m, h = tuple(map(int, input().rstrip().split()))
        board = [[0] * m for _ in range(n)]
        for i in range(n):
            for j, value in enumerate(list(map(int, input().rstrip().split()))):
                board[i][j] = value
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global n, m, h, board, adj, taken, values, par
        adj = [[] for _ in range(n + m)]
        par = [i for i in range(n + m)]
        for i in range(n):
            for j in range(m):
                if board[i][j] >= 0:
                    add_edge(i, j, board[i][j])

        # print('yolo')
        ans = 1
        for i in range(n):
            for j in range(m):
                if board[i][j] < 0:
                    if find_par(i) != find_par(j + n):
                        union(i, j + n)
                        ans = mul(ans, h)

        taken = [0] * (n + m)
        values = [-1] * (n + m)
        for u in range(n + m):
            if taken[u] == 0:
                values[u] = 0
                flag = dfs(u)
                if not flag:
                    ans = 0
                    break
        self.ans = ans
        return self

    def print_output(self) -> None:
        self.outputs += [self.ans]
        # print(self.ans)


def main(test_case: bool = False):
    global debug
    mediator = Mediator()

    def main_part():
        mediator.read_input().solve().print_output()

    if test_case:
        t = int(input().rstrip())
        for test in range(t):
            # if test == 112:
            #     debug = True
            main_part()
        print("\n".join(list(map(str, mediator.outputs))))
    else:
        main_part()


if __name__ == "__main__":
    main(True)
