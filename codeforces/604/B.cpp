
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;

int n, k, s[MN];

bool check(int each) {
    multiset<int> all;
    FOR(i,1,n) all.insert(s[i]);

    REP(turn,k) {
        if (all.empty()) break;

        // Grab the largest
        auto it = all.end(); --it;
        int ln = *it; all.erase(it);
        if (ln > each) return false;

        if (all.empty()) break;

        it = all.upper_bound(each - ln);
        if (it == all.begin()) continue;

        --it;
        all.erase(it);
    }
    return all.empty();
}

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) scanf("%d", &s[i]);
        int l = 1, r = 2000111;
        int res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        cout << res << endl;
    }
}
