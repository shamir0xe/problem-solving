from __future__ import annotations
import sys

sys.setrecursionlimit(2 * 10**5)

## generated template for competetive programming
## problem A (1/4)
## leetcode, weekly-contest-360
## author: @shamir0xe
## verdict: [AC]


# define variables
n: int = 0
some_list: list[int]
moves: str


# define other functions here
def fn():
    return (n**2,)


class Mediator:
    def read_input(self) -> Mediator:
        global moves
        readline = sys.stdin.readline

        moves = readline().rstrip()
        return self

    def solve(self):
        """
        main logic comes here
        """
        global moves
        cnt = 0
        ans = 0
        direction = -1
        for char in moves:
            if char == 'L':
                direction = -1
            elif char == 'R':
                direction = +1
            else:
                direction = -1
            cnt += direction
        ans = max(ans, abs(cnt))
        cnt = 0
        direction = +1
        for char in moves:
           if char == 'L':
                direction = -1
           elif char == 'R':
               direction = +1
           else:
               direction = +1
           cnt += direction
        ans = max(ans, abs(cnt))
        return ans 


def main():
    mediator = Mediator().read_input()
    ans = mediator.solve()
    print(" ".join(list(map(str, (ans,)))))


if __name__ == "__main__":
    main()

