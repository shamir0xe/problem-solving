from __future__ import annotations
import math
import sys

sys.setrecursionlimit(2 * 10**5)

## generated template for competetive programming
## problem D (4/4)
## leetcode, weekly-contest-360
## author: @shamir0xe
## verdict: [AC]


# define variables
k: int = 0
receiver: list[int]
dp: list[list[int]]
nexts: list[list[int]]


class Mediator:
    def read_input(self) -> Mediator:
        global receiver, k
        readline = sys.stdin.readline

        k = int(readline().rstrip())
        receiver = list(map(int, readline().split()))
        return self

    def solve(self):
        """
        main logic comes here
        """
        global k, receiver, dp, nexts
        n = len(receiver)
        maxi = n + n * k
        max_bits = int(math.log(maxi) / math.log(2)) + 1
        dp = [[0] * max_bits for _ in range(n)]
        nexts = [[0] * max_bits for _ in range(n)]
        for i in range(n):
            dp[i][0] = i
            nexts[i][0] = receiver[i]
        for bit in range(1, max_bits):
            for i in range(n):
                dp[i][bit] = dp[i][bit - 1] + dp[nexts[i][bit - 1]][bit - 1]
                nexts[i][bit] = nexts[nexts[i][bit - 1]][bit - 1]
        k += 1
        ans = 0
        for i in range(n):
            cur = 0
            pos = i
            for bit in range(max_bits):
                if (k >> bit) & 1 == 1:
                    cur += dp[pos][bit]
                    pos = nexts[pos][bit]
            ans = max(ans, cur)
        return ans 


def main():
    mediator = Mediator().read_input()
    ans = mediator.solve()
    print(" ".join(list(map(str, (ans,)))))


if __name__ == "__main__":
    main()

