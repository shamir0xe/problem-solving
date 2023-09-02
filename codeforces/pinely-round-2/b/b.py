from __future__ import annotations
import sys
import io
import os

sys.setrecursionlimit(10**5)
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem B (2/9)
## codeforces, Pinely-Round-2
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


# define variables
n: int = 0
perm: list[int]


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global n, perm

        n = int(input().rstrip())
        perm = list(map(int, input().rstrip().split()))
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global n, perm
        where = [0] * n
        for i in range(n):
            where[perm[i] - 1] = i
        ans = 0
        for i in range(n - 1):
            if where[i] > where[i + 1]:
                ans += 1
        self.ans = ans,
        return self

    def print_output(self) -> None:
        print(" ".join(list(map(str, self.ans))))


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
