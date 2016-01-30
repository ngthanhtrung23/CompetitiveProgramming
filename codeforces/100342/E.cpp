
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

const int MN = 30111000;
int x[MN], st[MN], first, last;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("minima.in", "r", stdin);
    freopen("minima.out", "w", stdout);
    int n, m, k;
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        FOR(i,1,k) scanf("%d", &x[i]);
        FOR(i,k+1,n) x[i] = a * x[i-2] + b * x[i-1] + c;

        ll res = 0;
        first = 1, last = 0;
        FOR(i,1,n) {
            // remove first
            while (first <= last && st[first] <= i - m) ++first;
            // remove last
            while (first <= last && x[st[last]] >= x[i]) --last;

            st[++last] = i;

            if (i >= m) {
                res += x[st[first]];
            }
        }
        cout << res << endl;
    }
}
