class AvlTree:
    """
    implementation of the avl-tree
    all of the orders are optimum as hell
    node's value should have been implemented with __lt__ operator
    """

    def __init__(self):
        self.__root = None

    def get_root(self):
        """
        returns the current root of the tree
        """
        return self.__root

    def empty(self):
        return self.__root is None

    def insert(self, value):
        """
        adding a new node with a value equals to {value}
        """
        if self.get_root() is None:
            self.__root = Node(value)
        else:
            if self.find(value) is None:
                self.__root = self.__add(self.__root, Node(value))

    def find(self, objective):
        """
        returns the node with a value equals to {objective}
        """
        return self.__find(objective, self.__root)

    def find_node(self, node):
        """
        check whether the node is exist or not
        """
        # debug_text("finding node with value = {}".format(node.get_value()))
        # debug_text("node = {}".format(node))
        return self.__find(node.get_value(), self.__root, node.get_hash())

    def remove(self, objective):
        """
        removes the node with a value equals to {objective}"""
        node = self.find(objective)
        if node is None:
            return False
        self.__root = self.__remove(objective, self.__root)
        return True

    def remove_node(self, node):
        """
        removes the node with it's actual node
        """
        # debug_text("going to remove the node with {} as value". \
        # format(node.get_value()))
        node = self.find_node(node)
        if node is None:
            return False
        # debug_text("\n\n==>{}".format(node.get_hash()))
        self.__root = self.__remove(node.get_value(), self.__root, node.get_hash())
        return True

    def get_size(self):
        if self.__root is None:
            return 0
        return self.__root.get_size()

    def get_lowest(self):
        """
        returns the node with the lowest value in the tree
        """
        if self.__root is None:
            return None
        node = self.__root
        while node.get_left() is not None:
            node = node.get_left()
        return node

    def get_highest(self):
        """
        returns the node with the highest value in the tree
        """
        if self.__root is None:
            return None
        node = self.__root
        while not node.get_right() is None:
            node = node.get_right()
        return node

    def inorder_list(self, node, res):
        """
        returns the inorder list of the tree as array of string
        """
        if node is None:
            return
        res.append("(")
        self.inorder_list(node.get_left(), res)
        res.append(",")
        if node.get_value():
            res.append(str(node.get_value()))
            # res.append(node.get_hash())
        res.append(",")
        self.inorder_list(node.get_right(), res)
        res.append(")")

    def get_list(self):
        res = []
        self.get_all(self.__root, res)
        return res

    def get_all(self, node, arr: list):
        if node is None:
            return
        self.get_all(node.get_left(), arr)
        if node.get_value():
            arr.append(node.get_value())
        self.get_all(node.get_right(), arr)

    def __remove(self, objective, node, node_hash=None):
        if node is None:
            return None
        if objective < node.get_value():
            left = self.__remove(objective, node.get_left(), node_hash)
            node.set_left(left)
        elif node.get_value() < objective:
            right = self.__remove(objective, node.get_right(), node_hash)
            node.set_right(right)
        else:
            if node_hash is None or node.get_hash() == node_hash:
                right = node.get_right()
                if not right is None:
                    node = self.__rotate_left(node)
                    left = self.__remove(
                        objective, node.get_left(), node.get_left().get_hash()
                    )
                    node.set_left(left)
                else:
                    left = node.get_left()
                    if not left is None:
                        node = self.__rotate_right(node)
                        right = self.__remove(
                            objective, node.get_right(), node.get_right().get_hash()
                        )
                        node.set_right(right)
                    else:
                        del node
                        return None
            else:
                right = self.__remove(objective, node.get_right(), node_hash)
                node.set_right(right)
        res = self.__relax(node)
        res.set_par(None)
        return res

    def __find(self, objective, node, node_hash=None):
        if node is None:
            return None

        c = "=="
        if objective < node.get_value():
            c = "<"
        if node.get_value() < objective:
            c = ">"
        # debug_text("obj{}node - {}/{}".format(c, node.get_hash(), node_hash))
        if objective < node.get_value():
            return self.__find(objective, node.get_left(), node_hash)
        if node.get_value() < objective:
            return self.__find(objective, node.get_right(), node_hash)
        if node_hash is None or node.get_hash() == node_hash:
            # debug_text("c'mon")
            return node
        return self.__find(objective, node.get_right(), node_hash)

    def __add(self, cur, node):
        if node < cur:
            if cur.get_left() is None:
                cur.set_left(node)
                node.set_par(cur)
            else:
                left = self.__add(cur.get_left(), node)
                left.set_par(cur)
                cur.set_left(left)
        else:
            if cur.get_right() is None:
                cur.set_right(node)
                node.set_par(cur)
            else:
                right = self.__add(cur.get_right(), node)
                right.set_par(cur)
                cur.set_right(right)
        return self.__relax(cur)

    def __get_height(self, node):
        if node is None:
            return 0
        return node.get_height()

    def __relax(self, node):
        if node is None:
            return
        node.update()
        balance = node.get_balance()
        if balance > 1:
            left_left = node.get_left().get_left()
            left_right = node.get_left().get_right()
            if self.__get_height(left_left) <= self.__get_height(left_right):
                node.set_left(self.__rotate_left(node.get_left()))
            return self.__rotate_right(node)
        elif balance < -1:
            right_right = node.get_right().get_right()
            right_left = node.get_right().get_left()
            if self.__get_height(right_right) <= self.__get_height(right_left):
                node.set_right(self.__rotate_right(node.get_right()))
            return self.__rotate_left(node)
        return node

    def __rotate_right(self, y):
        x = y.get_left()
        t_2 = x.get_right()
        x.set_right(y)
        y.set_left(t_2)
        y.update()
        x.update()
        x.set_par(None)
        return x

    def __rotate_left(self, x):
        y = x.get_right()
        t_2 = y.get_left()
        y.set_left(x)
        x.set_right(t_2)
        x.update()
        y.update()
        y.set_par(None)
        return y

    def __str__(self):
        res = []
        self.inorder_list(self.__root, res)
        list_string = "".join(res)
        return "list: {}\nbalance: {}, size: {}".format(
            list_string, self.__root.get_balance(), self.__root.get_size()
        )


