
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

const int MN=100111;

bool can[11][11];
int a[MN], b[MN];
int cnt[2][11];

int main() {
    ios :: sync_with_stdio(false);
    freopen("traces.in", "r", stdin);
    freopen("traces.out", "w", stdout);
    int d, k;
    while (cin >> d >> k) {
        memset(can, false, sizeof can);
        FOR(i,1,k) {
            char x, y; cin >> x >> y;
            x -= 'a'; y -= 'a';
            can[x][y] = can[y][x] = true;
        }
        memset(cnt, 0, sizeof cnt);

        string s; cin >> s;
        int n = SZ(s); FOR(i,1,n) a[i] = s[i-1] - 'a';
        cin >> s;

        if (SZ(s) != n) {
            cout << "NO" << endl;
            continue;
        }
        FOR(i,1,n) b[i] = s[i-1] - 'a';

//        PR(a, n);
//        PR(b, n);

        try {
            FOR(c,0,d-1) {
                int ia = 1, ib = 1;
                while (ia <= n || ib <= n) {
                    while (ia <= n && a[ia] != c) {
                        ++cnt[0][a[ia]];
                        ++ia;
                    }
                    while (ib <= n && b[ib] != c) {
                        ++cnt[1][b[ib]];
                        ++ib;
                    }

                    if (ia > n && ib > n) break;

                    if (ia > n) throw 1;
                    if (ib > n) throw 1;

                    REP(x,d)
                        if (x != c && !can[x][c]) {
                            if (cnt[0][x] != cnt[1][x]) throw 1;
                        }

                    ++ia;
                    ++ib;
                }
            }
            cout << "YES" << endl;
        }
        catch (...) {
            cout << "NO" << endl;
        }
    }
}

