
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

const int MAXN = 400111;
const int MAXLOG = 22;

int table[MAXLOG][MAXN];
int numlog[MAXN];

int n, x[MAXN];

void buildTable() {
    numlog[1] = 0;
    for (int i = 2; i <= n; i++)
        numlog[i] = numlog[i / 2] + 1;

    for (int i = 0; i <= numlog[n]; i++) {
        int curlen = 1 << i;
        for (int j = 1; j <= n; j++) {
            if (i == 0) {
                table[i][j] = x[j];
                continue;
            }
            table[i][j] = min(table[i - 1][j], table[i - 1][j + curlen / 2]);
        }
    }
}

int getMin(int l, int r) {
    int curlog = numlog[r - l + 1];
    return min(table[curlog][l], table[curlog][r - (1 << curlog) + 1]); 
}

string a, b;
int res[MAXN];
int sum[MAXN];

bool check(int i, int len) {
    int first = i+1, last = i;

    // find first
    int l = 1, r = i;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (getMin(mid, i) >= len) {
            first = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    // find last
    l = i+1, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (getMin(i+1, mid) >= len) {
            last = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }

    --first;
    if (first == 0) return sum[last] > 0;
    else return sum[last] - sum[first-1] > 0;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("hackers.in", "r", stdin);
    freopen("hackers.out", "w", stdout);
    while (cin >> a >> b) {
        string s = a + "#" + b;

        SuffixArray SA(s, 300);
//        PR0(SA.SA, SZ(SA.SA));

        int la = a.length();
        int lb = b.length();
//        DEBUG(la);

        n = SZ(s) - 1;
        FOR(i,1,n) x[i] = SA.LCP[i];
        buildTable();

        FOR(i,0,n) {
            if (SA.SA[i] > la) sum[i] = 1;
            else sum[i] = 0;

            if (i > 0) sum[i] += sum[i-1];
        }

        FOR(i,1,n) {
            int u = SA.SA[i];

            if (u >= la) continue;

            int l = 1, r = lb;
            res[u] = 0;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (check(i, mid)) {
                    res[u] = mid;
                    l = mid + 1;
                }
                else r = mid - 1;
            }
        }

        REP(i,la) cout << res[i] << ' '; cout << endl;
    }
}
