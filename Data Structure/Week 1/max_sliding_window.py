# python3
from collections import deque


def maxSliding_Window(n, arr, k):
    q = deque()
    for i in range(k):
        while q and arr[q[-1]] < arr[i]:
            q.pop()
        q.append(i)

    for i in range(k, n):
        print(str(arr[q[0]]) + ' ', end='')
        while q and q[0] <= i - k:
            q.popleft()
        while q and arr[i] >= arr[q[-1]]:
            q.pop()
        q.append(i)
    print(str(arr[q[0]]))


if __name__ == '__main__':
    n = int(input())
    input_sequence = [int(i) for i in input().split()]
    assert len(input_sequence) == n
    window_size = int(input())
    maxSliding_Window(n, input_sequence, window_size)