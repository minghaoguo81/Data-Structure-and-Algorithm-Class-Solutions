# python3

def first_last(s):
    counts = {'$': 0, "A": 0, 'C': 0, 'G': 0, 'T': 0}
    for char in s:
        counts[char] += 1
    c = {'$': 0}
    sum_so_far = counts['$']
    for char in ['A', 'C', 'G', 'T']:
        c[char] = sum_so_far
        sum_so_far += counts[char]
    arr = [0] * len(s)
    for i in range(len(s) - 1, -1, -1):
        arr[i] = counts[s[i]] + c[s[i]] - 1
        counts[s[i]] -= 1
    return arr

def bwt_inverse(bwt):
    f2l = first_last(bwt)
    cur = 0
    s = '$'
    for _ in range(1, len(bwt)):
        s += bwt[cur]
        cur = f2l[cur]
    return s[::-1]

if __name__ == '__main__':
    bwt = input()
    print(bwt_inverse(bwt))