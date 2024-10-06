from __future__ import annotations
import sys

# sys.setrecursionlimit(2 * 10**5)
# input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## problem a-bit-of-a-construction (1/1)
## codeforces, problemset
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

        # n = int(readline().rstrip())
        some_list = list(map(int, readline().split()))
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global some_list
        n, k = some_list
        # print(f"{n}, {k}")
        k_prim = 0
        last = 0
        for i in range(32):
            if k >= (1 << i):
                # print(f"1 << {i}")
                k_prim += 1 << i
                last = 1 << i
        k_prim -= last
        if n == 1:
            self.ans = [k]
        else:
            self.ans = [k_prim, k - k_prim]
            for i in range(n - 2):
                self.ans += [0]
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
