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
            SA(N), LCP(N), x(N), y(N), w(max(N, m)), c(N) {
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


#define TWO(X) (1<<(X))
#define next next_
const int MN = 1000111;

string s;
int n, indexOf[MN], next[MN];
int rmq[22][MN], lg[MN];

int getMin(int l, int r) {
    if (l > r) return 1000111000;
    int t = lg[r - l + 1];
    return min( rmq[t][l], rmq[t][1+r-TWO(t)] );
}

int getRight(int id, int x) {
    int left = id, right = n-1, res = id;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (getMin(id+1, mid) >= x) {
            res = mid;
            left = mid + 1;
        }
        else right = mid - 1;
    }
    return res;
}

int getLeft(int id, int x) {
    int left = 0, right = id, res = id;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (getMin(mid+1, id) >= x) {
            res = mid;
            right = mid - 1;
        }
        else left = mid + 1;
    }
    return res;
}

int count(int x) {
    int r = getRight(indexOf[x], n-x);
    int l = getLeft(indexOf[x], n-x);
    return r - l + 1;
}

int main() {
    while (cin >> s) {
        n = s.length();
        bool ok = true;
        REP(i,n) if (s[i] != s[0]) ok = false;
        if (ok) {
            cout << n << endl;
            FOR(i,1,n) cout << i << ' ' << n - i + 1 << "\n";
            continue;
        }
        SuffixArray SA(s, 256);

        memset(lg, 0, sizeof lg);
        lg[0] = 0;
        for(int i = 1, x = 0; i < MN; i *= 2, ++x)
            lg[i] = x;
        FOR(i,2,MN-1)
            if (!lg[i]) lg[i] = lg[i-1];

        REP(i,n) rmq[0][i] = SA.LCP[i];
        FOR(t,1,20)
            FOR(i,0,n-TWO(t))
                rmq[t][i] = min(rmq[t-1][i], rmq[t-1][i+TWO(t-1)]);

        REP(i,n) indexOf[SA.SA[i]] = i;

        next[0] = -1;
        int j = -1;
        FOR(i,1,n-1) {
            while (j >= 0 && s[i] != s[j+1]) j = next[j];
            if (s[i] == s[j+1]) ++j;
            next[i] = j;
        }

        vector< pair<int,int> > res;
        int x = n-1;
        while (x >= 0) {
            res.push_back(make_pair(1+x, count(n-1-x)));
            x = next[x];
        }
        cout << res.size() << "\n";
        FORD(i,res.size()-1,0)
            cout << res[i].first << ' ' << res[i].second << "\n";
    }
}