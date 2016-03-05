
#include <bits/stdc++.h>
#define int long long
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

const int MN = 1011;
int a[MN], n;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        multiset<int> all;
        FOR(i,1,n) {
            cin >> a[i];
            all.insert(a[i]);
        }
        int res = 0;
        set< pair<int,int> > cached;
        FOR(i,1,n) FOR(j,1,n) if (i != j) {
            if (cached.count(make_pair(a[i], a[j]))) continue;
            cached.insert(make_pair(a[i], a[j]));

            // sequence starts at i and j
            vector<int> cur;
            all.erase(all.find(a[i])); cur.push_back(a[i]);
            all.erase(all.find(a[j])); cur.push_back(a[j]);

            while (true) {
                int need = cur[SZ(cur) - 2] + cur[SZ(cur) - 1];
                if (all.find(need) != all.end()) {
                    all.erase(all.find(need));
                    cur.push_back(need);
                }
                else break;
            }
            res = max(res, SZ(cur));

            for(int x : cur) all.insert(x);
        }
        cout << res << endl;
    }
}
