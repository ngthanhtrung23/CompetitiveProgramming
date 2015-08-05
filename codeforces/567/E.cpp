
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

const int MN = 100111;
const ll MOD = 1e9 + 37;
int n, m, s, t;
vector< pair<int,int> > ke[2][MN];
ll f[2][MN];

struct Hash {
    ll x, y;
    Hash(ll x = 0, ll y = 0) : x(x), y(y) {}

    Hash operator + (const Hash& a) const {
        return Hash(x + a.x, (y + a.y) % MOD);
    }
    Hash operator * (const Hash& a) const {
        return Hash(x * a.x, y * a.y % MOD);
    }
};

bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x && a.y == b.y;
}

Hash cnt[2][MN];

void go(int start, int turn) {
    set< pair<ll, int> > q;
    FOR(i,1,n) {
        f[turn][i] = 1e16;
    }

    f[turn][start] = 0;
    cnt[turn][start] = Hash(1, 1);
    q.insert(make_pair(0, start));

    while (!q.empty()) {
        int u = q.begin()->second;
        ll l = q.begin()->first;
        q.erase(q.begin());

        if (l != f[turn][u]) continue;

        for(auto e : ke[turn][u]) {
            int v = e.first, c = e.second;

            if (f[turn][v] > f[turn][u] + c) {
                f[turn][v] = f[turn][u] + c;
                cnt[turn][v] = cnt[turn][u];
                q.insert(make_pair(f[turn][v], v));
            }
            else if (f[turn][v] == f[turn][u] + c) {
                cnt[turn][v] = cnt[turn][v] + cnt[turn][u];
            }
        }
    }
}

int eu[MN], ev[MN], ec[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> s >> t) {
        FOR(i,1,n) {
            ke[0][i].clear();
            ke[1][i].clear();
        }
        FOR(i,1,m) {
            int u, v, c; cin >> u >> v >> c;
            ke[0][u].push_back(make_pair(v, c));
            ke[1][v].push_back(make_pair(u, c));

            eu[i] = u;
            ev[i] = v;
            ec[i] = c;
        }
        go(s, 0);
//        PR(f[0], 100);
        go(t, 1);
//        PR(f[1], 100);

//        cerr << cnt[0][t].x << ' ' << cnt[0][t].y << endl;

        FOR(i,1,m) {
            int u = eu[i], v = ev[i], c = ec[i];
            if (f[0][u] + c + f[1][v] == f[0][t]) {
                // this edge is already on shortest path
                if (cnt[0][u] * cnt[1][v] == cnt[0][t]) {
                    cout << "YES\n";
                    continue;
                }
                else {
                    if (c > 1) cout << "CAN 1\n";
                    else cout << "NO\n";
                }
            }
            else {
                ll need = f[0][t] - f[0][u] - f[1][v] - 1;
                if (need < 1) cout << "NO\n";
                else cout << "CAN " << (c - need) << '\n';
            }
        }
        cout << endl;
    }
}

