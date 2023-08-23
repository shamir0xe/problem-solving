from __future__ import annotations
import os
import io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


class Mediator:
    def read_input(self) -> Mediator:
        n = int(input())
        arr = list(map(int, input().split()))
        self.inputs = (n, arr)
        return self

    def next(self, arr: list, idx: int) -> int:
        return arr[(idx + 1) % len(arr)]

    def before(self, arr, idx):
        return arr[(idx - 1 + len(arr)) % len(arr)]

    def finding_goods(self, arr: list) -> tuple:
        for i in range(len(arr)):
            if self.next(arr, i) != self.before(arr, i):
                return [*arr[:i], *arr[i + 1 :]], 1
        return arr, 0

    def check_alone(self, arr, n):
        bits = [0 for _ in range(n)]
        for number in arr:
            bits[number - 1] += 1
        for cnt in bits:
            if cnt == 1:
                return True
        return False
    
    def relax(self, arr) -> tuple:
        for i in range(len(arr)):
            if self.next(arr, i) == arr[i]:
                return [*arr[:i], *arr[i + 1:]], True
        return arr, False

    def solve(self, *args) -> Mediator:
        n, arr = args
        ans = 0
        while True:
            # finding alones
            if self.check_alone(arr, n):
                ans += len(arr)
                break
            # finding good ones
            arr, cnt = self.finding_goods(arr)
            ans += cnt
            if cnt > 0:
                continue
            # random deletion
            arr = arr[1:]
            ans += 1
            # relaxing
            do = True
            while do:
                arr, do = self.relax(arr)
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
    main(True)
