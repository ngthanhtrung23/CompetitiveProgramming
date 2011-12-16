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

char a[511];
int pal[511][511], f[511][511], k, tr[511][511];

void pald(int l, int r) {
    for(int i = l, j = r; i <= j; i++, j--) {
        if (a[i] != a[j]) a[j] = a[i];
    }
    FOR(i,l,r) printf("%c", a[i]);
}

void trace(int i, int k) {
    int j = tr[i][k];
    if (j == -1) {
        pald(0,i);
    }
    else {
        trace(j, k-1);
        printf("+");
        pald(j+1, i);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    gets(a);
    scanf("%d", &k);
    int n = strlen(a);
    FORD(i,n-1,0) FOR(j,i,n-1) {
        if (a[i] == a[j]) pal[i][j] = pal[i+1][j-1];
        else pal[i][j] = pal[i+1][j-1] + 1;
    }
    memset(tr, -1, sizeof tr);
    REP(i,n) {
        f[i][1] = pal[0][i];
        FOR(kk,2,k) {
            f[i][kk] = f[i][kk-1];
            tr[i][kk] = tr[i][kk-1];
            FOR(j,0,i-1) {
                if (f[j][kk-1] + pal[j+1][i] < f[i][kk]) {
                    f[i][kk] = f[j][kk-1] + pal[j+1][i];
                    tr[i][kk] = j;
                }
            }
        }
    }
    cout << f[n-1][k] << endl;
    trace(n-1, k);
    return 0;
}
