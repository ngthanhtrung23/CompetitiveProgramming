
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
struct City {
    int x, p, id;
} a[MN];
int n, res[MN];

bool operator < (const City& a, const City& b) {
    return a.p > b.p;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) {
            GI(a[i].x);
            GI(a[i].p);
            a[i].id = i;
        }
        sort(a+1, a+n+1);
        
        set< pair<int,int> > all;
        FOR(i,1,n) {
            if (i == 1) res[a[i].id] = -1;
            else {
                auto it = all.lower_bound(make_pair(a[i].x, 0));
                int bestDist = 1000111000;
                int bestP = -1;
                int saveId = -1;

                if (it != all.end()) {
                    int x = it->first;
                    int curDist = abs(x - a[i].x);
                    int curP = a[it->second].p;

                    if (curDist < bestDist || (curDist == bestDist && curP > bestP)) {
                        bestDist = curDist;
                        bestP = curP;
                        saveId = a[it->second].id;
                    }
                }
                if (it != all.begin()) {
                    --it;
                    int x = it->first;
                    int curDist = abs(x - a[i].x);
                    int curP = a[it->second].p;

                    if (curDist < bestDist || (curDist == bestDist && curP > bestP)) {
                        bestDist = curDist;
                        bestP = curP;
                        saveId = a[it->second].id;
                    }
                }

                res[ a[i].id ] = saveId;
            }
            all.insert(make_pair(a[i].x, i));
        }
        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
}
