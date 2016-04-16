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

const int MN = 100111;
vector< pair<int,int> > a[MN];
int x[MN];

#undef int
int main() {
#define int long long
    freopen("cards.in", "r", stdin);
    freopen("cards.out", "w", stdout);

    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int nStack;
    while (GI(nStack) == 1) {
        FOR(i,1,nStack) {
            a[i].clear();
            int n; GI(n);
            FOR(j,1,n) GI(x[j]);
            FOR(j,1,n) x[j] += x[j-1];

//            DEBUG(i);
//            PR(x, n);

            int l = 1;
            while (l <= n) {
                int r = l;
                int minVal = x[r] - x[l-1];
                while (r < n && x[r] - x[l-1] < 0) {
                    ++r;
                    minVal = min(minVal, x[r] - x[l-1]);
                }

                a[i].emplace_back(minVal, x[r] - x[l-1]);
                l = r + 1;
            }
//            for(auto p : a[i]) cout << p.first << ' ' << p.second << "    "; cout << endl;
        }

        set< pair<int, pair<int,int> > > all;
        FOR(i,1,nStack) {
            all.insert(make_pair(-a[i].begin()->first, make_pair(i, 0)));
        }

        int res = 0, cur = 0;
        while (!all.empty()) {
            auto p = *all.begin();
            all.erase(all.begin());

            if (cur >= p.first) {
                int i = p.second.first;
                int j = p.second.second;

                cur += a[i][j].second;
                res = max(res, cur);

                if (j+1 < SZ(a[i])) {
                    ++j;
                    if (a[i][j].second >= 0) {
                        all.insert(make_pair(-a[i][j].first, make_pair(i, j)));
                    }
                }
            }
            else break;
        }
        cout << res << endl;
    }
}
