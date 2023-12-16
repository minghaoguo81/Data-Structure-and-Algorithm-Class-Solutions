#include <iostream>
#include <vector>
#include <vector>
#include <bitset>

constexpr int INF = 1e9;

struct node {
    int dist{ INF };
    int parent{ 0 };
};

using namespace std;

using matrix = vector<vector<int> >;
using subset = vector<int>;
using cost = vector<vector<node> >;
using tour = pair<int, vector<int> >;

matrix read_data() noexcept
{
    ios::sync_with_stdio(false);

    int vertex_count, edge_count;
    cin >> vertex_count >> edge_count;
    matrix graph(vertex_count, vector<int>(vertex_count, INF));

    for (int i = 0, from, to, weight; i < edge_count; ++i) {
        cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }

    return graph;
}

struct TSP {
    TSP(matrix complete_graph)
        : N{ (int)complete_graph.size() }
        , C{ cost(1 << (N), std::vector<node>(N)) }
        , dist{ std::move(complete_graph) }
    {
        for (int k = 1; k < N; ++k) {
            C[1 << k][k] = node{ dist[0][k], 0 };
        }
    }

    tour optimal_tour() noexcept
    {
        for (int s = 2; s < 1 << (N - 1); ++s) {
            if (s & (s - 1)) {
                subset S = combinations(s);
                int bits = s * 2;

                for (auto k : S) {
                    int prev = bits ^ (1 << k);
                    node min_node;

                    for (auto m : S) {
                        if (C[prev][m].dist + dist[m][k] < min_node.dist && k != m) {
                            min_node = node{ C[prev][m].dist + dist[m][k], m };
                        }
                    }
                    C[bits][k] = min_node;
                }
            }
        }

        return backtrack_optimal();
    }

    subset combinations(const int n) noexcept
    {
        subset combs;
        bitset<16> bset = n;

        for (auto k = 0u; k < bset.size(); ++k) {
            if (bset[k]) {
                combs.emplace_back(k + 1);
            }
        }

        return combs;
    }

    tour backtrack_optimal() noexcept
    {
        node min_node;
        int bits = (1 << N) - 2;

        for (int k = 1; k < N; ++k) {
            if (min_node.dist > C[bits][k].dist + dist[k][0]) {
                min_node = node{ C[bits][k].dist + dist[k][0], k };
            }
        }

        if (min_node.dist == INF) {
            return { -1, {} };
        }

        tour optimal_tour;

        optimal_tour.second.reserve(N);
        optimal_tour.first = min_node.dist;
        optimal_tour.second.emplace_back(1);

        for (int i = 0; i < N - 1; ++i) {
            optimal_tour.second.emplace_back(min_node.parent + 1);
            min_node.parent = C[bits][min_node.parent].parent;
            bits = bits ^ (1 << (optimal_tour.second.back() - 1));
        }

        return optimal_tour;
    }

    const int N;
    cost C;
    matrix dist;
};

void print_answer(const tour& answer) noexcept
{
    printf("%d\n", answer.first);
    if (answer.first == -1)
        return;
    for (auto p : answer.second)
        printf("%d ", p);
    printf("\n");
}

int main()
{
    TSP tsp(read_data());
    print_answer(tsp.optimal_tour());
    return 0;
}