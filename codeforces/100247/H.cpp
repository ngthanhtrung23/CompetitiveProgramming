
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

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 200111;
int n, a[MN];
char s[MN], t[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        scanf("%s", &s[0]);
        scanf("%s", &t[0]);

        FOR(i,1,n) {
            a[i] = (s[i-1] - '0') ^ (t[i-1] - '0');
        }
//        PR(a, n);

        int res = 0;
        int i = 1;
        while (i <= n) {
            if (a[i] == 0) ++i;
            else {
                int j = i;
                while (j < n && a[j+1] == 1) ++j;

                i = j + 1;
                ++res;
            }
        }
        cout << res << endl;
    }
}
