# python3

import sys
import threading
sys.setrecursionlimit(10**7)
threading.stack_size(2**27)


class Node:
    def __init__(self, key=None):
        self.key = key
        self.children = []


def buildTree(n, node_data):
    nodes = [Node(i) for i in range(n)]
    root = None
    for child in range(n):
        parent = node_data[child]
        if parent == -1:
            root = child
        else:
            nodes[parent].children.append(nodes[child])
    return 1 + findHeit(nodes[root].children)


def findHeit(tree):
    if not tree:
        return 0
    return 1 + max(findHeit(child.children) for child in tree)


def main():
    n = int(input())
    node_data = list(map(int, input().split()))
    print(buildTree(n, node_data))

threading.Thread(target=main).start()