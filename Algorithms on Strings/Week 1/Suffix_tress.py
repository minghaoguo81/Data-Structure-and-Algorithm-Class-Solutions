# python3
import sys


class Node:
    def __init__(self, label=''):
        self.children = {}
        self.label = label


class Trie:
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


def show_trie(root):
    queue = []
    queue.append(root)
    while queue:
        u = queue.pop()
        if u != root:
            print(u.label)
        for label, node in u.children.items():
            queue.append(node)


def build_SuffixTrees(text):
    trie = Trie(text)
    show_trie(trie.root)


if __name__ == '__main__':
    text = sys.stdin.readline().strip()
    build_SuffixTrees(text)