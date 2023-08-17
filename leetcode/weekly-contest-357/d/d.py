from __future__ import annotations
import heapq


class Mediator:
    def read_input(self) -> Mediator:
        n = int(input())
        k = int(input())
        items = []
        for _ in range(n):
            items.append(list(map(int, input().split())))
        self.inputs = [items, k]
        return self

    def solve(self, *args):
        items, k = args
        n = len(items)
        items = sorted(items, key=lambda x: -x[0])
        items = list(map(lambda x: (x[0], x[1] - 1), items))
        distincts = []
        reserved = []
        seen = [False for _ in range(n)]
        for value, cat in items:
            if seen[cat]:
                reserved.append((-value, cat))
                continue
            seen[cat] = True
            distincts.append((value, cat))
        distincts = distincts[:k]
        distincts = distincts[::-1]
        t = len(distincts)
        heapq.heapify(reserved)
        while len(distincts) < k:
            value, cat = heapq.heappop(reserved)
            value = -value
            distincts.append((value, cat))
        ans = sum([x[0] for x in distincts]) + t**2
        cur = ans
        for i in range(t):
            try:
                value, cat = heapq.heappop(reserved)
            except:
                break
            value = -value
            cur = cur - t**2 + (t - 1) ** 2 + value - distincts[i][0]
            t -= 1
            ans = max(ans, cur)
        return ans

    def print_output(self) -> None:
        pass


def main():
    mediator = Mediator().read_input()
    ans = mediator.solve(*mediator.inputs)
    print(ans)
    mediator.print_output()


if __name__ == "__main__":
    main()
