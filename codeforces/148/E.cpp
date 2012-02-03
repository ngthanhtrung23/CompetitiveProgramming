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
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

int INP,AM;
#define BUFSIZE (1<<10)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF,0,sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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

const double PI = acos(-1.0);

int f[111][10111], n, m, a[111][111], len[111], sum[111], left_[111][111], right_[111][111], best[111][111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d%d", &n, &m);
    FOR(i,1,n) {
        scanf("%d", &len[i]);
        FOR(j,1,len[i]) {
            scanf("%d", &a[i][j]);
            left_[i][j] = left_[i][j-1] + a[i][j];
        }
        FORD(j,len[i],1) {
            right_[i][j] = right_[i][j+1] + a[i][j];
        }
        FOR(j,1,len[i]) FOR(l,0,j) {
            int r = j - l;
            best[i][j] = max(best[i][j], left_[i][l] + right_[i][len[i]-r+1]);
        }
        sum[i] = sum[i-1] + len[i];
    }
    /*
    FOR(i,1,n) {
        FOR(j,1,len[i]) cout << best[i][j] << ' ';
        puts("");
    }*/
    if (m > sum[n]) m = sum[n];
    f[0][0] = 0;
    FOR(i,1,n) FOR(j,0,sum[i]) {
        f[i][j] = f[i-1][j];
        FOR(now,1,len[i]) if (now <= j) {
            f[i][j] = max(f[i][j], f[i-1][j-now] + best[i][now]);
        }
    }
//    FOR(i,1,n) {
//        FOR(j,0,sum[i]) cout << f[i][j] << ' ';
//        puts("");
//    }
    printf("%d", f[n][m]);
    return 0;
}
