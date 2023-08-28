from __future__ import annotations
import sys

sys.setrecursionlimit(2 * 10**5)

## generated template for competetive programming
## problem C (3/4)
## leetcode, weekly-contest-360
## author: @shamir0xe
## verdict: [AC]


# define variables
n: int = 0
target: int
nums: list[int]


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global nums, target
        readline = sys.stdin.readline

        target = int(readline().rstrip())
        nums = list(map(int, readline().split()))
        return self

    def solve(self):
        """
        main logic comes here
        """
        global nums, target
        nums = sorted(nums)
        sums = 0
        i, j = 0, 0
        ans = 0
        while (1 << i) <= target:
            if (target >> i) & 1 == 1:
                while j < len(nums) and (1 << i) > nums[j]:
                    sums += nums[j]
                    j += 1
                if sums >= (1 << i):
                    sums -= (1 << i)
                    i += 1
                    continue
                else:
                    if j >= len(nums):
                        ans = -1
                        break
                    while nums[j] > (1 << i):
                        nums = [*nums[:j], *[nums[j] >> 1, nums[j] >> 1], *nums[j + 1:]]
                        ans += 1
                    j += 1
            i += 1
        return ans 


def main():
    mediator = Mediator().read_input()
    ans = mediator.solve()
    print(" ".join(list(map(str, (ans,)))))


if __name__ == "__main__":
    main()

