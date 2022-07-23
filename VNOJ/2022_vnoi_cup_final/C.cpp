#include "bits/stdc++.h"

// Tested:
// - https://open.kattis.com/problems/eulerianpath
struct EulerDirected {
    EulerDirected(int _n) : n(_n), adj(n), in_deg(n, 0), out_deg(n, 0) {}

    void add_edge(int u, int v) {  // directed edge
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        adj[u].push_front(v);
        in_deg[v]++;
        out_deg[u]++;
    }

    std::pair<bool, std::vector<int>> solve() {
        int start = -1, last = -1;
        for (int i = 0; i < n; i++) {
            // for all u, |in_deg(u) - out_deg(u)| <= 1
            if (std::abs(in_deg[i] - out_deg[i]) > 1) return {false, {}};

            if (out_deg[i] > in_deg[i]) {
                // At most 1 vertex with out_deg[u] - in_deg[u] = 1 (start vertex)
                if (start >= 0) return {false, {}};
                start = i;
            }

            if (in_deg[i] > out_deg[i]) {
                // At most 1 vertex with in_deg[u] - out_deg[u] = 1 (last vertex)
                if (last >= 0) return {false, {}};
                last = i;
            }
        }

        // can start at any vertex with degree > 0
        if (start < 0) {
            for (int i = 0; i < n; i++) {
                if (in_deg[i]) {
                    start = i;
                    break;
                }
            }
            // no start vertex --> all vertices have degree == 0
            if (start < 0) return {true, {}};
        }

        std::vector<int> path;
        find_path(start, path);
        std::reverse(path.begin(), path.end());

        // check that we visited all vertices with degree > 0
        std::vector<bool> visited(n, false);
        for (int u : path) visited[u] = true;

        for (int u = 0; u < n; u++) {
            if (in_deg[u] && !visited[u]) {
                return {false, {}};
            }
        }

        return {true, path};
    }

private:
    int n;
    std::vector<std::list<int>> adj;
    std::vector<int> in_deg, out_deg;

    void find_path(int v, std::vector<int>& path) {
        while (adj[v].size() > 0) {
            int next = adj[v].front();
            adj[v].pop_front();
            find_path(next, path);
        }
        path.push_back(v);
    }
};

long long hash_vowels(const std::string& s) {
    std::vector<int> cnt(5, 0);
    for (char c : s) {
        if (c == 'a') ++cnt[0];
        if (c == 'e') ++cnt[1];
        if (c == 'i') ++cnt[2];
        if (c == 'o') ++cnt[3];
        if (c == 'u') ++cnt[4];
    }

    long long h = 0;
    for (int i = 0; i < 5; i++) {
        h = h * 311 + cnt[i] + 1;
    }
    return h;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int nLines; std::cin >> nLines;
    // input lines
    std::vector<std::string> lines;

    // map: (hash of last word) -> ids of six
    std::map<long long, std::vector<int>> hashToSix;
    // map: (hash of 6-th and 8-th words) -> ids of eights
    std::map<std::pair<long long, long long>, std::vector<int>> hashToEight;

    // map: (any hash) -> id
    std::map<long long, int> ids;
    std::map<int, long long> idToHashes;
    auto addHash = [&] (long long newHash) {
        if (ids.count(newHash)) return;

        int val = (int) ids.size();
        ids[newHash] = val;
        idToHashes[val] = newHash;
    };

    std::vector< std::pair<long long, long long> > edges;

    for (int len : {6, 8}) {
        for (int i = 0; i < nLines; i++) {
            std::string line = "";
            std::vector<std::string> words;
            for (int j = 0; j < len; j++) {
                std::string word; std::cin >> word;
                words.push_back(word);

                if (j > 0) line += ' ';
                line += word;
            }

            lines.push_back(line);
            if (len == 6) {
                auto h = hash_vowels(words.back());
                hashToSix[h].push_back(i);
            } else {
                auto h1 = hash_vowels(words[5]);
                auto h2 = hash_vowels(words[7]);
                hashToEight[{h1, h2}].push_back(i + nLines);
                addHash(h1);
                addHash(h2);
                edges.push_back({h1, h2});
            }
        }
    }

    int n = (int) ids.size();
    EulerDirected euler(n);

    for (auto [h1, h2] : edges) {
        euler.add_edge(ids[h1], ids[h2]);
    }

    auto [can, path] = euler.solve();

    auto no = [&] () {
        std::cout << "NO\n";
        return 0;
    };

    if (!can) return no();

    std::vector<int> res;
    for (int i = 0; i < -1 + (int) path.size(); ++i) {
        auto h1 = idToHashes[path[i]];
        auto h2 = idToHashes[path[i+1]];

        if (hashToSix[h1].empty()) return no();
        else {
            res.push_back(hashToSix[h1].back());
            hashToSix[h1].pop_back();
        }

        auto h12 = std::make_pair(h1, h2);
        if (hashToEight[h12].empty()) return no();
        else {
            res.push_back(hashToEight[h12].back());
            hashToEight[h12].pop_back();
        }
    }

    std::cout << "YES\n";
    for (int r : res) {
        std::cout << lines[r] << '\n';
    }
    return 0;
}
