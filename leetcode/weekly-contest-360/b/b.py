from __future__ import annotations
import sys

sys.setrecursionlimit(2 * 10**5)

## generated template for competetive programming
## problem B (2/4)
## leetcode, weekly-contest-360
## author: @shamir0xe
## verdict: [AC]


# define variables
n: int = 0
target: int = 0


# define other functions here
def range_sum(a, b):
    return (a + b) * (b - a + 1) // 2


class Mediator:
    def read_input(self) -> Mediator:
        global n, target
        readline = sys.stdin.readline

        n = int(readline().rstrip())
        target = int(readline().rstrip())
        return self

    def solve(self):
        """
        main logic comes here
        """
        global n, target
        # print(range_sum(1, target // 2))
        # print(range_sum(target, n + target // 2 - 1))
        if n >= target // 2 + 1:
            return range_sum(1, target // 2) + range_sum(target, n + (target - 1) // 2)
        else:
            return range_sum(1, n)



def main():
    mediator = Mediator().read_input()
    ans = mediator.solve()
    print(" ".join(list(map(str, (ans,)))))


if __name__ == "__main__":
    main()

