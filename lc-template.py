from __future__ import annotations


class Mediator:
    def read_input(self) -> Mediator:
        self.inputs = [self.a, self.b]
        return self

    def solve(self, *args):
        return self.ans

def main():
    mediator = Mediator().read_input()
    ans = mediator.solve(*mediator.inputs)
    print(ans)


if __name__ == "__main__":
    main()
