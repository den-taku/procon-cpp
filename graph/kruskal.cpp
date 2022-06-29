#include <vector>
#include <iostream>
#include <tuple>
#include <optional>
#include <algorithm>

typedef std::tuple<unsigned long long, size_t, size_t> edge_t;


namespace kruskal {
    namespace disjoint_set {
        class DisjointSet {
            private:
                std::vector<size_t> parent;
                std::vector<size_t> rank;
            public:
                DisjointSet(size_t n);
                size_t find(size_t x);
                bool unite(size_t x, size_t y);
                bool same(size_t x, size_t y);
        };

        DisjointSet::DisjointSet(size_t n) {
            parent = std::vector<size_t>(n);
            for (size_t i = 0; i < n; ++i) {
                parent[i] = i;
            }
            rank = std::vector<size_t>(n, 0);
        }

        size_t DisjointSet::find(size_t x) {
            if (parent[x] == x) {
                return x;
            } else {
                auto represent = x;
                do {
                    represent = parent[represent];
                } while (parent[represent] != represent);
                parent[x] = represent;
                return represent;
            }
        }

        bool DisjointSet::unite(size_t x, size_t y) {
            auto x_par = this->find(x);
            auto y_par = this->find(y);
            if (x_par != y_par) {
                if (rank[x_par] < rank[y_par]) {
                    parent[x_par] = y_par;
                } else {
                    parent[y_par] = x_par;
                    if (rank[x_par] == rank[y_par]) {
                        rank[x_par] += 1;
                    }
                }
            }
            return x_par != y_par;
        }

        bool DisjointSet::same(size_t x, size_t y) {
            return this->find(x) == this->find(y);
        }
    }

    class Kruskal {
        private:
            size_t vertices;
            std::vector<edge_t> edges;
        public:
            Kruskal(size_t vertices);
            void add_edge(size_t u, size_t v, unsigned long long wight);
            std::optional<unsigned long long> minimum_spanning_tree();
    };

    Kruskal::Kruskal(size_t vertices) : vertices(vertices) {
        edges = std::vector<edge_t>();
    }

    void Kruskal::add_edge(size_t u, size_t v, unsigned long long weight) {
        edges.push_back(std::make_tuple(weight, u, v));
    }

    std::optional<unsigned long long> Kruskal::minimum_spanning_tree() {
        auto sets = disjoint_set::DisjointSet(vertices);
        std::sort(edges.begin(), edges.end());

        unsigned long long sum = 0;
        unsigned long long count = 0;
        for (const auto &e : edges) {
            auto u = std::get<1>(e);
            auto v = std::get<2>(e);
            auto w = std::get<0>(e);

            if (sets.same(u, v)) {
                continue;
            }

            sets.unite(u, v);
            sum += w;
            count += 1;
            if (count == vertices - 1) {
                break;
            }
        }
        if (count == vertices -1) {
            return std::make_optional(sum);
        } else {
            return std::nullopt;
        }
    }
}

int main() {
    using namespace std;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    size_t u, v;
    unsigned long long w;
    cin >> n >> m;

    auto k = kruskal::Kruskal(n);
    for (size_t i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        k.add_edge(u, v, w);
    }

    auto tree = k.minimum_spanning_tree();
    if (tree) {
        cout << tree.value() << endl;
    }
}