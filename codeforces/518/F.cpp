#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 2011;
#define __ [MN][MN]
#define left __left
#define right __right
#define next __next
#define ll long long

int m, n;
char a __, tmp __;
bool down __, up __, left __, right __;
int sum __, next __;

void init() {
    memset(down, 0, sizeof down);
    memset(up, 0, sizeof up);
    memset(left, 0, sizeof left);
    memset(right, 0, sizeof right);
    memset(sum, 0, sizeof sum);
    memset(next, 0, sizeof next);
}

void preprocess() {
    init();
    FOR(i,1,m) FOR(j,1,n) {
        if (a[i][j] == '#') up[i][j] = 0;
        else if (i == 1) up[i][j] = 1;
        else up[i][j] = up[i-1][j];
    }
    FORD(i,m,1) FOR(j,1,n) {
        if (a[i][j] == '#') down[i][j] = 0;
        else if (i == m) down[i][j] = 1;
        else down[i][j] = down[i+1][j];
    }
    FOR(i,1,m) {
        FOR(j,1,n) {
            sum[i][j] = sum[i][j-1];
            if (up[i][j]) ++sum[i][j];
            if (down[i][j]) ++sum[i][j];
        }
    }

    FOR(j,1,n) FOR(i,1,m) {
        if (a[i][j] == '#') left[i][j] = 0;
        else if (j == 1) left[i][j] = 1;
        else left[i][j] = left[i][j-1];
    }
    FORD(j,n,1) FOR(i,1,m) {
        if (a[i][j] == '#') right[i][j] = 0;
        else if (j == n) right[i][j] = 1;
        else right[i][j] = right[i][j+1];
    }

    FOR(i,1,m) {
        FORD(j,n,1) {
            if (a[i][j] == '#') next[i][j] = j;
            else if (j == n) next[i][j] = n;
            else next[i][j] = next[i][j+1];
        }
    }
}

int zero() {
    int res = 0;
    // straight line
    FOR(j,2,n-1)
        if (down[1][j]) ++res;
    return res;
}

int one() {
    int res = 0;
    // 1 turn
    FOR(i,2,m-1) FOR(j,2,n-1)
        if (up[i][j]) {
            if (right[i][j]) ++res;
            if (left[i][j]) ++res;
        }
    return res;
}

ll two() {
    // we only count the paths that start from upper edge
    ll res = 0;
    
    // 2 turns
    FOR(i,2,m-1) FOR(j,2,n-1) if (up[i][j]) {
        if (j+1 < n && down[i][j+1]) ++res;

        int from = j + 2;
        int to = next[i][j] - 1;
        if (to == n) --to;
        if (from <= to) {
            res += sum[i][to] - sum[i][from-1];
        }
    }
    return res;
}

int main() {
    while (scanf("%d %d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        init();
        
        // normal
        preprocess();
        ll res = zero();
        res += one();
        res += two();
//        DEBUG(res);

        // reverse
        for(int i=1; i < m+1-i; i++)
            FOR(j,1,n)
                swap(a[i][j], a[m+1-i][j]);
        preprocess();
        res += one();
        res += two();
//        DEBUG(res);

        // rotate
        FOR(i,1,m) FOR(j,1,n) tmp[i][j] = a[i][j];
        swap(m, n);
        FOR(i,1,m) FOR(j,1,n) a[i][j] = tmp[j][i];
        preprocess();
        res += zero();
        res += two();
//        DEBUG(res);

        // reverse
        for(int i=1; i < m+1-i; i++)
            FOR(j,1,n)
                swap(a[i][j], a[m+1-i][j]);
        preprocess();
        res += two();
//        DEBUG(res);

        cout << res << endl;
    }
    return 0;
}
