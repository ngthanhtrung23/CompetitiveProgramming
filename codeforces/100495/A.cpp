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

#define TWO(X) (1<<(X))

int read() {
    int s; cin >> s;
    int res = 0;
    while (s--) {
        int u; cin >> u;
        res |= TWO(u);
    }
    return res;
}

long long oo = 1000111000111000LL;
long long d[TWO(13)];
vector< pair<int,int> > ke[TWO(13)];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n, m; cin >> n >> m;
        int start = read();
        int target = read();
        REP(i,TWO(n)) ke[i].clear();

        FOR(i,1,m) {
            int c; cin >> c;
            int u = read();
            int v = read();
            ke[u].push_back(make_pair(v, c));
        }
        REP(i,TWO(n)) d[i] = oo;
        d[start] = 0LL;
        set< pair<long long, int> > s;
        s.insert(make_pair(0, start));
        while (!s.empty()) {
            int u = s.begin()->second;
            long long l = s.begin()->first;
            s.erase(s.begin());
            if (d[u] != l) continue;

            for(int x = u; x > 0; x = ((x - 1) & u)) {
                for(auto e : ke[x]) {
                    int v = (u - x) | e.first, c = e.second;
                    if (d[v] > d[u] + c) {
                        d[v] = d[u] + c;
                        s.insert(make_pair(d[v], v));
                    }
                }
            }
        }
        cout << "Case #" << test << ": ";
        if (d[target] == oo) cout << "NO" << endl;
        else cout << "YES " << d[target] << endl;
    }
    return 0;
}
