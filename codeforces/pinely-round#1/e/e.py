from __future__ import annotations
import sys

sys.setrecursionlimit(2 * 10**5)

color: list[bool]
adj: list[list[int]]
children: list[list[int]]
n: int
cur_papa: int


def dfs(u: int, size: int, depth: int = 0) -> tuple[bool, int]:
    # global adj, color, cur_papa, components
    color[u] = True
    # print(
    #     f"{u} -- {len(adj[u])} - {depth} != {size}",
    #     file=sys.stderr,
    # )
    if len(adj[u]) - depth != size:
        # find the brother
        return True, children[cur_papa][0]
    for v in adj[u]:
        if not color[v]:
            flag, index = dfs(v, size - 1, depth + 1)
            if flag:
                return True, index
    return False, -1


def set_children(u: int, papa: int):
    # global adj, color, children
    color[u] = True
    children[papa].append(u)
    for v in adj[u]:
        if not color[v]:
            set_children(v, papa)


class Mediator:
    def read_input(self) -> Mediator:
        global n, adj
        self.ans: tuple[int, list[int]]
        readline = sys.stdin.readline
        n = int(readline())
        adj = [[] for _ in range(n)]
        for u in range(n):
            cur_line = readline()
            for v in range(n):
                if cur_line[v] == "1":
                    adj[u].append(v)
        self.inputs = (0,)
        return self

    def solve(self) -> Mediator:
        global color, n, children, cur_papa
        color = [False] * n
        children = [[] * n for _ in range(n)]
        comp_cnt = 0
        min_component = -1
        for u in range(n):
            if not color[u]:
                comp_cnt += 1
                set_children(u, u)
                children[u] = sorted(children[u], key=lambda idx: len(adj[idx]))
                if min_component == -1 or len(children[u]) < len(
                    children[min_component]
                ):
                    min_component = u

        color = [False] * n
        ans = len(children[min_component])
        real_indices: list[int] = children[min_component]
        # print(f"{ans} - {real_indices}")
        # for u in children:
        #     print(f"{u} -> {children[u]}")
        alter_ans_list = []
        for u in range(n):
            if not color[u]:
                alter_ans_list.append(u)
                cur_papa = u
                found, the_brother = dfs(u, len(children[u]) - 1)
                if found:
                    ans = 1
                    real_indices = [the_brother]
                    break
        if comp_cnt == 1:
            self.ans = (0, [])
            return self
        if comp_cnt == 2 or ans < 2:
            self.ans = (ans, real_indices)
        else:
            self.ans = (2, alter_ans_list[:2])
        return self

    def print_output(self) -> None:
        cnt, indices = self.ans
        print(cnt)
        if cnt > 0:
            print(" ".join(list(map(lambda a: str(a + 1), indices))))


def main(test_case: bool = False):
    def main_part():
        Mediator().read_input().solve().print_output()

    if test_case:
        t = int(input())
        for _ in range(t):
            main_part()
    else:
        main_part()


if __name__ == "__main__":
    main(True)
