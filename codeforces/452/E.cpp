#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <complex>
#include <cstring>
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

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1000111;

char a[MN];

#define x _x
#define y _y

int N, m, SA [MN], LCP [MN];
int x [MN], y [MN], w [MN], c [MN];

inline bool cmp (const int a, const int b, const int l) { return (y [a] == y [b] && y [a + l] == y [b + l]); }

void Sort () {
    for (int i = 0; i < m; ++i) w [i] = 0;
    for (int i = 0; i < N; ++i) ++w [x [y [i]]];
    for (int i = 0; i < m - 1; ++i) w [i + 1] += w [i];
    for (int i = N - 1; i >= 0; --i) SA [--w [x [y [i]]]] = y [i];
}

void DA () {
    for (int i = 0; i < N; ++i) x [i] = a [i], y[i] = i;
    Sort();
    for (int i, j = 1, p = 1; p < N; j <<= 1, m = p) {
        for (p = 0, i = N - j; i < N; i++) y [p++] = i;
        for (int k = 0; k < N; ++k) if (SA [k] >= j) y [p++] = SA [k] - j;
        Sort ();
        for (swap (x, y), p = 1, x [SA [0]] = 0, i = 1; i < N; ++i) x [SA [i]] = cmp (SA [i - 1], SA [i], j) ? p - 1 : p++;
    }
}

void kasaiLCP () {
    for (int i = 0; i < N; i++) c [SA [i]] = i;
    for (int i = 0, j, k = 0; i < N; LCP [c [i++]] = k)
        if (c [i] > 0) for (k ? k-- : 0, j = SA [c [i] - 1]; a [i + k] == a [j + k]; k++);
        else k = 0;
}

void suffixArray () {
    m = 256;
    DA ();
    kasaiLCP ();
}

#undef x
#undef y

int n;
char x[MN], y[MN], z[MN];
int typ[MN], cnt[4][MN];

long long MOD = 1000000007LL;

long long get(int from, int to) {
    long long x = cnt[1][to] - ((from == 0) ? 0 : cnt[1][from-1]);
    long long y = cnt[2][to] - ((from == 0) ? 0 : cnt[2][from-1]);
    long long z = cnt[3][to] - ((from == 0) ? 0 : cnt[3][from-1]);
    return (x * y) % MOD * z % MOD;
}

int top, st[MN], l[MN], r[MN];
long long res[MN];

set< pair<int,int> > all;

int main() {
    ios :: sync_with_stdio(false);
    while (gets(x) && gets(y) && gets(z)) {
        int lx = strlen(x);
        int ly = strlen(y);
        int lz = strlen(z);
        n = 0;
        REP(i,lx) a[n++] = x[i];
        a[n++] = 'X';
        REP(i,ly) a[n++] = y[i];
        a[n++] = 'Y';
        REP(i,lz) a[n++] = z[i];
        a[n++] = 'Z';
        N = n;
        // PR0(a,n);
        suffixArray();
        // PR0(SA, n);
        // PR0(LCP, n);
        REP(i,n) {
            if (SA[i] >= 0 && SA[i] <= lx-1) typ[i] = 1;
            else if (SA[i] >= lx+1 && SA[i] <= lx+ly) typ[i] = 2;
            else if (SA[i] >= lx+ly+2 && SA[i] <= lx+ly+lz+1) typ[i] = 3;
            else typ[i] = 0;
        }

        REP(t,4) {
            REP(i,n) {
                if (i == 0) cnt[t][i] = 0;
                else cnt[t][i] = cnt[t][i-1];

                if (typ[i] == t) ++cnt[t][i];
            }
        }

        int top = 0; st[0] = -1;
        REP(i,n) {
            while (top && LCP[st[top]] >= LCP[i]) --top;
            l[i] = st[top] + 1;
            st[++top] = i;
        }

        top = 0; st[0] = n;
        FORD(i,n-1,0) {
            while (top && LCP[st[top]] >= LCP[i]) --top;
            r[i] = st[top] - 1;
            st[++top] = i;
        }

        // PR0(l, n);
        // PR0(r, n);

        memset(res, 0, sizeof res);
        all.clear();

        REP(i,n) if (LCP[i]) {
            int from = l[i] - 1;
            int to = r[i];

            if (all.find(make_pair(from, to)) != all.end()) continue;

            all.insert(make_pair(from, to));

            long long cur = get(from, to);

            int x = max(LCP[l[i] - 1], LCP[r[i]+1]) + 1;
            int y = LCP[i];
            res[x] = (res[x] + cur) % MOD;
            res[y+1] = (res[y+1] - cur + MOD) % MOD;
        }

        FOR(i,1,min(lx,min(ly,lz))) {
            res[i] = (res[i] + res[i-1]) % MOD;
            cout << res[i] << ' ';
        }
        cout << endl;
    }
    return 0;
}
