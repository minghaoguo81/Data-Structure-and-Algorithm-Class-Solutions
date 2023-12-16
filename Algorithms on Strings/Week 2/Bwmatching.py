# python3

def preprocessBwt(bwt, symbols=['$', 'A', 'C', 'G', 'T']):
    n = len(bwt)
    bwt_sorted = sorted(bwt)
    c = {ch: 0 for ch in symbols}
    count = {ch: [0 for _ in range(n+1)] for ch in symbols}
    for i in range(n):
        c[bwt[i]] += 1
        for ch in symbols:
            count[ch][i+1] = c[ch]
    first = {}
    for id, ch in enumerate(bwt_sorted):
        if first.get(ch, None) is None:
            first[ch] = id
    return count, first


def bwt_match(bwt, pattern, count, first):
    top = 0
    bottom = len(bwt) - 1
    while top <= bottom:
        if pattern:
            symbol = pattern.pop()
            if symbol in bwt[top:bottom + 1]:
                top = first[symbol] + count[symbol][top]
                bottom = first[symbol] + count[symbol][bottom + 1] - 1
            else:
                return 0
        else:
            return bottom - top + 1


def main(bwt, patterns):
    count, first = preprocessBwt(bwt)
    res = []
    for pattern in patterns:
        res.append(str(bwt_match(bwt, list(pattern), count, first)))
    print(' '.join(res))
    

if __name__ == '__main__':
    bwt = input()
    n = int(input())
    patterns = input().split()
    main(bwt, patterns)