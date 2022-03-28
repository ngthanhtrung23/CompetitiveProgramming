#include "bits/stdc++.h"
using namespace std;

#define int long long

const int MC = 'z' - 'a' + 1;
const int MOD = static_cast<int> (1e9 + 7);
struct Str {
    char first, last;
    int cnt[MC];  // exclude first and last
    int sz;

    Str(const std::string& s) {
        sz = s.size();
        first = *s.begin();
        last = *prev(s.end());

        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i < -1 + (int) s.size(); i++) {
            cnt[s[i] - 'a']++;
        }
    }

    void append(char c) {
        if (sz > 1) cnt[last - 'a']++;
        last = c;
        ++sz;
    }

    void prepend(char c) {
        if (sz > 1) cnt[first - 'a']++;
        first = c;
        ++sz;
    }

    void concat(const Str& other) {
        if (sz > 1) cnt[last - 'a']++;
        if (other.sz > 1) cnt[other.first - 'a']++;

        for (int i = 0; i < MC; i++) {
            cnt[i] += other.cnt[i];
        }
        sz += other.sz;
        last = other.last;
    }

    void reverse() {
        std::swap(first, last);
    }
};
std::ostream& operator << (std::ostream& out, const Str& s) {
    out << s.first << ".[";
    for (char c = 'a'; c <= 'z'; c++) {
        if (s.cnt[c - 'a'] > 0) {
            out << c << ": " << s.cnt[c - 'a'] << ", ";
        }
    }
    out << "]." << s.last;
    return out;
}

// prefix(a) + suffix(b)
int count(const Str& a, const Str& b) {
    int res = a.sz * b.sz;
    for (int i = 0; i < MC; i++) {
        int ca = a.cnt[i];
        if (a.sz > 1 && a.last - 'a' == i) ++ca;

        int cb = b.cnt[i];
        if (b.sz > 1 && b.first - 'a' == i) ++cb;

        res -= ca * cb;
    }
    return res % MOD;
}

int32_t main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    std::vector<Str> f;
    std::string s; std::cin >> s;
    f.push_back(Str(s));

    int q; std::cin >> q;
    for (int i = 1; i <= q; i++) {
        int typ; std::cin >> typ;
        if (typ == 1) {
            int u; char c;
            std::cin >> u >> c;
            f.push_back(f[u]);
            f.back().append(c);
        } else if (typ == 2) {
            int u; char c;
            std::cin >> u >> c;
            f.push_back(f[u]);
            f.back().prepend(c);
        } else if (typ == 3) {
            int u, v;
            std::cin >> u >> v;
            f.push_back(f[u]);
            f.back().concat(f[v]);
        } else if (typ == 4) {
            int u; std::cin >> u;
            f.push_back(f[u]);
            f.back().reverse();
        } else if (typ == 5) {
            f.push_back(f.back());
            int u, v; std::cin >> u >> v;
            std::cout << count(f[u], f[v]) << '\n';
        } else {
            std::cout << ":@)" << std::endl;
            assert(false);
        }
    }
    return 0;
}
