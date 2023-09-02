from __future__ import annotations
import sys

# sys.setrecursionlimit(2 * 10**5)
# input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem C (3/6)
## codeforces, Educational-Codeforces-Round-154
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


# define variables
n: int = 0
some_list: list[int]
seq: str


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global seq
        readline = sys.stdin.readline

        seq = readline().rstrip()
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global seq
        a, b = 1, -1
        cur = 0
        ans = True
        for char in seq:
            if char == '+':
                cur += 1
            elif char == '-':
                cur -= 1
                a = min(a, cur)
                a = max(a, 1)
                if b != -1 and cur < b:
                    b = -1
            elif char == '0':
                if a >= cur:
                    ans = False
                    break
                if b == -1 or b > cur:
                    b = cur
            else:
                # char == '1'
                if b != -1 and b <= cur:
                    ans = False
                    break
                a = max(cur, 1)
            # print(char, cur, a, b)

        self.ans = "YES" if ans else "NO", 
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
