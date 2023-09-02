from __future__ import annotations
import sys

# sys.setrecursionlimit(10**5)
# input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem A (1/6)
## codeforces, Educational-Codeforces-Round-154
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


# define variables
digits: str

# define other functions here


class Mediator:
    def read_input(self) -> Mediator:
        global digits
        readline = sys.stdin.readline

        digits = readline().rstrip()
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global digits
        i = digits.index('1')
        j = digits.index('3')
        if i < j:
            ans = "13"
        else:
            ans = "31"
            

        self.ans = ans
        return self

    def print_output(self) -> None:
        print("".join(list(map(str, self.ans))))


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
