# python3
import random


def read_input():
    return (input().rstrip(), input().rstrip())


def print_occurrences(output):
    print(' '.join(map(str, output)))


def poly_hash(s, P, X):
    ans = 0
    for c in reversed(s):
        ans = (ans * X + ord(c)) % P
    return ans


def precompute_hashes(T, len_p, P, X):
    len_t = len(T)
    H = [0 for _ in range(len_t-len_p+1)]
    S = T[len_t-len_p:len_t]
    H[len_t-len_p] = poly_hash(S, P, X)
    y = pow(X, len_p, P)
    for i in range(len_t-len_p-1, -1, -1):
        H[i] = (X * H[i+1] + ord(T[i]) - y * ord(T[i+len_p])) % P
    return H


def rabinKarp(pattern, text):
    _prime = 1000000007
    _multiplier = 263
    res = []
    p_hash = poly_hash(pattern, _prime, _multiplier)
    len_p, len_t = len(pattern), len(text)
    H = precompute_hashes(text, len_p, _prime, _multiplier)
    for i in range(len_t-len_p+1):
        if p_hash != H[i]:
            continue
        if text[i:i+len_p] == pattern:
            res.append(i)
    return res


if __name__ == '__main__':
    print_occurrences(rabinKarp(*read_input()))