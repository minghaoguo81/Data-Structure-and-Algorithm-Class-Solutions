# uses python3

def trie_f(patterns):
    tree = dict()
    node = 0

    for pattern in patterns:
        i = 0

        for letter in pattern:
            if tree.get(i):
                if letter not in tree[i]:
                    tree[i].update({letter: node+1})
                    node += 1
                    i = node
                else:
                    i = tree[i][letter]
                    # i += 1
            else:
                tree[i] = {letter: node+1}
                node += 1
                i += 1

    return tree

def findPattern(text, trie):
    indexes = []
    i = 0
    j = 0
    root = trie[0]
    v = root
    pattern_index = []
    while j < len(text):
        while i < len(text) and text[i] in v:
            if '$' in trie[v[text[i]]]:
                if pattern_index:
                    indexes.append(pattern_index[0])
                else:
                    indexes.append(j)
                break
            else:
                v = trie[v[text[i]]]
                pattern_index.append(i)
                i += 1
        j += 1
        i = j
        v = root
        pattern_index.clear()
    return indexes if len(indexes) > 0 else None


text = input()
n = int(input())
patterns = []

for i in range(n):
    patterns.append(input()+'$')

trie = trie_f(patterns)

ind_pattern = findPattern(text, trie)

if ind_pattern:
    print(' '.join (map (str, ind_pattern)))
else:
    print()