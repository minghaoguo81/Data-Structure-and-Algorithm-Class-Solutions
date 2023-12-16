#python3

def poly_hash(s, prime, multiplier):
    ans = 0
    for c in reversed(s):
        ans = (ans * multiplier + ord(c)) % prime
    return ans


def create_hash_table(s, len_p, prime, multiplier):
    len_s = len(s)
    last_substring = s[len_s-len_p:]
    hash_table = [0 for _ in range(len_s - len_p + 1)]
    hash_table[len_s-len_p] = poly_hash(last_substring, prime, multiplier)
    y = pow(multiplier, len_p, prime)
    for i in range(len_s-len_p-1, -1, -1):
        hash_table[i] = (multiplier*hash_table[i+1] + ord(s[i]) - y * ord(s[i+len_p])) % prime
    return hash_table


def create_hash_dict(s, len_p, prime, multiplier):
    hash_dict = {}
    len_s = len(s)
    last_substring = s[len_s-len_p:]
    last = poly_hash(last_substring, prime, multiplier)
    hash_dict[last] = len_s-len_p
    y = pow(multiplier, len_p, prime)
    for j in range(len_s-len_p-1, -1, -1):
        current_hash = (multiplier * last + ord(s[j]) - y * ord(s[j + len_p])) % prime
        hash_dict[current_hash] = j
        last = current_hash
    return hash_dict


def search_substring(hash_table, hash_dict):
    found = False
    matches = {}
    for i in range(len(hash_table)):
        start_pos = hash_dict.get(hash_table[i], -1)
        if start_pos != -1:
            found = True
            matches[i] = start_pos
    return found, matches


def search_hash(s1, s2, k):
    res = {'found': False}
    prime1 = 1000000007
    prime2 = 1000004249
    x = 263
    hash_table_1 = create_hash_table(s1, k, prime1, x)
    hash_table_2 = create_hash_table(s1, k, prime2, x)
    hash_dict_1 = create_hash_dict(s2, k, prime1, x)
    hash_dict_2 = create_hash_dict(s2, k, prime2, x)
    found1, matches1 = search_substring(hash_table_1, hash_dict_1)
    found2, matches2 = search_substring(hash_table_2, hash_dict_2)
    if found1 and found2:
        for a, b in matches1.items():
            temp = matches2.get(a, -1)
            if temp != -1:
                res['found'] = True
                res['max_length'] = k
                res['1'] = a
                res['2'] = b
                break
    return res


def find_maxLength(s1, s2):
    swapped = False
    if len(s1) < len(s2):
        swapped = True
        s1, s2 = s2, s1
    low = 0
    high = len(s2)
    start1, start2, max_len = 0, 0, 0
    while low <= high:
        mid = (low+high)//2
        result = search_hash(s1, s2, mid)
        if result['found']:
            low = mid + 1
            start1, start2, max_len = result['1'], result['2'], result['max_length']
        else:
            high = mid - 1
    if swapped:
        return start2, start1, max_len
    return start1, start2, max_len


if __name__ == '__main__':
    while True:
        line = input()
        if not line:
            break
        else:
            s1, s2 = line.split()
            print('{} {} {}'.format(*find_maxLength(s1, s2)))