
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

const int MN = 111;

int a[MN], n, g[MN][MN], c[MN];

struct Block {
    int f[MN][MN];

    void cal1() {
        memset(f, 0, sizeof f);
        FOR(from,1,100) {
            FOR(to,from,100) f[from][to] = 0;

            memset(g, 0, sizeof g);
            FOR(i,1,n) {
                FOR(to,from,100)
                    g[i][to] = g[i-1][to];

                if (a[i] >= from) {
                    g[i][a[i]] = max(g[i][a[i]], 1);
                    FOR(prev,from,a[i])
                        g[i][a[i]] = max(g[i][a[i]], g[i-1][prev] + 1);
                }
            }

            FOR(to,from,100) f[from][to] = g[n][to];
        }
    }

    void print() {
        FOR(from,1,4) {
            FOR(to,1,4) cout << f[from][to] << ' ';
            cout << endl;
        }
        cout << "----" << endl;
    }
} f[30], trans;

Block operator + (const Block& a, const Block& b) {
    Block res;
    memset(res.f, 0, sizeof res.f);

    FOR(from,1,100) {
        FOR(to,1,100) {
            res.f[from][to] = a.f[from][to];
            
            FOR(mid,from,to)
                res.f[from][to] = max(res.f[from][to],
                        a.f[from][mid] + b.f[mid][to]);
        }
    }
    return res;
}

void RR() {
    FOR(i,1,n) c[i] = a[i];
    sort(c+1, c+n+1);
    int sc = unique(c+1, c+n+1) - c - 1;

    FOR(i,1,n) a[i] = lower_bound(c+1, c+n+1, a[i]) - c;
}

int main() {
    ios :: sync_with_stdio(false);
    int T;
    while (cin >> n >> T) {
        FOR(i,1,n) cin >> a[i];
        RR();
//        PR(a, n);

        f[0].cal1();

        FOR(i,1,23) f[i] = f[i-1] + f[i-1];

//        f[0].print();
//        f[1].print();
//        f[2].print();

        bool first = true;
        REP(bit,24)
            if ((T >> bit) & 1) {
                if (first) {
                    first = false;
                    trans = f[bit];
                }
                else trans = trans + f[bit];
            }

        int res = 0;
        FOR(from,1,100) FOR(to,from,100) {
            res = max(res, trans.f[from][to]);
            if (res == 8) {
                cout << from << ' ' << to << endl;
                assert(0);
            }
        }
        cout << res << endl;
    }
}
