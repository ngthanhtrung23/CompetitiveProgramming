
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

#define next next__
#define right right__
#define left left__

const int MN = 6011;
string s;
int n;
ll p31[MN], h[MN];
set<ll> right[MN], left[MN];

ll getHash(int i, int j) {
    return (h[j+1] - h[i]) * p31[n-i];
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(0);
    freopen("dna.in", "r", stdin);
    freopen("dna.out", "w", stdout);

    p31[0] = 1; FOR(i,1,MN-1) p31[i] = p31[i-1] * 31LL;

    while (cin >> s) {
        n = s.length();

        FOR(i,1,n) {
            h[i] = h[i-1] + s[i-1] * p31[i];
        }

        int ln = 0;

        // right branching
        SuffixArray SA1(s, 300);

        REP(i,SZ(SA1.SA)-1) {
            int start = SA1.SA[i];
            int len = SA1.LCP[i+1];
            if (len > 0) {
                right[len].insert(getHash(start, start+len-1));
            }
        }
        // left branching
        string t = s;
        reverse(t.begin(), t.end());
        SuffixArray SA2(t, 300);
        REP(i,SZ(SA2.SA)-1) {
            int start = SA2.SA[i];
            int len = SA2.LCP[i+1];
            if (len > 0) {
                int fr = n - (start + len - 1) - 1;
                int to = n - start - 1;

                ll cur = getHash(fr, to);
                if (right[len].count(cur)) {
                    left[len].insert(cur);
                    if (len > ln) ln = len;
                }
            }
        }

        int sum = 0;
        FOR(i,1,ln) sum += SZ(left[i]);
        cout << sum << endl << ln << endl << SZ(left[ln]) << endl;
    }
}
