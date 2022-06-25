#include "bits/stdc++.h"
using namespace std;

std::vector<long long> p;
std::set<long long> allHashes;
std::map<long long, int> cached;
int f(const string& s, const std::vector<long long>& h) {
    int found = INT_MAX;
    for (int i = 0; i < (int) s.size(); i++) {
        auto right = h.back() - h[i];
        auto curHash = h[i] + s[i] * p[i+1] + right * p[1];

        if (!allHashes.count(curHash)) {
            return cached[h.back()] = 1;
        }

        if (cached.count(curHash)) {
            found = std::min(found, cached[curHash] + 1);
        }
    }

    return cached[h.back()] = found;
}

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    p.resize(1000111);
    p[0] = 1;
    for (int i = 1; i < 1000111; i++) {
        p[i] = p[i-1] * 311;
    }

    int n; std::cin >> n;
    std::vector< std::pair<std::string, int> > a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i].first;
        a[i].second = i;

        std::vector<long long> h(a[i].first.size());
        for (int j = 0; j < (int) a[i].first.size(); j++) {
            h[j] = p[j] * a[i].first[j];
            if (j > 0) h[j] += h[j-1];
        }

        allHashes.insert(h.back());
    }
    // sort by decreasing length
    std::sort(a.begin(), a.end(), [] (const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                if (a.first.length() != b.first.length()) {
                    return a.first.length() > b.first.length();
                }
                return a.second < b.second;
            });

    // find ans
    std::vector<int> res(n);
    for (int i = 0; i < (int) a.size(); i++) {
        const auto& [s, id] = a[i];

        std::vector<long long> h(s.size());
        for (int j = 0; j < (int) s.size(); j++) {
            h[j] = p[j] * s[j];
            if (j > 0) h[j] += h[j-1];
        }

        res[id] = f(s, h);
    }

    for (int r : res) std::cout << r << '\n';
    return 0;
}
