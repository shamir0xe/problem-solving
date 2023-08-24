from __future__ import annotations
import os
import io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


mod = 10**9 + 7


def add(a: int, b: int) -> int:
    return (a + b) % mod


def mul(a: int, b: int, c: int = 1):
    return (a * b * c) % mod


def pow(a: int, b: int) -> int:
    if b < 0:
        return 0
    cur = a
    ans = 1
    while b > 0:
        if b & 1 == 1:
            ans = mul(ans, cur)
        cur = mul(cur, cur)
        b >>= 1
    return ans


class Mediator:
    def read_input(self) -> Mediator:
        self.inputs = tuple(map(int, input().split()))
        self.fac: list
        self.inverse: list
        return self

    def choose(self, k: int, n: int) -> int:
        if k == 0:
            temp = 1
        elif n == 0:
            temp = 0
        elif k == n:
            temp = 1
        elif k > n:
            temp = 0
        else:
            temp = mul(self.fac[n], self.inverse[n - k], self.inverse[k])
        return temp

    def solve(self, *args) -> Mediator:
        n, k = args
        self.fac = [1 for _ in range(n + 3)]
        for i in range(2, n + 3):
            self.fac[i] = mul(i, self.fac[i - 1])
        pow3 = [1 for _ in range(n + 1)]
        for i in range(1, n + 1):
            pow3[i] = mul(pow3[i - 1], 3)
        self.inverse = [1 for _ in range(n + 1)]
        self.inverse[n] = pow(self.fac[n], mod - 2)
        for i in range(n - 1, -1, -1):
            self.inverse[i] = mul(self.inverse[i + 1], i + 1)
        ans = 0
        if k == 0:
            ans = pow3[n]
        else:
            for q in range(1, n + 1):
                ans = add(
                    ans,
                    mul(
                        pow3[n - q],
                        self.choose(((q + 1) >> 1) - 1, k - 1),
                        self.choose(q - ((q + 1) >> 1), n - k),
                    ),
                )
        self.ans = ans
        return self

    def print_output(self) -> None:
        print(self.ans)


def main(test_case: bool = False):
    def main_part():
        mediator = Mediator().read_input()
        mediator.solve(*mediator.inputs).print_output()

    if test_case:
        t = int(input())
        for _ in range(t):
            main_part()
    else:
        main_part()


if __name__ == "__main__":
    main(False)
