#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 10111;

int n, k, m;
vector< pair<int, pair<int,int> > > ke[MN];
int d[MN];

bool check(int val) {
    memset(d, -1, sizeof d);
    queue<int> q; q.push(n);
    d[n] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for(auto cur : ke[u]) {
            if (cur.second.second < val || d[cur.first] >= 0) continue;
            d[cur.first] = 1;
            q.push(cur.first);
        }
    }
    FOR(i,1,k) if (d[i] > 0) return true;
    return false;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n >> k >> m;
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v, d, nr; cin >> u >> v >> d >> nr;
            ke[u].push_back(make_pair(v, make_pair(d, nr)));
            ke[v].push_back(make_pair(u, make_pair(d, nr)));
        }
        cout << "Case #" << test << ": ";
        if (!check(0)) {
            cout << 0 << endl;
            continue;
        }
        int l = 0, r = 1000111, res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }

        set< pair<int,int> > s;
        s.insert(make_pair(0, n));
        FOR(i,1,n) d[i] = 1000111000;
        d[n] = 0;
        while (!s.empty()) {
            int u = s.begin()->second, l = s.begin()->first;
            s.erase(s.begin());
            if (d[u] != l) continue;

            for(auto cur : ke[u]) {
                if (cur.second.second < res) continue;
                int v = cur.first;
                if (d[v] > d[u] + cur.second.first) {
                    d[v] = d[u] + cur.second.first;
                    s.insert(make_pair(d[v], v));
                }
            }
        }
        int x = *min_element(d+1, d+k+1);
        FOR(i,1,k) if (d[i] == x) cout << i << ' '; cout << endl;
    }
    return 0;
}
