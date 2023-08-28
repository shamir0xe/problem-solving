import random


def test_generator(cnt: int):
    cnt = 5
    print(2 ** ((cnt**2 - cnt) // 2))
    for mask in range(2 ** ((cnt**2 - cnt) // 2)):
        board = [["0" for _ in range(cnt)] for _ in range(cnt)]
        bit = 0
        for i in range(cnt):
            for j in range(cnt):
                if i <= j:
                    continue
                if (mask >> bit) & 1 == 1:
                    board[i][j] = board[j][i] = "1"
                bit += 1
        print(cnt)
        for i in range(cnt):
            print("".join(board[i]))


def assert_output():
    def assertq():
        print(f"test #{test_case}")
        print(f"{n} - {numbers}")
        exit(0)
    test_case = 0
    while True:
        try:
            n = int(input())
        except BaseException:
            break
        test_case += 1
        if n == 0:
            continue
        numbers = list(map(int, input().split()))
        if n != len(numbers):
            assertq()
        if max(numbers) > 5:
            assertq()
        if min(numbers) < 1:
            assertq()
            
    print(f"total test_cases = {test_case}")
    print("done")

def large_test_generator(n : int):
    board = [["0"] * n for _ in range(n)]
    print(1)
    bit = 0
    # mask = random.randint(1 << (n ** 2 // 2), 1 << (n ** 2 - n))
    for i in range(n):
        for j in range(n):
            if i <= j:
                continue
            if random.random() < 0.000001:
                board[i][j] = board[j][i] = "1"
            bit += 1
    print(n)
    for i in range(n):
        print("".join(board[i])) 

def main():
    # assert_output()
    # test_generator(cnt = 5)
    large_test_generator(n = 4000)


if __name__ == "__main__":
    main()
