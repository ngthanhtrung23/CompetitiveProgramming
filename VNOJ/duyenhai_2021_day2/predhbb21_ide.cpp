// CTDL:
// - prefix sum: s(i) = sum(1..i)
//   ( -> +1
//   ) -> -1
//
// - s(i) = (
//   -> j:
//      s(i-1) = s(j)
//      s(i)..s(j-1) >= s(i-1)
//
// day ngoac dung:
// - tong = 0
// - khong ton tai prefix sum < 0

#include "bits/stdc++.h"
using namespace std;

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

void upd(int& f, int val) {
    if (val < f) f = val;
}

struct {
    int lazy[400111];
    int min_sum[400111];

    void down(int i) {
        if (!lazy[i]) return;

        lazy[i*2] += lazy[i];
        min_sum[i*2] += lazy[i];

        lazy[i*2+1] += lazy[i];
        min_sum[i*2+1] += lazy[i];

        lazy[i] = 0;
    }

    void update(int i, int l, int r, int u, int v, int val) {
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            min_sum[i] += val;
            lazy[i] += val;
            return;
        }

        int mid = (l + r) / 2;
        down(i);

        update(i*2, l, mid, u, v, val);
        update(i*2+1, mid+1, r, u, v, val);

        min_sum[i] = min(min_sum[i*2], min_sum[i*2+1]);
    }

    int get(int i, int l, int r, int u) {
        if (l == r) return min_sum[i];

        int mid = (l + r) / 2;
        down(i);

        if (u <= mid) return get(i*2, l, mid, u);
        else return get(i*2+1, mid+1, r, u);
    }

    int getMin(int i, int l, int r, int u, int v, int val) {
        if (v < l || r < u || min_sum[i] > val) return 1000111000;
        if (u <= l && r <= v) return min_sum[i];

        int mid = (l + r) / 2;
        down(i);

        int res = 1000111000;
        // [u, v] giao [l, mid]
        if (u <= mid) {
            upd(res, getMin(i*2, l, mid, u, v, val));
        }
        if (v > mid) {
            upd(res, getMin(i*2+1, mid+1, r, u, v, val));
        }
        return res;
    }

    int matching(int u, int n) {
        int pref_u_1 = (u == 1) ? 0 : get(1, 1, n, u - 1);

        if (getMin(1, 1, n, u, n, 1000111000) > pref_u_1) {
            return -1;
        }

        int l = u, r = n, res = n;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (getMin(1, 1, n, u, mid, pref_u_1) <= pref_u_1) {
                r = mid - 1;
                res = mid;
            } else {
                l = mid + 1;
            }
        }
        int v = res;
        int pref_v = get(1, 1, n, v);
        if (pref_v == pref_u_1) return v;

        return -1;
    }
} xuoi, nguoc;

string s, rev;

int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}

bool valid(char c) {
    if (c == '(' || c == ')') return true;
    return c >= 'a' && c <= 'z';
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n, q; GN(n); GN(q);
    for (int i = 0; i <= n + 1; i++) {
        s += ' ';
    }
    rev = s;

    while (q--) {
        int u; char c = ' '; GN(u);
        while (!valid(c)) GETCHAR(c);

        int rev_u = n - u + 1;
        char rev_c = c;
        if (c == '(') rev_c = ')';
        else if (c == ')') rev_c = '(';

        if (s[u] == '(') {
            // (..
            // ..)
            xuoi.update(1, 1, n, u, n, -1);

            assert(rev[rev_u] == ')');
            nguoc.update(1, 1, n, rev_u, n, +1);
        } else if (s[u] == ')') {
            xuoi.update(1, 1, n, u, n, +1);

            assert(rev[rev_u] == '(');
            nguoc.update(1, 1, n, rev_u, n, -1);
        }

        s[u] = c;
        rev[rev_u] = rev_c;

        if (s[u] == '(') {
            // (..
            // ..)
            xuoi.update(1, 1, n, u, n, +1);

            assert(rev[rev_u] == ')');
            nguoc.update(1, 1, n, rev_u, n, -1);
        } else if (s[u] == ')') {
            xuoi.update(1, 1, n, u, n, -1);

            assert(rev[rev_u] == '(');
            nguoc.update(1, 1, n, rev_u, n, +1);
        }

        if (s[u] == '(') {
            cout << xuoi.matching(u, n) << '\n';
        } else if (s[u] == ')') {
            assert(rev[rev_u] == '(');
            int res = nguoc.matching(rev_u, n);
            if (res < 0) cout << "-1\n";
            else cout << n - res + 1 << '\n';
        }
    }
    return 0;
}
