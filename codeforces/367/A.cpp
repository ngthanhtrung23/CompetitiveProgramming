
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;

string s;
int cnt[3][MN];
int a[MN];

bool eq(int x, int y, int z) {
    return x == y && y == z;
}

bool good(int x, int y, int z) {
    return eq(x, y, z)
        || eq(x-1, y, z)
        || eq(x, y-1, z)
        || eq(x, y, z-1)
        || eq(x+1, y, z)
        || eq(x, y+1, z)
        || eq(x, y, z+1)
        ;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> s) {
        int n = s.length();
        FOR(i,1,n) {
            a[i] = s[i-1] - 'x';
        }

        REP(t,3) {
            cnt[t][0] = 0;
            FOR(i,1,n) {
                cnt[t][i] = cnt[t][i-1];
                if (a[i] == t) ++cnt[t][i];
            }
        }

        int q; cin >> q;
        while (q--) {
            int l, r; cin >> l >> r;
            if (r - l + 1 < 3) {
                cout << "YES\n";
                continue;
            }
            int x = cnt[0][r] - cnt[0][l-1];
            int y = cnt[1][r] - cnt[1][l-1];
            int z = cnt[2][r] - cnt[2][l-1];

            cout << (good(x, y, z) ? "YES" : "NO") << '\n';
        }
    }
}
