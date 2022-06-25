#include "bits/stdc++.h"
using namespace std;

struct PartiallyPersistentDSU {
    vector<int> lab, t_unite;

    PartiallyPersistentDSU(int n)
            : lab(n + 1, -1), t_unite(n + 1, INT_MAX) {}

    // return root
    int getRoot(int t, int x) {
        if (t_unite[x] > t) {
            return x;
        }
        return getRoot(t, lab[x]);
    }

    void merge(int t, int x, int y) {
        int root_x = getRoot(t, x);
        int root_y = getRoot(t, y);
        x = root_x; y = root_y;
        if (x == y) {
            return;
        }
        if (lab[x] > lab[y]) {
            std::swap(x, y);
        }
        lab[x] += lab[y];
        lab[y] = x;
        t_unite[y] = t;
    }
};

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    PartiallyPersistentDSU dsu(n);

    // read input and handle add_edge
    std::vector< std::tuple<int, int, int> > queries(q);
    for (int i = 0; i < q; i++) {
        int typ; std::cin >> typ;
        if (typ == 1) {
            // add_edge(u, v)
            int u, v; std::cin >> u >> v;
            --u; --v;

            dsu.merge(i, u, v);
            queries[i] = {typ, u, v};
        } else if (typ == 2) {
            // add_friend(x, y)
            int x, y; std::cin >> x >> y;
            --x; --y;
            queries[i] = {typ, x, y};
        } else {
            // query(u)
            int u; std::cin >> u;
            --u;
            queries[i] = {typ, u, -1};
        }
    }

    // handle add_friends
    // connected_friend_times[u] contains the moments where number of connected
    //  friends of u increases
    std::vector<std::vector<int>> connected_friend_times(n);
    for (int i = 0; i < q; i++) {
        auto [typ, x, y] = queries[i];
        if (typ != 2) continue;

        // binary search to find the smallest time where x and y are connected
        // time = q -> not connected
        auto r = std::views::iota(0, q);
        auto res = std::ranges::partition_point(
                r,
                [&] (int mid) {
                    return dsu.getRoot(mid, x) != dsu.getRoot(mid, y);
                }) - r.begin();

        if (res != q) {
            connected_friend_times[x].push_back(std::max(i, (int) res));
            connected_friend_times[y].push_back(std::max(i, (int) res));
        }
    }

    for (int i = 0; i < n; i++) {
        std::sort(connected_friend_times[i].begin(), connected_friend_times[i].end());
        connected_friend_times[i].push_back(q);
    }

    // handle queries
    for (int i = 0; i < q; i++) {
        auto [typ, u, _] = queries[i];
        if (typ != 3) continue;

        int id = std::lower_bound(
                connected_friend_times[u].begin(),
                connected_friend_times[u].end(),
                i) - connected_friend_times[u].begin();
        std::cout << id << '\n';
    }

    return 0;
}
