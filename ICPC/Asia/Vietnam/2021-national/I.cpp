#include <bits/stdc++.h>

const int NTYPE = 5;
using State = std::array<int, NTYPE>;

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    // Read input
    int n; std::cin >> n;
    std::vector<State> types(n);
    for (auto& type : types) {
        int k; std::cin >> k;
        while (k--) {
            std::string s; std::cin >> s;
            if (s == "dp") ++type[0];
            if (s == "graph") ++type[1];
            if (s == "mathgeo") ++type[2];
            if (s == "ds") ++type[3];
            if (s == "adhoc") ++type[4];
        }
    }

    State min_types, max_types;
    for (int i = 0; i < NTYPE; i++) {
        std::cin >> min_types[i] >> max_types[i];
    }

    // DP
    std::vector< std::map<State, long long> > f(n + 1);
    f[0][{0, 0, 0, 0, 0}] = 1;

    for (int processed = 0; processed < n; processed++) {
        for (auto [state, cnt] : f[processed]) {
            // do not use this task
            auto new_state = state;
            f[processed + 1][new_state] += cnt;

            // use this task
            bool valid = true;
            for (int i = 0; i < NTYPE; i++) {
                new_state[i] += types[processed][i];
                if (new_state[i] > max_types[i]) valid = false;
            }
            if (valid) f[processed + 1][new_state] += cnt;
        }
    }

    auto is_valid = [min_types, max_types] (State state) {
        for (int i = 0; i < NTYPE; i++) {
            if (state[i] < min_types[i] || state[i] > max_types[i]) {
                return false;
            }
        }
        return std::accumulate(state.begin(), state.end(), 0LL) > 0;
    };

    long long res = 0;
    for (auto [state, cnt] : f.back()) {
        if (is_valid(state)) res += cnt;
    }
    std::cout << res << std::endl;
    return 0;
}
