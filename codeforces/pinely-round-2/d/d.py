from __future__ import annotations

# import sys
import io
import os

# sys.setrecursionlimit(2 * 10**5)
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem D (4/9)
## codeforces, Pinely-Round-2
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


# define variables
n: int = 0
m: int
vers: list
hors: list


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global n, m, vers, hors

        vers, hors = [], []
        n, m = tuple(map(int, input().rstrip().split()))
        for i in range(n):
            line = str(input().rstrip())
            for j, char in enumerate(line[2:-1]):
                if char == "U":
                    vers += [(i, j)]
                if char == "L":
                    hors += [(i, j)]
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global n, m, vers, hors
        vers = sorted(vers)
        hors = sorted(hors, key=lambda a: a[1])
        board = [[0] * m for _ in range(n)]
        color = 1
        for pair in vers:
            i, j = pair
            board[i][j] = color
            board[i + 1][j] = -1 * color
            color *= -1
        color = 1
        for pair in hors:
            i, j = pair
            board[i][j] = color
            board[i][j + 1] = -1 * color
            color *= -1

        flag = True
        for i in range(n):
            cur_sum = 0
            for j in range(m):
                cur_sum += board[i][j]
            flag &= cur_sum == 0
        for j in range(m):
            cur_sum = 0
            for i in range(n):
                cur_sum += board[i][j]
            flag &= cur_sum == 0
        if not flag:
            self.ans = "-1"
        else:
            out = []
            for i in range(n):
                line = "".join(
                    [
                        "W" if board[i][j] == 1 else "B" if board[i][j] == -1 else "."
                        for j in range(m)
                    ]
                )
                out += [line]
            self.ans = "\n".join(out)
        return self

    def print_output(self) -> None:
        print(self.ans)


def main(test_case: bool = False):
    def main_part():
        Mediator().read_input().solve().print_output()

    if test_case:
        t = int(input())
        for _ in range(t):
            main_part()
    else:
        main_part()


if __name__ == "__main__":
    main(True)
