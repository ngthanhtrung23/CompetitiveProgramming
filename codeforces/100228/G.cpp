
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

const int MN = 1000111;
char a[150][150];
struct Node {
    bool black, white;
    string rep;
} it[MN];
int m, n;

ll p[MN];

int go1(int i, int u, int d, int l, int r) {
    if (u == d) {
        if (a[u][l] == '1') {
            it[i].black = true;
            it[i].white = false;
            it[i].rep = "1";
        }
        else {
            it[i].white = true;
            it[i].black = false;
            it[i].rep = "0";
        }
        return 1;
    }
    int m1 = (u + d) >> 1;
    int m2 = (l + r) >> 1;

    int f1 = go1(i*4 - 2, u, m1, l, m2);
    int f2 = go1(i*4 - 1, u, m1, m2+1, r);
    int f3 = go1(i*4 - 0, m1+1, d, l, m2);
    int f4 = go1(i*4 + 1, m1+1, d, m2+1, r);

    it[i].black = it[i*4 - 2].black
                && it[i*4 - 1].black
                && it[i*4 - 0].black
                && it[i*4 + 1].black;
    it[i].white = it[i*4 - 2].white
                && it[i*4 - 1].white
                && it[i*4 - 0].white
                && it[i*4 + 1].white;

    if (it[i].black || it[i].white) {
        if (it[i].black) it[i].rep = "1";
        else it[i].rep = "0";
        return 1;
    }
    else {
        char bound = 'A' - 1;
        for(char c : it[i*4 - 2].rep) bound = max(bound, c);
        for(char c : it[i*4 - 1].rep) bound = max(bound, c);
        for(char c : it[i*4 - 0].rep) bound = max(bound, c);
        for(char c : it[i*4 + 1].rep) bound = max(bound, c);
        ++bound;

        it[i].rep = it[i*4 - 2].rep + bound
                +   it[i*4 - 1].rep + bound
                +   it[i*4 - 0].rep + bound
                +   it[i*4 + 1].rep;
        return 1 + f1 + f2 + f3 + f4;
    }
}

unordered_set<string> all;
int go2(int i, int u, int d, int l, int r) {
    if (it[i].black || it[i].white) {
        return 1;
    }
    if (all.count(it[i].rep)) {
        return 0;
    }
    all.insert(it[i].rep);

    int m1 = (u + d) >> 1;
    int m2 = (l + r) >> 1;

    int f1 = go2(i*4 - 2, u, m1, l, m2);
    int f2 = go2(i*4 - 1, u, m1, m2+1, r);
    int f3 = go2(i*4 - 0, m1+1, d, l, m2);
    int f4 = go2(i*4 + 1, m1+1, d, m2+1, r);

    return 1 + f1 + f2 + f3 + f4;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    p[0] = 1; FOR(i,1,MN-1) p[i] = p[i-1] * 7LL;

    while (scanf("%d%d", &m, &n) == 2 && m && n) {
        memset(a, '0', sizeof a);
        FOR(i,1,m) {
            scanf("%s\n", &a[i][1]);
            a[i][n+1] = '0';
        }
        while (__builtin_popcount(m) > 1) ++m;
        while (__builtin_popcount(n) > 1) ++n;

        m = n = max(m, n);

        all.clear();
        int res1 = go1(1, 1, m, 1, n);
        int res2 = go2(1, 1, m, 1, n);
        cout << res1 << ' ' << res2 << endl;
    }
}
