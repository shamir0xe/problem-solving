from __future__ import annotations
import sys

# sys.setrecursionlimit(2 * 10**5)
# input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

## generated template for competetive programming
## problem D (4/6)
## codeforces, Educational-Codeforces-Round-154
## author: @shamir0xe
## verdict: [AC/WA/TLE/MLE]


# define variables
n: int = 0
arr: list[int]


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global n, arr
        readline = sys.stdin.readline

        n = int(readline().rstrip())
        arr = list(map(int, readline().rstrip().split()))
        return self

    def solve(self) -> Mediator:
        """
        main logic comes here
        """
        global n, arr
        a = [0] * n
        b = [0] * n
        # print(arr)
        # print(n)
        for i in range(1, n):
            a[i] = a[i - 1] + (1 if arr[i] <= arr[i - 1] else 0)
            b[i] = b[i - 1] + (1 if arr[i] >= arr[i - 1] else 0)
        
        c = [0] * (n + 1)
        for i in range(n - 2, -1, -1):
            c[i] = c[i + 1] + (1 if arr[i] >= arr[i + 1] else 0)
        
        ans = n
        for i in range(n):
            # print(f"[{i}]: {a[i]} {b[i]} {c[i]}")
            t1 = a[i] + c[i]
            t2 = (b[i] + 1) + c[i + 1]
            # print(f"t1: {t1} t2: {t2}")
            ans = min(ans, min(t1, t2))

        self.ans = (ans,)
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
