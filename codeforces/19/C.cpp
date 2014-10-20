#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

struct SuffixArray {
    vector<int> a;
    int N, m;
    vector<int> SA, LCP, x, y, w, c;

    SuffixArray(vector<int> _a, int m) : a(_a),N(a.size() + 1), m(m),
            SA(N), LCP(N), x(N), y(N), w(max(m, N)), c(N) {
        a.insert(a.begin(), 0);
        DA();
        kasaiLCP();
        #define REF(X) { rotate(X.begin(), X.begin()+1, X.end()); X.pop_back(); }
        REF(SA); REF(LCP);
        a.erase(a.begin());
        for(int i = 0; i < SA.size(); ++i) --SA[i];
        #undef REF
    }

    inline bool cmp (const int a, const int b, const int l) { return (y[a] == y[b] && y[a + l] == y[b + l]); }

    void Sort() {
        for(int i = 0; i < m; ++i) w[i] = 0;
        for(int i = 0; i < N; ++i) ++w[x[y[i]]];
        for(int i = 0; i < m - 1; ++i) w[i + 1] += w[i];
        for(int i = N - 1; i >= 0; --i) SA[--w[x[y[i]]]] = y[i];
    }

    void DA() {
        for(int i = 0; i < N; ++i) x[i] = a[i], y[i] = i;
        Sort();
        for(int i, j = 1, p = 1; p < N; j <<= 1, m = p) {
            for(p = 0, i = N - j; i < N; i++) y[p++] = i;
            for (int k = 0; k < N; ++k) if (SA[k] >= j) y[p++] = SA[k] - j;
            Sort();
            for(swap(x, y), p = 1, x[SA[0]] = 0, i = 1; i < N; ++i)
                x[SA[i]] = cmp(SA[i - 1], SA[i], j) ? p - 1 : p++;
        }
    }

    void kasaiLCP() {
        for (int i = 0; i < N; i++) c[SA[i]] = i;
        for (int i = 0, j, k = 0; i < N; LCP[c[i++]] = k)
            if (c[i] > 0) for (k ? k-- : 0, j = SA[c[i] - 1]; a[i + k] == a[j + k]; k++);
            else k = 0;
    }
};

const int MN = 100111;
vector<int> a;
int n, c[MN];
vector<int> ls[MN];

int lg[MN];
int rmq[22][MN];

void RR() {
    REP(i,n) c[i] = a[i];
    sort(c, c+n);
    int s = unique(c, c+n) - c;
    REP(i,n) a[i] = lower_bound(c, c+s, a[i]) - c + 1;

    // PR0(a, n);

    FOR(i,0,100000) ls[i].clear();
    REP(i,n) ls[a[i]].push_back(i);
}

void init() {
    lg[0] = 0;
    for(int i = 1, t = 0; i < MN; i *= 2, ++t)
        lg[i] = t;
    FOR(i,2,100000)
        if (!lg[i]) lg[i] = lg[i-1];
}

#define TWO(X) (1<<(X))

int id[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        a.resize(n);
        REP(i,n) cin >> a[i];
        RR();
        init();

        SuffixArray sa(a, n);

        REP(i,n) rmq[0][i] = sa.LCP[i];
        FOR(t,1,18)
            REP(i,n-TWO(t))
                rmq[t][i] = min(rmq[t-1][i], rmq[t-1][i+TWO(t-1)]);

        // PR0(sa.SA, n);
        // PR0(sa.LCP, n);

        REP(i,n)
            id[sa.SA[i]] = i;

        vector< pair<int,int> > res;
        REP(u,n) {
            REP(i,ls[a[u]].size()) {
                int v = ls[a[u]][i];
                if (v <= u) continue;

                int id_u = id[u], id_v = id[v];
                if (id_u > id_v) swap(id_u, id_v);
                ++id_u;
                int len = id_v - id_u + 1;
                int t = lg[len];

                int nn = min(rmq[t][id_u], rmq[t][id_v - TWO(t) + 1]);

                if (nn >= v - u) {
                    res.push_back(make_pair(u, v));
                }
            }
        }
        int start = 0;
        REP(i,res.size()) {
            // cout << res[i].first << ' ' << res[i].second << endl;
            if (res[i].first >= start)
                start = res[i].second;
        }
        cout << a.size() - start << endl;
        FOR(i,start,a.size()-1)
            cout << c[a[i]-1] << ' ';
        cout << endl;
    }
    return 0;
}