class Node:
    def __init__(self, objective=None):
        self.__value = objective
        self.__height = 1
        self.__size = 1
        self.__parent = self.__left = self.__right = None
        self.__hash = HashGenerator().generate(5)

    def set_value(self, value):
        self.__value = value

    def set_right(self, node):
        if not node is None:
            node.set_par(self)
        self.__right = node

    def set_left(self, node):
        if not node is None:
            node.set_par(self)
        self.__left = node

    def set_par(self, node):
        self.__parent = node

    def set_hash(self, node_hash):
        self.__hash = node_hash

    def get_balance(self):
        left_height = 0
        if not self.__left is None:
            left_height = self.__left.get_height()
        right_height = 0
        if not self.__right is None:
            right_height = self.__right.get_height()
        return left_height - right_height

    def get_left(self):
        return self.__left

    def get_right(self):
        return self.__right

    def get_value(self):
        return self.__value

    def get_hash(self):
        return self.__hash

    def get_size(self):
        return self.__size

    def __str__(self):
        return "val: [{}], par: [{}], sz: [{}], h: [{}], hash: [{}]".format(
            self.__value, self.__parent, self.__size, self.__height, self.__hash
        )

    def get_height(self):
        if self.__value is None:
            return 0
        return self.__height

    def update_height(self):
        self.__height = 1
        maxi = 0
        if self.__left:
            maxi = max(maxi, self.__left.get_height())
        if self.__right:
            maxi = max(maxi, self.__right.get_height())
        self.__height += maxi

    def update_size(self):
        self.__size = 1
        if self.__left:
            self.__size += self.__left.get_size()
        if self.__right:
            self.__size += self.__right.get_size()

    def update(self):
        self.update_height()
        self.update_size()

    def __eq__(self, other):
        if self.__value == other.get_value():
            return self.__hash == other.get_hash()
        return False

    def __lt__(self, other):
        # if other is None:
        # 	return False
        # if self.__value == other.get_value():
        # 	return False
        # if other.get_value is None:
        # 	return False
        return self.__value < other.get_value()


