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
int k, n;
long long sumLen[MN];
SuffixArray SA("", 256);

inline int suffixLen(int i) {
    return n - i;
}

int findPos(int l, int r, char c, int len, bool first) {
    int res = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        char cmid = (SA.SA[mid] + len - 1 < n) ? s[SA.SA[mid] + len - 1] : 'a' - 1;
        if (cmid < c) {
            l = mid + 1;
        }
        else if (cmid > c) {
            r = mid - 1;
        }
        else {
            res = mid;
            if (first) r = mid - 1;
            else l = mid + 1;
        }
    }
    return res;
}

int main() {
    while (cin >> s >> k) {
        n = s.length();
        SA = SuffixArray(s, 256);
        if (k > (n * (n+1LL)) / 2) {
            cout << "No such line." << endl;
            continue;
        }

//        PR0(SA.SA, n);
//        PR0(SA.LCP, n);

        sumLen[0] = suffixLen(SA.SA[0]);
        FOR(i,1,n-1) sumLen[i] = sumLen[i-1] + suffixLen(SA.SA[i]);

        int l = 0, r = n-1, len = 1;
        while (k > 0) {
//            cout << "Search " << k << ": " << l << " --> " << r << "  " << len << endl;
            int from, to;
            FOR(c,'a','z') {
                from = findPos(l, r, c, len, true);
                to = findPos(l, r, c, len, false);

                if (from < 0) continue;

                long long cnt = sumLen[to] - ((from == 0) ? 0 : sumLen[from - 1]);
                cnt -= (to - from + 1) * (len - 1);

//                cout << "   " << (char) c << ' ' << from << ' ' << to << ' ' << cnt << endl;

                if (cnt >= k) {
                    l = from;
                    r = to;
                    break;
                }
                else k -= cnt;
            }
            ++len;
            k -= to - from + 1;
        }

        cout << s.substr(SA.SA[l], len-1) << endl;
    }
}
