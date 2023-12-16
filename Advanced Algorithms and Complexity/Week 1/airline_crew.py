# python3
import copy
import queue

class maximumMatching:
    def readData(self):
        n, m = map(int, input().split())
        adj_matrix = [list(map(int, input().split())) for i in range(n)]
        return adj_matrix
    def writeResponse(self, matching):
        line = [str(-1 if x == -1 else x + 1) for x in matching]
        print(' '.join(line))
    def Matching_f(self, adj_matrix):
        n = len(adj_matrix)
        m = len(adj_matrix[0])
        matching = [-1] * n
        busy_right = [False] * m
        def bfs():
            visited_Node = set()
            q = queue.Queue()
            q.put((1, None))
            visited_Node.add((1, None))
            path = []
            parent = dict()
            while not q.empty():
                current_node = q.get()
                if 1 == current_node[0]:
                    for i in range(n):
                        if -1 == matching[i]:
                            visited_Node.add((2, i))
                            parent[(2, i)] = (1, None)
                            q.put((2, i))
                elif 2 == current_node[0]:
                    i = current_node[1]
                    for j in range(m):
                        if 1 == adj_matrix[i][j] and j != matching[i] and not (3, j) in visited_Node:
                            visited_Node.add((3, j))
                            parent[(3, j)] = current_node
                            q.put((3, j))
                elif 3 == current_node[0]:
                    j = current_node[1]
                    if not busy_right[j]:
                        prevNode = current_node
                        current_node = (4, j)
                        while True:
                            path.insert(0, (prevNode, current_node))
                            if 1 == prevNode[0]:
                                break
                            current_node = prevNode
                            prevNode = parent[current_node]
                        for e in path:
                            if 2 == e[0][0]:
                                matching[e[0][1]] = e[1][1]
                            elif 3 == e[0][0] and 4 == e[1][0]:
                                busy_right[e[1][1]] = True
                        return True
                    else:
                        for i in range(n):
                            if j == matching[i] and not (2, i) in visited_Node:
                                visited_Node.add((2, i))
                                parent[(2, i)] = current_node
                                q.put((2, i))
            return False

        while bfs():
            continue
        return matching
    def solve(self):
        adj_matrix = self.readData()
        matching = self.Matching_f(adj_matrix)
        self.writeResponse(matching)

if __name__ == '__main__':
    max_matching = maximumMatching()
    max_matching.solve()