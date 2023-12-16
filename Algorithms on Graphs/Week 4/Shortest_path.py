# Uses python3

import sys
import queue


def bfs(adj, s, n):
    dist = [None for i in range(n)]
    dist[s] = 0
    q = queue.Queue(maxsize=n)
    q.put(s)
    while not q.empty():
        u = q.get()
        for v in adj[u]:
            if dist[v] is None:
                q.put(v)
                dist[v] = dist[u] + 1
    reach = [1 if dist[i] is not None else 0 for i in range(n)]
    return reach


def relax(u, v, distance, cost):
    if distance[v] > distance[u] + cost:
        distance[v] = distance[u] + cost
        return True
    return False


def bellman_ford(adj, cost, s, distance, shortest, n):
    distance[s] = 0
    for iteration in range(n-1):
        for u in range(n):
            for id, v in enumerate(adj[u]):
                relax(u, v, distance, cost[u][id])
    negative = []
    for u in range(n):
        for id, v in enumerate(adj[u]):
            if relax(u, v, distance, cost[u][id]):
                negative.append(v)
    return negative


def OptiCurrency(adj, cost, s, distance, reachable, shortest, n):
    reachable = bfs(adj, s, n)
    negative = bellman_ford(adj, cost, s, distance, shortest, n)
    for node in negative:
        if shortest[node]:
            reached_nodes = bfs(adj, node, n)
            for id, node in enumerate(reached_nodes):
                if node == 1:
                    shortest[id] = 0
    return distance, reachable, shortest


if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))
    data = data[3 * m:]
    adj = [[] for _ in range(n)]
    cost = [[] for _ in range(n)]
    for ((a, b), w) in edges:
        adj[a - 1].append(b - 1)
        cost[a - 1].append(w)
    s = data[0]
    s -= 1
    distance = [float('inf')] * n
    reachable = [0] * n
    shortest = [1] * n
    distance, reachable, shortest = OptiCurrency(adj, cost, s, distance, reachable, shortest, n)
    for x in range(n):
        if reachable[x] == 0:
            print('*')
        elif shortest[x] == 0:
            print('-')
        else:
            print(distance[x])