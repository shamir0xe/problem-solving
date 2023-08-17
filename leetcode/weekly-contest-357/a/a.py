from __future__ import annotations


class Mediator:
    def read_input(self) -> Mediator:
        self.s = input()
        self.inputs = [self.s]
        return self

    def solve(self, *args):
        s = args[0]
        self.ans = ''
        for char in s:
            if char == 'i':
                self.ans = self.ans[::-1]
            else:
                self.ans += char
        return self.ans

    def print_output(self) -> None:
        print(self.ans)


def main():
    mediator = Mediator().read_input()
    mediator.solve(*mediator.inputs)
    mediator.print_output()


if __name__ == "__main__":
    main()
