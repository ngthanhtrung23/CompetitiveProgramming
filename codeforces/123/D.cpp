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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
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
string s;
int l[MN], r[MN], st[MN], top;
int n;

inline long long f(long long x) { return x * (x + 1) / 2; }

int main() {
    while (cin >> s) {
        n = s.length();
        SuffixArray sa(s, 256);
        // PR0(sa.SA, n);
        // PR0(sa.LCP, n);
        sa.LCP.push_back(0);

        top = 0; st[0] = -1;
        REP(i,n) {
            while (top && sa.LCP[st[top]] >= sa.LCP[i]) --top;
            l[i] = st[top] + 1;
            st[++top] = i;
        }
        top = 0; st[0] = n;
        FORD(i,n-1,0) {
            while (top && sa.LCP[st[top]] >= sa.LCP[i]) --top;
            r[i] = st[top] - 1;
            st[++top] = i;
        }

        set< pair<int,int> > all;
        long long res = 0;
        REP(i,n) {
            pair<int,int> cur = make_pair(l[i] - 1, r[i]);
            if (all.count(cur)) continue;

            all.insert(cur);
            if (sa.LCP[i] == 0) continue;
            
            int bound = max(sa.LCP[l[i] - 1], sa.LCP[r[i] + 1]);
            res += f(r[i] - l[i] + 2) * (sa.LCP[i] - bound);

            // cout << l[i] << ' ' << r[i] << ' ' << sa.LCP[i] << ' ' << res << endl;
        }

        REP(i,n) {
            int len = n - sa.SA[i];
            int done = max(sa.LCP[i], sa.LCP[i+1]);

            res += len - done;
        }
        cout << res << endl;
    }
}
