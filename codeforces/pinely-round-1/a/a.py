from __future__ import annotations
import os
import io
 
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
 
 
class Mediator:
    def read_input(self) -> Mediator:
        self.inputs = tuple(map(int, input().split()))
        return self
 
    def solve(self, *args) -> Mediator:
        n, a, b = args
        p = [0 for _ in range(n)]
        q = p[::]
        cur = 1
        for i in range(a):
            q[i] = p[i] = cur
            cur += 1
        for i in range(b):
            q[n - i - 1] = p[n - i - 1] = cur
            cur += 1
        # in ascending order, fill q
        for i in range(n - a - b):
            q[a + i] = cur
            cur += 1
        for i in range(n - a - b):
            cur -= 1
            p[a + i] = cur
        self.ans = a >= n or q[a] != p[a]
        self.ans &= n - b - 1 < 0 or q[n - b - 1] != p[n - b - 1]
        return self
 
    def print_output(self) -> None:
        print("Yes" if self.ans else "No")
 
 
def main():
    t = int(input())
    for _ in range(t):
        mediator = Mediator().read_input()
        mediator.solve(*mediator.inputs).print_output()
 
 
if __name__ == "__main__":
    main()
