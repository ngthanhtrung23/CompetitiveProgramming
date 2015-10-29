
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int n, m;
const int MN = 150111;

struct SuffixArray {
    string a;
    int N, m;
    vector<int> SA, LCP, x, y, w, c;

    SuffixArray(string _a, int m) : a(" " + _a), N(a.length()), m(m),
            SA(N), LCP(N), x(N), y(N), w(max(m, N)), c(N) {
        a[0] = 0;
        DA();
        kasaiLCP();
        #define REF(X) { rotate(X.begin(), X.begin()+1, X.end()); X.pop_back(); }
        REF(SA); REF(LCP);
        a = a.substr(1, a.size());
        for(int i = 0; i < (int) SA.size(); ++i) --SA[i];
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

int st[MN], top;
ll l[MN], r[MN];
int a[MN];

int main() {
    ios :: sync_with_stdio(false);
    freopen("refrain.in", "r", stdin);
    freopen("refrain.out", "w", stdout);
    while (cin >> n >> m) {
        string s = "";
        FOR(i,1,n) {
            cin >> a[i];
            s += (char) (a[i] - 1 + 'a');
        }
//        DEBUG(s);
        SuffixArray SA(s, 256);
//        PR0(SA.LCP, SZ(SA.LCP));

        --n;
        top = 0; st[0] = 0;
        FOR(i,1,n) {
            while (top && SA.LCP[ st[top] ] >= SA.LCP[i]) --top;
            l[i] = st[top] + 1;
            st[++top] = i;
        }
        top = 0; st[0] = n + 1;
        FORD(i,n,1) {
            while (top && SA.LCP[ st[top] ] >= SA.LCP[i]) --top;
            r[i] = st[top] - 1;
            st[++top] = i;
        }
        ll best = n+1, len = n+1, start = 1;
        FOR(i,1,n) {
            ll cur = SA.LCP[i] * (ll) (r[i] - l[i] + 2);
            if (cur > best) {
                best = cur;
                len = SA.LCP[i];
                start = SA.SA[i] + 1;
            }
        }
        cout << best << endl;
        cout << len << endl;
//        DEBUG(start);
        FOR(i,start,start+len-1) cout << a[i] << ' '; cout << endl;
    }
}

