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
int a[MN], b[MN], n;

bool canWin(int a[], int b[]) {
    // can a wins?
    multiset<int> all;
    FOR(i,1,n) all.insert(a[i]);

    int res = 0;
    FOR(i,1,n) {
        auto it = all.upper_bound(b[i]);
        if (it == all.end()) {
            all.erase(all.begin());
        }
        else {
            ++res;
            all.erase(it);
        }
    }
    return res > n-res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) GI(a[i]);
        FOR(i,1,n) GI(b[i]);

        int ta = canWin(a, b);
        int tb = canWin(b, a);

        if (ta && tb) cout << "Both" << endl;
        else if (ta && !tb) cout << "First" << endl;
        else if (!ta && tb) cout << "Second" << endl;
        else cout << "None" << endl;
    }
}
