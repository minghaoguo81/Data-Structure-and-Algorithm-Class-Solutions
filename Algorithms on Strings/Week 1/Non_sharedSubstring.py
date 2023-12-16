# python3
import sys
import threading

sys.setrecursionlimit(10**7)
threading.stack_size(2**25)


class Node:
    def __init__(self, label=''):
        self.children = {}
        self.label = label
        self.type = 1
        self.visited = False
        self.parent = None


class SuffixTree:
    def __init__(self, s):
        self.root = Node()
        self.root.children[s[0]] = Node(s)
        self.add(s)

    def add(self, word):
        for i in range(1, len(word)):
            cur = self.root
            j = i
            while j < len(word):
                if word[j] in cur.children:
                    child = cur.children[word[j]]
                    label = child.label
                    k = j + 1
                    while k - j < len(label) and word[k] == label[k - j]:
                        k += 1
                    if k - j == len(label):
                        cur = child
                        j = k
                    else:
                        c_exist, c_new = label[k - j], word[k]
                        mid = Node(label[:k - j])
                        mid.children[c_new] = Node(word[k:])
                        child.label = label[k - j:]
                        mid.children[c_exist] = child
                        cur.children[word[j]] = mid
                else:
                    cur.children[word[j]] = Node(word[j:])

    def shortest_UncommonStrings(self):
        leaves_1 = []
        self.explore(self.root, leaves_1)
        results = []
        for leaf in leaves_1:
            char = ''
            substring = ''
            cur = leaf.parent
            if leaf.label[0] == '#' and cur.type == 2:
                continue
            elif cur.type == 2:
                char += leaf.label[0]
            while cur != self.root:
                substring = cur.label + substring
                cur = cur.parent
            substring += char
            results.append(substring)
        result = min(results, key=lambda x: len(x))
        return result

    def explore(self, cur, leaves_1):
        cur.visited = True
        if len(cur.children) == 0:
            if '#' not in cur.label:
                cur.type = 2
            else:
                leaves_1.append(cur)
        else:
            for char, node in cur.children.items():
                if not node.visited:
                    node.parent = cur
                    self.explore(node, leaves_1)
            for char, node in cur.children.items():
                if node.type == 2:
                    cur.type = 2


def solve(p, q):
    text = p + '#' + q + '$'
    tree = SuffixTree(text)
    return tree.shortest_UncommonStrings()


if __name__ == '__main__':
    s = input()
    t = input()
    print(solve(s, t))  