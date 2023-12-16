# python3
import queue

class Edge:

    def __init__(self, u, v, capacity):
        self.u = u
        self.v = v
        self.capacity = capacity
        self.flow = 0

class Flow_Graph:
    def __init__(self, n):
        self.edges = []
        self.graph = [[] for _ in range(n)]

    def add_edge(self, from_, to, capacity):
        forward_edge = Edge(from_, to, capacity)
        backward_edge = Edge(to, from_, 0)
        self.graph[from_].append(len(self.edges))
        self.edges.append(forward_edge)
        self.graph[to].append(len(self.edges))
        self.edges.append(backward_edge)

    def size(self):
        return len(self.graph)

    def get_ids(self, from_):
        return self.graph[from_]

    def get_edge(self, id):
        return self.edges[id]

    def add_flow(self, id, flow):
        self.edges[id].flow += flow
        self.edges[id ^ 1].flow -= flow
        self.edges[id].capacity -= flow
        self.edges[id ^ 1].capacity += flow


def read_data():
    vertex_count, edge_count = map(int, input().split())
    graph = Flow_Graph(vertex_count)
    for _ in range(edge_count):
        u, v, capacity = map(int, input().split())
        graph.add_edge(u - 1, v - 1, capacity)
    return graph


def maximumFlow(graph, from_, to):
    flow = 0
    while True:
        has_Path, path, X = Evac(graph, from_, to)
        if not has_Path:
            return flow
        for id in path:
            graph.add_flow(id, X)
        flow += X
    return flow

def Evac(graph, from_, to):
    X = float('inf')
    has_Path = False
    n = graph.size()
    dist = [float('inf')]*n
    path = []
    parent = [(None, None)]*n
    q = queue.Queue()
    dist[from_] = 0
    q.put(from_)
    while not q.empty():
        currFromNode = q.get()
        for id in graph.get_ids(currFromNode):
            currEdge = graph.get_edge(id)
            if float('inf') == dist[currEdge.v] and currEdge.capacity > 0:
                dist[currEdge.v] = dist[currFromNode] + 1
                parent[currEdge.v] = (currFromNode, id)
                q.put(currEdge.v)
                if currEdge.v == to:
                    while True:
                        path.insert(0, id)
                        currX = graph.get_edge(id).capacity
                        X = min(currX, X)
                        if currFromNode == from_:
                            break
                        currFromNode, id = parent[currFromNode]
                    has_Path = True
                    return has_Path, path, X
    return has_Path, path, X

if __name__ == '__main__':
    graph = read_data()
    print(maximumFlow(graph, 0, graph.size() - 1))