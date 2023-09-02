from __future__ import annotations
import sys

sys.setrecursionlimit(2 * 10**5)
# input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem A (1/9)
## codeforces, Pinely-Round-2
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


# define variables
n: int = 0
a: int
q: int
operations: str


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global n, a, q, operations
        readline = sys.stdin.readline

        n, a, q = tuple(map(int, readline().rstrip().split()))
        operations = readline()
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global n, a, q, operations
        bl = False
        bl |= a >= n
        flag = operations.count("+") + a >= n
        for char in operations:
            a += 1 if char == "+" else -1
            bl |= a >= n
        if bl & flag:
            self.ans = "YES"
        elif bl | flag:
            self.ans = "MAYBE"
        else:
            self.ans = "NO"

        return self

    def print_output(self) -> None:
        print(" ".join(list(map(str, (self.ans,)))))


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
