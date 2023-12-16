# python3

def com_pre(S):
    n = len(S)
    s = [None] * n
    s[0] = 0
    border = 0
    for i in range(1, n):
        while border and S[i] != S[border]:
            border = s[border - 1]
        if S[i] == S[border]:
            border += 1
        else:
            border = 0
        s[i] = border
    return s

def find_pat(pattern, text):
    result = []
    S = pattern + '$' + text
    pre = com_pre(S)
    p = len(pattern)
    for i in range(p + 1, len(S)):
        if pre[i] == p:
            result.append(i-2*p)
    return result

if __name__ == '__main__':
    pattern = input()
    text = input()
    result = find_pat(pattern, text)
    print(" ".join(map(str, result)))