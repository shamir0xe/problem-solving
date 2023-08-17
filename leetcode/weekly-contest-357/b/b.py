from __future__ import annotations


class Mediator:
    def read_input(self) -> Mediator:
        self.m = int(input())
        self.nums = list(map(int, input().split()))
        self.inputs = [self.nums, self.m]
        return self

    def solve(self, *args):
        nums, m = args
        n = len(nums)
        def get_sum(i, j):
            if i == 0:
                return sums[j]
            return sums[j] - sums[i - 1]
        sums = [0 for _ in range(n)]
        for i in range(n):
            sums[i] += nums[i] + (sums[i - 1] if i - 1 >= 0 else 0)
        dp = [[False for _ in range(n)] for _ in range(n)]
        for i in range(n):
            dp[i][i] = True
        for length in range(2, n + 1):
            for i in range(n):
                j = i + length - 1
                if j >= n:
                    break
                for k in range(i, j):
                    # print(f'({i}, {j}, {k})')
                    flag = True
                    if i != k:
                        flag &= get_sum(i, k) >= m
                    if k + 1 != j:
                        flag &= get_sum(k + 1, j) >= m
                    flag &= dp[i][k]
                    flag &= dp[k + 1][j]
                    dp[i][j] |= flag
        return dp[0][n - 1]

    def print_output(self) -> None:
        print(self.ans)


def main():
    mediator = Mediator().read_input()
    ans = mediator.solve(*mediator.inputs)
    print(ans)


if __name__ == "__main__":
    main()
