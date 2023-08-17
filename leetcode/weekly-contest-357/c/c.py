from __future__ import annotations
from collections import deque


class Mediator:
    def read_input(self) -> Mediator:
        self.n = int(input())
        self.grid = []
        for _ in range(self.n):
            self.grid.append(list(map(int, input().split())))
        self.inputs = [self.grid]
        return self

    def solve(self, *args):
        grid = args[0]
        n = len(grid)
        dist = [[-1 for _ in range(n)] for _ in range(n)]
        directions = [(-1, 0), (0, -1), (+1, 0), (0, +1)]

        def in_range(x, y):
            return 0 <= x < n and 0 <= y < n

        def can_go(m: int) -> bool:
            if dist[0][0] < m:
                return False
            bbfs = deque()
            check = [[0 for _ in range(n)] for _ in range(n)]
            bbfs.append((0, 0))
            check[0][0] = 1
            while True:
                try:
                    x, y = bbfs.popleft()
                except:
                    break
                for delta_x, delta_y in directions:
                    xx, yy = x + delta_x, y + delta_y
                    if (
                        in_range(xx, yy)
                        and check[xx][yy] == 0
                        and dist[xx][yy] >= m
                    ):
                        check[xx][yy] = 1
                        bbfs.append((xx, yy))
            return check[n - 1][n - 1]

        bfs = deque()
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    bfs.append((i, j))
                    dist[i][j] = 0
        while True:
            try:
                x, y = bfs.popleft()
            except:
                break
            for delta_x, delta_y in directions:
                xx, yy = x + delta_x, y + delta_y
                if in_range(xx, yy) and dist[xx][yy] == -1:
                    dist[xx][yy] = dist[x][y] + 1
                    bfs.append((xx, yy))
        s, e = 0, n
        while e - s > 1:
            m = (e + s) >> 1
            if can_go(m):
                s = m
            else:
                e = m
        return s

    def print_output(self) -> None:
        print()


def main():
    mediator = Mediator().read_input()
    ans = mediator.solve(*mediator.inputs)
    print(ans)
    mediator.print_output()


if __name__ == "__main__":
    main()
