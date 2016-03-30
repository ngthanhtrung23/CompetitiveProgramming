
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

vector< pair<int,string> > ls[10111];

char a[111];
int id, score;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, m;
    while (scanf("%lld%lld\n", &n, &m) == 2) {
        FOR(i,1,m) ls[i].clear();
        FOR(i,1,n) {
            scanf("%s%lld%lld\n", &a[0], &id, &score);
            ls[id].push_back(make_pair(-score, string(a)));
        }
        FOR(i,1,m) {
            sort(ls[i].begin(), ls[i].end());
            if (SZ(ls[i]) > 2 && ls[i][2].first == ls[i][1].first) puts("?");
            else {
                printf("%s %s\n", ls[i][0].second.c_str(), ls[i][1].second.c_str());
            }
        }
    }
}
