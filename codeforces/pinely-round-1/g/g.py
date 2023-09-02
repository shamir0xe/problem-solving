from __future__ import annotations
import os
import io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


class Mediator:
    def read_input(self) -> Mediator:
        self.inputs = tuple(map(int, input().split()))
        return self

    def solve(self, *args) -> Mediator:
        a1, a2, a3 = args
        self.ans = "bla bla"
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
