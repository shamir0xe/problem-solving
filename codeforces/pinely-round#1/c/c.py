from __future__ import annotations
from collections.abc import Iterable
from typing import List
import os
import io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


class Pair(Iterable):
    def __init__(self, *args) -> None:
        self.pair: tuple = (*args,)

    def __le__(self, other: Pair):
        x, y = self.pair, other.pair

        return x[0] > y[0] if x[0] != y[0] else x[1] < y[1]

    def __iter__(self):
        return self.pair.__iter__()


class Mediator:
    def read_input(self) -> Mediator:
        n = int(input())
        board: List[List[bool]] = []
        for _ in range(n):
            line = str(input().split())[3:-2]
            board.append(list(map(lambda char: char == "1", line)))
        self.inputs = (n, board)
        return self

    def solve(self, *args) -> Mediator:
        n, board = args
        inverse = [[False for _ in range(n)] for _ in range(n)]
        for u in range(n):
            for v in range(n):
                if board[u][v]:
                    inverse[v][u] = True
        # finding sources
        sources = set([i for i in range(n)])
        for i in range(n):
            for j in range(n):
                if board[j][i]:
                    sources.remove(i)
                    break
        # create the list of sets for each index
        sets_list: list[set[int]] = [set() for _ in range(n)]
        pq: set[Pair] = set()
        # assign indices for each source
        counter = 0
        for node in sources:
            sets_list[node].add(counter)
            counter += 1
            # push them into pq
            pq.add(Pair(1, node))
        seen = [False for _ in range(n)]
        while True:
            try:
                size, node = pq.pop()
            except Exception:
                break
            if seen[node]:
                continue
            seen[node] = True
            for u in range(n):
                if inverse[node][u] and sets_list[u] == sets_list[node]:
                    sets_list[node].add(counter)
                    counter += 1
                    size += 1
                    break
            # add each set to the children and update list of sets
            for i in range(n):
                if board[node][i]:
                    # union the sets
                    sets_list[i] |= sets_list[node]
                    pq.add(Pair(len(sets_list[i]), i))
        self.ans = sets_list
        return self

    def print_output(self) -> None:
        sets_list = self.ans
        for i in range(len(sets_list)):
            print(len(sets_list[i]), end="")
            for node in sets_list[i]:
                print(f" {node + 1}", end="")
            print()


def main(test_case: bool = False):
    def main_part():
        mediator = Mediator().read_input()
        mediator.solve(*mediator.inputs).print_output()

    if test_case:
        t = int(input())
        for _ in range(t):
            main_part()
    else:
        main_part()


if __name__ == "__main__":
    main(True)
