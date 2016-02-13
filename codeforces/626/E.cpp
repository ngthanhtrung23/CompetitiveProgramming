
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
#define double long double
using namespace std;

const int MN = 200111;
ll x[MN], sum[MN];
int n;
double best;
vector< pair<int,int> > res;

double f(int k, int med) {
    return (sum[n] - sum[n-k] + sum[med] - sum[med-k-1]) / (double) (2*k+1) - x[med];
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            int a; scanf("%d", &a);
            x[i] = a;
        }
        sort(x+1, x+n+1);
        FOR(i,1,n) sum[i] = sum[i-1] + x[i];

        best = 0.0;
        res.clear(); res.push_back(make_pair(1, 1));

        // odd
        FOR(x,1,n) {
            int l = 1, r = min(n - x, x - 1);
            while (l + 10 < r) {
                int mid = (l + r) >> 1;
                if (f(mid, x) > f(mid+1, x)) {
                    r = mid;
                }
                else l = mid + 1;
            }
            FOR(i,l,r) {
                double cur = f(i, x);
                if (cur > best) {
                    best = cur;
                    res.clear();
                    res.push_back(make_pair(x - i, x));
                    res.push_back(make_pair(n - i + 1, n));
                }
            }
        }

        int cnt = 0;
        for(auto p : res) cnt += p.second - p.first + 1;
        printf("%d\n", cnt);

        for(auto p : res) {
            FOR(i,p.first,p.second) {
                printf("%d ", (int) x[i]);
            }
        }
        puts("");
    }
}
