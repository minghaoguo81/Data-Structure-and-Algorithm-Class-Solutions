# python3

def sort_chars(s, chars):
    n = len(s)
    order = [None] * n
    count = [0] * n
    chars = [ch for ch in chars if ch in s]
    ch = {c: id for id, c in enumerate(chars)}
    for i in range(n):
        count[ch[s[i]]] += 1
    for j in range(1, len(chars)):
        count[j] += count[j - 1]
    for i in range(n - 1, -1, -1):
        c_id = ch[s[i]]
        count[c_id] -= 1
        order[count[c_id]] = i
    return order


def compute_classes(s, order):
    n = len(s)
    class_ = [None] * n
    class_[order[0]] = 0
    for i in range(1, n):
        if s[order[i]] != s[order[i - 1]]:
            class_[order[i]] = class_[order[i - 1]] + 1
        else:
            class_[order[i]] = class_[order[i - 1]]
    return class_


def Sorted_double(s, L, order, class_):
    n = len(s)
    count = [0] * n
    new_order = [None] * n
    for i in range(n):
        count[class_[i]] += 1
    for j in range(1, n):
        count[j] += count[j - 1]
    for i in range(n - 1, -1, -1):
        start = (order[i] - L + n) % n
        cl = class_[start]
        count[cl] -= 1
        new_order[count[cl]] = start
    return new_order


def Updated_class(order, class_, L):
    n = len(order)
    new_class = [None] * n
    new_class[order[0]] = 0
    for i in range(1, n):
        cur = order[i]
        prev = order[i - 1]
        mid = (cur + L) % n
        mid_prev = (prev + L) % n
        if class_[cur] != class_[prev] or class_[mid] != class_[mid_prev]:
            new_class[cur] = new_class[prev] + 1
        else:
            new_class[cur] = new_class[prev]
    return new_class


def Suffix_array(text, chars=['$', 'A', 'C', 'G', 'T']):
    order = []
    order = sort_chars(text, chars)
    class_ = compute_classes(text, order)
    L = 1
    while L < len(text):
        order = Sorted_double(text, L, order, class_)
        class_ = Updated_class(order, class_, L)
        L = 2*L
    return order[1:]


def match_with_suffix(t, p, sa):
    min = 0
    max = len(t)
    while min < max:
        mid = (min + max) // 2
        suffix = sa[mid]
        i = 0
        while i < len(p) and suffix + i < len(t):
            if p[i] > t[suffix + i]:
                min = mid + 1
                break
            elif p[i] < t[suffix + i]:
                max = mid
                break
            i += 1
            if i == len(p):
                max = mid
            elif suffix + i == len(t):
                min = mid + 1
    start = min
    max = len(t)
    while min < max:
        mid = (min + max) // 2
        suffix = sa[mid]
        i = 0
        while i < len(p) and suffix + i < len(t):
            if p[i] < t[suffix + i]:
                max = mid
                break
            i += 1
            if i == len(p) and i <= len(t) - suffix:
                min = mid + 1
    end = max - 1
    return start, end


def find_occur(text, patterns):
    suffix_arr = Suffix_array(text+'$')
    res = [0]*len(text)
    for pattern in patterns:
        s, e = match_with_suffix(text, pattern, suffix_arr)
        if s <= e:
            for i in range(s, e + 1):
                pos = suffix_arr[i]
                if res[pos] == 0:
                    print(pos, end=' ')
                res[pos] += 1


if __name__ == '__main__':
    text = input()
    n = int(input())
    patterns = input().split()
    find_occur(text, patterns)