#include <bits/stdc++.h>

using namespace std;
const int maxn = 2005;
const int MOD = 1e9 + 7;
int n;
vector<pair<int, int> > b;
int c[maxn];
int T[maxn], d[maxn], d2[maxn];
void update(int x, int val) {
    for (; x < maxn - 1; x += x & -x)
        (T[x] += val) %= MOD;
}
int get_sum(int x) {
    long long res = 0;
    for (; x; x -= x & -x)
        res += T[x];
    return res % MOD;
}
int main() {
#ifdef LDT
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //x1 > x2 && y1 < y2
    //d[i][l]:
    //= sum (  d[j][l - 1]  )
    cin >> n;
    vector<int> Y;
    b.resize(n);
    for (auto &[x, y]: b)
        cin >> x;
    for (auto &[x, y]: b) {
        cin >> y;
        Y.push_back(y);
    }
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());

    sort(b.begin(), b.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first > b.first ||
            (a.first == b.first && a.second > b.second);
    });

    for (auto &[x, y] : b) {
        y = lower_bound(Y.begin(), Y.end(), y) - Y.begin() + 2;
        // cout << y << ' ';
    }
    // cout << '\n';
    for (int i = 1; i <= n; ++i)
        c[i] = b[i - 1].second;
    c[0] = 1;
    d2[0] = 1;
    for (int l = 1; l <= n; ++l) {
        // cout << "\n";
        memset(T, 0, sizeof(T));
        for (int i = 1; i <= n; ++i) {
            update(c[i - 1], d2[i - 1]);
            d[i] = get_sum(c[i] - 1);
            // cout << d[i] << ' ';
        }
        for (int i = 0; i <= n; ++i)
            d2[i] = d[i];
        cout << accumulate(d + 1, d + 1 + n, 0ll) % MOD << ' ';
    }
    return 0;
}

