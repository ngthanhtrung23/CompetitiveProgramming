
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

int n, a[100111];
int visited[100111];

void solve() {
    FOR(i,1,n) if (a[i] == i) {
        cout << "YES\n";

        FOR(j,1,n) if (j != i) cout << i << ' ' << j << '\n';
        return ;
    }

    FOR(t,1,n) if (a[a[t]] == t) {
        int u = t, v = a[t];

        memset(visited, 0, sizeof visited);
        visited[u] = visited[v] = 1;

        vector< pair<int,int> > res;
        res.push_back(make_pair(u, v));

        FOR(i,1,n) if (!visited[i]) {
            int x = i;
            int cnt = 0;
            while (!visited[x]) {
                ++cnt;

                if (cnt & 1) res.push_back(make_pair(u, x));
                else res.push_back(make_pair(v, x));

                visited[x] = true;
                x = a[x];
            }

            if (cnt % 2 == 1) {
                cout << "NO\n";
                return ;
            }
        }

        cout << "YES\n";
        for(auto p : res) cout << p.first << ' ' << p.second << '\n';
        return ;
    }
    cout << "NO\n";
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        solve();
    }
}

