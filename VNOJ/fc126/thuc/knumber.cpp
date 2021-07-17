#include <bits/stdc++.h>

using namespace std;
const int maxn = 1005;
int a[maxn];
int cnt[maxn];
bool mark[maxn];
vector<int> adj[maxn];
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        adj[i].push_back(0);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        adj[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        adj[i].push_back(n + 1);
    }
    auto check = [&](int x, int k) {
        for (int i = 0; i + 1 < (int) adj[x].size(); ++i)
            if (adj[x][i + 1] - adj[x][i] > k)
                return false;
        return true;
    };
    for (int k = 1; k <= n; ++k) {
        int found = -1;
        for (int i = 1; i <= n; ++i)
            if (check(i, k)) {
                found = i;
                break;
            }
        cout << found << ' ';
    }
    cout << '\n';
}
int main() {
#ifdef LDT
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

