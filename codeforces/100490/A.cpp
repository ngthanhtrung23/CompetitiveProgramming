
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

const int MN = 200111;
int n, a[MN], s[MN], color[MN];
pair<int,int> st[MN];
int top;

bool bad() {
    int u = st[top].first, v = st[top].second;
    int x = st[top-1].first, y = st[top-1].second;

    return (s[v] - s[u - 1]) * (y - x + 1LL) < (s[y] - s[x - 1]) * (v - u + 1LL);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("approximation.in", "r", stdin);
    freopen("approximation.out", "w", stdout);
    while (scanf("%lld", &n) == 1) {
        FOR(i,1,n) scanf("%lld", &a[i]);
        FOR(i,1,n) s[i] = s[i-1] + a[i];

        top = 0;
        FOR(i,1,n) {
            st[++top] = make_pair(i, i);
            while (bad()) {
                --top;
                st[top].second = i;
            }
        }
        FOR(i,1,top) {
            int l = st[i].first, r = st[i].second;
            FOR(x,l,r) printf("%.9lf ", (s[r] - s[l-1]) / (double) (r - l + 1));
        }
        puts("");
    }
}
