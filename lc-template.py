from __future__ import annotations


class Mediator:
    def read_input(self) -> Mediator:
        self.inputs = (input(), input())
        return self

    def solve(self, *args):
        in1, in2 = args
        ans = "ok"
        return ans


def main():
    mediator = Mediator().read_input()
    ans = mediator.solve(*mediator.inputs)
    print(ans)


if __name__ == "__main__":
    main()
