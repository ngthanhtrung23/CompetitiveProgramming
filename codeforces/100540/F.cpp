#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

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

const int MN = 1000111;
string a[66];
int id[MN];

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (S & TWO(X))
#define left left_
#define right right_
#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

int left[MN], right[MN], st[MN], top, x[MN];
long long it[MN * 4];

void update(int i, int l, int r, int u, long long val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i] |= val;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, val);
    update(CP(i), mid+1, r, u, val);
    it[i] = it[CT(i)] | it[CP(i)];
}

long long get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i];
    int mid = (l + r) >> 1;
    return get(CT(i), l, mid, u, v) | get(CP(i), mid+1, r, u, v);
}

int start[1000111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n;
    while (cin >> n && n) {
        memset(id, 0, sizeof id);
        string all = "";
        memset(start, 0, sizeof start);
        FOR(i,1,n) {
            int oldLen = all.length();
            cin >> a[i];
            all += a[i];
            all += i;

            FOR(x,oldLen,SZ(all)-2)
                id[x] = i;
            start[oldLen] = i;
        }
//        PR0(id,all.size());
        SuffixArray sa(all, 300);
//        DEBUG(all);
//        PR0(sa.SA, sa.SA.size());
//        PR0(sa.LCP, sa.LCP.size());

        n = all.size();

        FOR(i,1,n-1) {
            x[i] = sa.LCP[i];
        }

        top = 0; st[0] = -1;
        REP(i,n) {
            while (top && x[st[top]] >= x[i]) --top;
            left[i] = st[top] + 1;
            st[++top] = i;
        }
        top = 0; st[0] = n;
        FORD(i,n-1,0) {
            while (top && x[st[top]] >= x[i]) --top;
            right[i] = st[top] - 1;
            st[++top] = i;
        }
//        PR0(left, n);
//        PR0(right, n);
        memset(it, 0, sizeof it);
        REP(i,n) {
            int t = id[sa.SA[i]];
            if (t) {
                update(1, 1, n, i+1, TWO(t-1LL));
            }
        }

        set< long long > masks;
        REP(i,n) if (id[sa.SA[i]] && sa.LCP[i]) {
            int from = left[i], to = right[i] + 1;
            long long t = get(1, 1, n, from, to);
            masks.insert(t);
        }
        REP(i,n) if (start[sa.SA[i]]) {
            int id = start[sa.SA[i]];
            if (sa.LCP[i] >= a[id].length()) continue;
            if (i < n-1 && sa.LCP[i+1] >= a[id].length()) continue;

            masks.insert(TWO(start[sa.SA[i]] - 1));
        }
//        for(auto mask : masks) cout << mask << ' '; cout << endl;

        cout << SZ(masks) << endl;
    }
    return 0;
}
