// Shortest Path (https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A): 00.24s
#include <cstddef>
#include <climits>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

typedef struct Edge Edge;

class Edge {
    public:
        size_t to;
        unsigned long cost;
    public:
        Edge(size_t to, unsigned long cost);
};

Edge::Edge(size_t to, unsigned long cost) : to(to), cost(cost){}

class State {
    public:
        unsigned long cost;
        size_t position;
    public:
        State(unsigned long cost, size_t position);
};

State::State(unsigned long cost, size_t position) : cost(cost), position(position) {}

bool operator<(const State& s1, const State& s2) {
    if (s1.cost == s2.cost) {
        return s1.position > s2.position;
    } else {
        return s1.cost > s2.cost;
    }
}

class Dijkstra {
    public:
        size_t nodes;
        std::vector<std::vector<Edge>> edges;

    public:
        Dijkstra(size_t node);
        void add_edge(size_t from, size_t to, unsigned int cost);
        std::vector<unsigned long> shortest_path(size_t start);
};

Dijkstra::Dijkstra(size_t node) {
    nodes = node;
    edges = std::vector<std::vector<Edge>>(node);
}

void Dijkstra::add_edge(size_t from, size_t to, unsigned int cost) {
    edges[from].push_back(Edge(to, cost));
}

std::vector<unsigned long> Dijkstra::shortest_path(size_t start) {
    auto dist = std::vector<unsigned long>(nodes, ULONG_MAX);
    dist[start] = 0;
    auto pre = std::vector<size_t>(nodes, 0);

    auto heap = std::priority_queue<State>();
    heap.push(State(0, start));

    while (!heap.empty()) {
        auto state = heap.top();
        heap.pop();
        // std::cout << '(' << state.cost << ',' << state.position << ')' << std::endl;
        if (state.cost > dist[state.position]) {
            continue;
        }

        for(const auto& edge: edges[state.position]) {
            auto next = State(state.cost + edge.cost, edge.to);
            if (next.cost < dist[next.position]) {
                heap.push(next);
                dist[next.position] = next.cost;
                pre[next.position] = state.position;
            }
        }
    }

    return dist;
}

int main() {
    using namespace std;

    // input
    size_t n;
    size_t m;
    size_t start;

    size_t from;
    size_t to;
    unsigned long cost;

    cin >> n;
    cin >> m;
    cin >> start;

    // Dijkstra
    Dijkstra dijkstra = Dijkstra(n);
    for (size_t i = 0; i < m; ++i) {
        cin >> from >> to >> cost;
        dijkstra.add_edge(from, to, cost);
    }
    auto shortest_path = dijkstra.shortest_path(start);

    for (const auto& e: shortest_path) {
        if (e == ULONG_MAX) {
            cout << "INF\n";
        } else {
            cout << e << '\n';
        }
    }
    cout << flush;

    return 0;
}