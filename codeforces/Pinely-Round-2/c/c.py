from __future__ import annotations
# import sys
import os
import io

# sys.setrecursionlimit(2 * 10**5)
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem C (3/9)
## codeforces, Pinely-Round-2
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


# define variables
n: int = 0
k: int
arr: list[int]


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def __init__(self) -> None:
        self.outputs = []

    def read_input(self) -> Mediator:
        global n, k, arr

        n, k = tuple(map(int, input().split()))
        arr = list(map(int, input().split()))
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global n, k, arr
        k = k % (n + 1)
        ans = []
        add_one = set([i for i in range(n + 1)])
        for i in range(n):
            if arr[i] in add_one:
                add_one.remove(arr[i])
        add_one = add_one.pop()
        # print(f"add{add_one}")
        arr += [add_one]
        for i in range(n):
            ans += [arr[(n + 1 + i - k) % (n + 1)]]

        self.ans = ans
        return self

    def print_output(self) -> Mediator:
        self.outputs += [" ".join(list(map(str, self.ans)))]
        return self


def main(test_case: bool = False):
    med = Mediator()
    def main_part():
        med.read_input().solve().print_output()

    if test_case:
        t = int(input())
        for _ in range(t):
            main_part()
        print("\n".join(med.outputs))
    else:
        main_part()


if __name__ == "__main__":
    main(True)
