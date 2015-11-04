
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 100111;
ll x[2];
pair<ll,ll> f[MN];

ll read() {
    int x; scanf("%d", &x);
    return x;
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (scanf("%d", &n) == 1) {
        x[0] = read();
        x[1] = read();

        FOR(i,1,n) {
            ll k = read();
            ll b = read();

            f[i] = make_pair(
                    k*x[0] + b,
                    k*x[1] + b
                    );
        }
        sort(f+1, f+n+1);
        bool good = true;
        FOR(i,2,n)
            if (f[i].second < f[i-1].second) good = false;
        cout << (good ? "NO" : "YES") << endl;
    }
}

