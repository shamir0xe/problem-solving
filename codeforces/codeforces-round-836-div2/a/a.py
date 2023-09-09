from __future__ import annotations
import sys

sys.setrecursionlimit(2 * 10**5)
# input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem A (1/6)
## codeforces, 836-div2
## author: @shamir0xe
## verdict: [AC]


# define variables
n: int = 0
some_list: list[int]
string: str


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global string
        readline = sys.stdin.readline
        string = readline().rstrip()
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global string
        self.ans = ("".join([string, string[::-1]]),)
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
