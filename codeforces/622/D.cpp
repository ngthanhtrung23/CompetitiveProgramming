
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

const int MN = 1000111;
int a[MN], x[MN], y[MN];
int n;

ll get() {
    FOR(i,1,n) x[i] = y[i] = -1;

    FOR(i,1,n+n) {
        int u = a[i];
        if (x[u] < 0) x[u] = i;
        else y[u] = i;
    }
    ll res = 0;
    FOR(i,1,n) {
        res += (n - i) * (ll) llabs(y[i] - x[i] + i - n);
    }
    return res;
}

int main() {
    while (cin >> n) {
        memset(a, 0, sizeof a);

        int l = 1, r = n;
        for(int i = 1; i < n; i += 2) {
            a[l] = a[r] = i;
            ++l;
            --r;
        }
        l = n + 2; r = n + n;
        for(int i = 2; i < n; i += 2) {
            a[l] = a[r] = i;
            ++l;
            --r;
        }
        FOR(i,1,n+n) if (a[i] == 0) a[i] = n;

        assert(get() == 0LL);
        FOR(i,1,n+n) printf("%d ", a[i]);
        cout << endl;
    }
}
