from __future__ import annotations
import sys

sys.setrecursionlimit(2 * 10**5)

## problem {} ({}/{})
## {}, {}
## author: @shamir0xe
## generated by contest-builder
## https://github.com/shamir0xe/contest-builder


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

    def solve(self):
        """
        main logic comes here
        """
        global n, some_list

        return (fn(),)


def main():
    mediator = Mediator().read_input()
    ans = mediator.solve()
    print(" ".join(list(map(str, (ans,)))))


if __name__ == "__main__":
    main()
