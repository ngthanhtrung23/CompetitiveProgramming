#include <bits/stdc++.h>

using namespace std;
const int maxn = 2e5 + 5;
int L[maxn], R[maxn];
int n;
int m;
int f[maxn][1 << 8];
vector<tuple<int, int, int> > endpoints;
#define OPEN 1
#define CLOSE 0
int get_mask(const map<int, bool> &intervals) {
    int mask = 0;
    for (auto x : intervals) {
        mask <<= 1;
        mask |= x.second;
    }
    return mask;
}
int calc(int i, map<int, bool> &intervals) {
    if (i >= m - 1)
        return 0;
    int mask = get_mask(intervals);
    bool parity = __builtin_parity(mask);
    int &res = f[i][mask];
    if (res != -1) return res;
    res = 0;
    auto [val, typ, id] = endpoints[i];
    if (typ == CLOSE) {
        bool save = 0;
        if (intervals[id])
            parity ^= 1, save = 1;
        intervals.erase(id);
        res = calc(i + 1, intervals) + parity * (get<0>(endpoints[i + 1]) - val); 
        intervals[id] = save;
        return res;
    }
    //OPEN
    //chon
    intervals[id] = 1;
    parity ^= 1;
    res = calc(i + 1, intervals) + parity * (get<0>(endpoints[i + 1]) - val);
    parity ^= 1;
    //
    intervals[id] = 0;
    res = max(res, calc(i + 1, intervals) + parity * (get<0>(endpoints[i + 1]) - val));
    intervals.erase(id);
    return res;
}
int main() {
#ifdef LDT
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    
    for (int i = 1; i <= n; ++i) {
        cin >> L[i] >> R[i];
        ++R[i];
    }
    for (int i = 1; i <= n; ++i) {
        endpoints.push_back({L[i], OPEN, i});
    }
    for (int i = 1; i <= n; ++i) {
        endpoints.push_back({R[i], CLOSE, i});
    }
    sort(endpoints.begin(), endpoints.end());
    m = endpoints.size();
    memset(f, 255, sizeof(f));
    map<int, bool> dummy;
    cout << calc(0, dummy) << '\n';
    return 0;
}

