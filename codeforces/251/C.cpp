
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

const int MN = 500111;

ll a, b;
int k;
ll dist[MN];

ll lcm(ll a, ll b) {
    return a * b / __gcd(a, b);
}

void dijkstra(int lcm, int start) {
    set< pair<ll, int> > s;
    REP(i,lcm) dist[i] = 1000111000111000111LL;
    dist[start] = 0;
    s.insert(make_pair(0, start));

    while (!s.empty()) {
        ll l = s.begin()->first;
        int u = s.begin()->second;
        s.erase(s.begin());

        if (dist[u] != l) continue;

        FOR(i,1,k) {
            int v = (i == 1) ? (u-1) : u - u % i;
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                s.insert(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> a >> b >> k) {
        ll x = 2;
        FOR(i,2,k) x = lcm(x, i);

        ll ka = a / x, ua = a % x;
        ll kb = b / x, ub = b % x;

        if (ka == kb) {
            dijkstra(x, ua);
            cout << dist[ub] << endl;
        }
        else {
            dijkstra(x, ua);
            ll res = dist[0];

            ll turn = ka - kb - 1;
            dijkstra(x, x-1);
            ll each = dist[0] + 1;

            res += each * turn;
            
            res += 1 + dist[ub];

            cout << res << endl;
        }
    }
    return 0;
}
