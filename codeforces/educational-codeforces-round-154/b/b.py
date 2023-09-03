from __future__ import annotations
import sys

# sys.setrecursionlimit(10**5)
# input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem B (2/6)
## codeforces, Educational-Codeforces-Round-154
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


# define variables
n: int = 0
some_list: list[int]
a1: str
a2: str


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global a1, a2
        readline = sys.stdin.readline

        a1 = readline().rstrip()
        a2 = readline().rstrip()
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global a1, a2
        n = len(a1)
        ans = False
        for i in range(n - 1):
            ans |= (
                a1[i] == "0" and a2[i] == "0" and a1[i + 1] == "1" and a2[i + 1] == "1"
            )
        self.ans = "YES" if ans else "NO"
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
