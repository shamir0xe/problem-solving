from __future__ import annotations
import os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


class Mediator:
    def __init__(self) -> None:
        self.ans = 0
        self.sums = [0 for _ in range(3 * 10**5 + 1)]
        self.cnts = [0 for _ in range(3 * 10**5 + 1)]
        self.primes = [[] for _ in range(3 * 10**5 + 1)]

    def read_input(self) -> Mediator:
        self.n = int(input())
        self.arr = list(map(int, input().split()))
        self.arr = sorted(self.arr)
        return self

    def calc(self, idx, value):
        # k -> te'daade avaamele aval nesbat be value
        # sum -> majmoo'e andis haaye avaamele aval nesbat be value
        k, sum = idx, ((idx - 1) * idx) >> 1
        m = len(self.primes[value])
        for mask in range(1, 1 << m):
            cur = 1
            parity = 0
            for i in range(m):
                if ((mask >> i) & 1) == 1:
                    cur *= self.primes[value][i]
                    parity ^= 1
            sum = sum + (-1 if parity == 1 else +1) * self.sums[cur]
            k = k + (-1 if parity == 1 else +1) * self.cnts[cur]

            self.sums[cur] += idx
            self.cnts[cur] += 1
        return k, sum

    def sieve(self) -> Mediator:
        maxi = self.arr[-1] + 1
        flags = [0 for _ in range(maxi)]
        for i in range(2, maxi):
            if flags[i] == 0:
                # here we have a prime number
                flags[i] = 1
                self.primes[i] = [i]
                for j in range(i + i, maxi, i):
                    flags[j] = 2
                    self.primes[j].append(i)
        return self

    def solve(self) -> Mediator:
        self.sieve()
        for i in range(self.n):
            k, sum = self.calc(i, self.arr[i])
            if i == 0:
                continue
            self.ans += k * (i - 1) - sum
        return self

    def print_output(self) -> None:
        print(self.ans)


def main():
    # status: accepted
    Mediator().read_input().solve().print_output()


if __name__ == "__main__":
    main()
