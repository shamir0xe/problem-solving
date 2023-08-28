from __future__ import annotations
import sys

sys.setrecursionlimit(2 * 10**5)
# input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem B (2/6)
## codeforces, 836-div2
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


# define variables
n: int = 0
some_list: list[int]


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global n, some_list
        readline = sys.stdin.readline

        n = int(readline().rstrip())
        some_list = list(map(int, readline().split()))
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global n, some_list

        self.ans = (fn(),)
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
    main(False)
