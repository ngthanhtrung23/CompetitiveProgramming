
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
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

int nx, x[10111];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    int test = 0;
    while (cin >> n && n) {
        map<string,int> cnt;
        FOR(i,1,n) {
            string s; cin >> s;
            cnt[s] += 1;
        }
        cout << "Case " << ++test << ": ";

        nx = 0;
        for(auto p : cnt) {
            int u = p.second;
            FOR(i,1,nx) {
                if (u == 0) break;
                if (x[i] < 9) {
                    x[i]++;
                    u--;
                }
            }
            while (u) {
                --u;
                x[++nx] = 1;
            }
        }
        FORD(i,nx,1) cout << x[i]; cout << '\n';
    }
}
