#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
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
//End of buffer reading

const long double PI = acos((long double) -1.0);

bool check(long long t) {
    while (t % 2 == 0) t /= 2;
    return t == 1;
}

map< pair<int,long long>, long long > cache;

long long get(int row, long long val) {
    if (row == 1) {
        if (val == 1) return 1;
        else return 0;
    }
    if (cache.find(make_pair(row, val)) != cache.end()) {
        return cache[make_pair(row, val)];
    }

    long long res = get(row-1, val);
    if (val % 2 == 0) res += get(row-1, val / 2);
    return cache[make_pair(row, val)] = res;
}

long long get2(int row, long long rowlen, long long k, long long val) {
    if (k == 0) return 0;
    if (row == 1) {
        if (val == 1) return 1;
        else return 0;
    }
    if (k >= rowlen/2) {
        long long res = get(row-1, val);
        if (val % 2 == 0)
            res += get2(row, rowlen, k - rowlen / 2, val / 2);
        return res;
    }
    else {
        return get2(row-1, rowlen / 2, k, val);
    }
}

int main() {
    long long n, t;
    while (cin >> n >> t) {
        cache.clear();
        // cout << "Test: " << n << ' ' << t << endl;
        if (!check(t)) {
            puts("0");
            continue;
        }
        ++n;
        long long res = 0;
        long long counted = 0, rowlen = 1;
        int saveRow = 0;

        for(int row = 1; row <= 1000; ++row) {
            if (counted + rowlen > n) {
                saveRow = row;
                break;
            }

            res += get(row, t);

            counted += rowlen;
            rowlen *= 2;
        }

        // DEBUG(res);
        long long left = n - counted;

        // cout << saveRow << ' ' << rowlen << ' ' << left << endl;

        res += get2(saveRow, rowlen, left, t);

        if (t == 1) --res;
        cout << res << endl;
    }
}
