# python3

import sys
import threading

sys.setrecursionlimit(2*10**9)
threading.stack_size(2**27)
root = None

class Vertex:
    def __init__(self, key, char, size, left, right, parent):
        (self.key, self.char, self.size, self.left, self.right,
         self.parent) = (key, char, size, left, right, parent)


def update(v):
    if v == None:
        return
    v.size = 1 + (v.left.size if v.left != None else 0) + \
        (v.right.size if v.right != None else 0)
    if v.left != None:
        v.left.parent = v
    if v.right != None:
        v.right.parent = v


def small_rotation(v):
    parent = v.parent
    if parent == None:
        return
    grandparent = v.parent.parent
    if parent.left == v:
        m = v.right
        v.right = parent
        parent.left = m
    else:
        m = v.left
        v.left = parent
        parent.right = m
    update(parent)
    update(v)
    v.parent = grandparent
    if grandparent != None:
        if grandparent.left == parent:
            grandparent.left = v
        else:
            grandparent.right = v


def big_rotation(v):
    if v.parent.left == v and v.parent.parent.left == v.parent:
        small_rotation(v.parent)
        small_rotation(v)
    elif v.parent.right == v and v.parent.parent.right == v.parent:
        small_rotation(v.parent)
        small_rotation(v)
    else:
        small_rotation(v)
        small_rotation(v)


def splay(v):
    if v == None:
        return None
    while v.parent != None:
        if v.parent.parent == None:
            small_rotation(v)
            break
        big_rotation(v)
    return v


def find_order_statistic(node, k):
    if not node:
        return None
    if not node.left:
        s = 0
    else:
        s = node.left.size
    if k == s+1:
        return node
    elif k < s+1:
        return find_order_statistic(node.left, k)
    else:
        return find_order_statistic(node.right, k-s-1)


def find_order_iterative(node, k):
    while True:
        if not node:
            return None
        if not node.left:
            s = 0
        else:
            s = node.left.size
        if k == s+1:
            return node
        elif k < s+1:
            node = node.left
        else:
            node = node.right
            k = k - s - 1


def split(root, k):
    split_node = find_order_iterative(root, k)
    if split_node is None:
        return (root, None)
    right = splay(split_node)
    left = right.left
    right.left = None
    if left != None:
        left.parent = None
    update(left)
    update(right)
    return (left, right)


def merge(left, right):
    if left is None:
        return right
    if right is None:
        return left
    while right.left != None:
        right = right.left
    right = splay(right)
    right.left = left
    update(right)
    return right


def in_order_traversal(root, res=[]):
    if not root:
        return res
    res = in_order_traversal(root.left, res)
    res.append(root.char)
    res = in_order_traversal(root.right, res)
    return res


def in_order_iterative(root):
    cur = root
    stack = []
    chars = []
    while True:
        if cur is not None:
            stack.append(cur)
            cur = cur.left
        elif(stack):
            cur = stack.pop()
            chars.append(cur.char)
            cur = cur.right
        else:
            break
    return chars


def make_tree():
    global root
    s = sys.stdin.readline().strip()
    n = int(sys.stdin.readline())
    qs = []
    for _ in range(n):
        qs.append(list(map(int, sys.stdin.readline().split())))
    for id, char in enumerate(s):
        new_vertex = Vertex(id, char, 1, None, None, None)
        root = merge(root, new_vertex)
    for i, j, k in qs:
        processQueries(i, j, k)
    show_node(root)


def show_node(node):
    print(''.join(in_order_iterative(root)))


def processQueries(i, j, k):
    global root
    i, j, k = i+1, j+1, k+1
    useful, rem = split(root, j+1)
    pre, to_use = split(useful, i)
    root = merge(pre, rem)
    prefix, suffix = split(root, k)
    root = merge(merge(prefix, to_use), suffix)


threading.Thread(target=make_tree).start()