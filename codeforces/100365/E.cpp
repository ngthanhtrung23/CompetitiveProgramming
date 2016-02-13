
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

int a[22];
int res[20] = {
1,2,3,5,8,14,25,45,85,162,310,595,1165,2285,4485,8808,17306,34302,68009,134853
};

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("chipmunks.in", "r", stdin);
    freopen("chipmunks.out", "w", stdout);
    int n;
    while (cin >> n) {
        cout << res[n-1] << endl;
    }

    return 0;

    set< pair<int,int> > all;
    FOR(i,1,20) {
        DEBUG(i);
        if (i <= 3) {
            a[i] = i;
        }
        else {
            a[i] = a[i-1] + 1;
            while (true) {
                bool found = false;
                REP(mask,1<<(i-1)) {
                    int cnt = __builtin_popcount(mask) + 1;
                    int sum = a[i];
                    REP(b,i-1) if (mask & (1<<b)) {
                        sum += a[b+1];
                    }
                    if (all.find(make_pair(cnt, sum)) != all.end()) {
                        found = true;
                        break;
                    }
                }
                if (found) ++a[i];
                else break;
            }
        }
        DEBUG(a[i]);
        // add all sets with this bit on
        REP(mask,1<<(i-1)) {
            int cnt = __builtin_popcount(mask) + 1;
            int sum = a[i];
            REP(b,i-1) if (mask & (1<<b)) {
                sum += a[b+1];
            }
            all.insert(make_pair(cnt, sum));
        }
//        for(auto p : all) cout << p.first << ' ' << p.second << "   "; cout << endl;
    }
    FOR(i,1,20) cout << a[i] << ',';
    cout << endl;
}
