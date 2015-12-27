
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

const int MN = 2000111;

pair<int,int> x[MN];

int main() {
    int n, k;
    while (scanf("%d%d", &n, &k) == 2) {
        int nx = 0;
        FOR(i,1,n) {
            int a, b; scanf("%d%d", &a, &b);
            x[++nx] = make_pair(a, -1);
            x[++nx] = make_pair(b, 1);
        }
        sort(x+1, x+nx+1);

        int start;
        int cur = 0;
        vector< pair<int,int> > res;
        FOR(i,1,nx) {
            if (x[i].second == -1) {
                ++cur;
                if (cur == k) start = x[i].first;
            }
            else {
                if (cur == k) {
                    res.push_back(make_pair(start, x[i].first));
                }
                --cur;
            }
        }
        printf("%d\n", SZ(res));
        for(auto p : res) {
            printf("%d %d\n", p.first, p.second);
        }
    }
}
