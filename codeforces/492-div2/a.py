import os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


class Mediator:
    def read_input(self):
        self.n = int(input())
        return self

    def solve(self):
        num = 0
        arr = [100, 20, 10, 5, 1]
        for denominator in arr:
            num += int(self.n / denominator)
            self.n = int(self.n % denominator)
        self.out = num
        return self

    def output(self):
        print(self.out)
        return self


def main():
    Mediator().read_input().solve().output()


if __name__ == "__main__":
    main()