class HashGenerator:
    mother_string = "abcdefghijklmnopqrstuvwxyz0123456789"
    mother_size = len(mother_string)

    @staticmethod
    def generate(length=5):
        import random

        res = ""
        while length > 0:
            length -= 1
            res += HashGenerator.mother_string[
                random.randint(0, HashGenerator.mother_size - 1)
            ]
        return res


class Mediator:
    directions = [(+1, 0), (0, +1), (-1, 0), (0, -1)]

    def read_input(self):
        self.n = int(input())
        self.out = 0
        return self

    @staticmethod
    def clear_board(n: int) -> list:
        return [[False for j in range(n)] for i in range(n)]

    def dp(self, steps: int, board_set: AvlTree):
        # print('--')
        boards = [board_set, AvlTree()]
        turn = 0
        while steps > 0:
            steps -= 1
            for entry in boards[turn].get_list():
                # print(entry)
                i, j = entry
                for direction in range(4):
                    x, y = (
                        i + Mediator.directions[direction][0],
                        j + Mediator.directions[direction][1],
                    )
                    if x < 0:
                        x, y = y, -x
                    if y < 0:
                        x, y = -y, x
                    boards[1 ^ turn].insert((x, y))
                boards[turn].remove((i, j))
            turn ^= 1
        # print('<>')
        # print(boards[turn])
        xx = 0
        yy = 0
        zz = 0
        count = 0
        # print(boards[turn].get_list())
        for entry in boards[turn].get_list():
            # print(entry)
            i, j = entry
            if i == 0 and j == 0:
                zz = 1
                continue
            if i == 0:
                xx += 1
                continue
            if j == 0:
                yy += 1
                continue
            count += 1
        count *= 4
        count += 2 * (xx + yy) + zz
        return count

    def rotate(self, x, y, direction) -> tuple:
        mid = int(self.n / 2)
        dx, dy = (x - mid, y - mid)
        if direction == 1:
            x, y = dy, -dx
        elif direction == 2:
            x, y = -dx, -dy
        elif direction == 3:
            x, y = -dy, dx
        else:
            x, y = dx, dy
        return (x + mid, y + mid)

    def print_board(self):
        for i in range(self.n):
            for j in range(self.n):
                bl = False
                for direction in range(4):
                    bl |= self.board_direction[i][j][direction]
                print("#" if bl else ".", end="")
            print()

    def solve(self):
        steps = self.n - 2
        self.n += 10
        # center = int(self.n / 2)
        # self.board_direction = self.clear_board(self.n)
        # self.board_direction[center][center][0] = True
        a = AvlTree()
        a.insert((1, 1))
        self.out = self.dp(steps, a)
        # # self.print_board()
        # temp = [[False for j in range(self.n)] for i in range(self.n)]
        # for i in range(self.n):
        #     for j in range(self.n):
        #         bl = False
        #         for direction in range(4):
        #             bl |= board[i][j][direction]
        #         if bl:
        #             for direction in range(4):
        #                 x, y = self.rotate(i, j, direction)
        #                 temp[x][y] = True
        # count = 0
        # for i in range(self.n):
        #     for j in range(self.n):
        #         count += 1 if temp[i][j] else 0
        # self.out = count
        return self

    def output(self):
        print(self.out)
        return self


def main():
    Mediator().read_input().solve().output()


if __name__ == "__main__":
    main()
