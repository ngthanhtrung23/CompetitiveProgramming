
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int c[2][5011];
int f[5011];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("twothree.in", "r", stdin);
    freopen("twothree.out", "w", stdout);
    int n, r;
    while (cin >> n >> r) {
        memset(f, 0, sizeof f);
        memset(c, 0, sizeof c);
        f[1] = 1;
        c[1][0] = 1;
        c[1][1] = 1;

        FOR(i,1,n-1) {
            FOR(two,0,i) {
                int three = i - two;
                int x = two * 2 + three * 3;
                if (x > n) continue;

                f[x] = (f[x] + f[i] * c[i % 2][two]) % r;
            }

            int t = 1 - i % 2;
            FOR(x,0,i+1) {
                if (x == 0) c[t][x] = 1;
                else c[t][x] = (c[1-t][x] + c[1-t][x-1]) % r;
            }
        }
        cout << f[n] << endl;
    }
}
