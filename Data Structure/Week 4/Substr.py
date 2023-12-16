# python3
import random


def hash_function(s, X, mod):
    ans = 0
    m = len(s)
    for j in range(m):
        ans = (ans + ord(s[j])*pow(X, m-j-1)) % mod
    return ans


def pre_process_string(s):
    n = len(s)
    base = pow(10, 9)
    M1 = base+7
    M2 = base+9
    X = 263
    h1 = [0 for _ in range(n+1)]
    h2 = [0 for _ in range(n+1)]
    for i in range(1, n+1):
        h1[i] = (X*h1[i-1] + ord(s[i-1])) % M1
        h2[i] = (X*h2[i-1] + ord(s[i-1])) % M2
    return X, h1, h2, M1, M2


def hash_value(table, prime, x, start, length):
    y = pow(x, length, prime)
    hash_value = (table[start+length] - y*table[start]) % prime
    return hash_value


def processQueries(s, queries):
    X, h1, h2, m1, m2 = pre_process_string(s)
    res = []
    for a, b, l in queries:
        a_m1 = hash_value(h1, m1, X, a, l)
        a_m2 = hash_value(h2, m2, X, a, l)
        b_m1 = hash_value(h1, m1, X, b, l)
        b_m2 = hash_value(h2, m2, X, b, l)
        if a_m1 == b_m1 and a_m2 == b_m2:
            res.append("Yes")
        else:
            res.append("No")
    return res


if __name__ == "__main__":
    s = input()
    n = int(input())
    qs = []
    for _ in range(n):
        qs.append(list(map(int, input().split())))
    rs = processQueries(s, qs)
    for r in rs:
        print(r)