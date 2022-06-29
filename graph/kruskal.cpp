#include <vector>
#include <iostream>

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
                represent = parent[x];
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

int main() {
    using namespace std;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //
}