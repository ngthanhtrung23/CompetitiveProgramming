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
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

//Buffer reading
int INP,AM;
#define BUFSIZE (1<<10)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        fread(BUF,1,BUFSIZE,stdin); \
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

int n, next[100111], prev[100111];
pair<pair<int,int>, pair< pair<int,int>, pair<int,int> > > a[100111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n;
    GN(n);
    FOR(i,0,n+1) {
        next[i] = i+1;
        prev[i] = i-1;
    }
    FOR(i,1,n) {
        GN(a[i].S.F.F);
        GN(a[i].S.S.F);
        GN(a[i].S.F.S);
        GN(a[i].S.S.S);
        GN(a[i].F.F);
        a[i].F.S = i;
    }
        
    sort(a+1,a+n+1);
    
    int q; GN(q);
    int u, v;
    while (q--) {
        GN(u); GN(v);
        int res = 0;
        int i = next[0];
        while (i != n+1) {
            if (a[i].S.F.F <= u && u <= a[i].S.S.F 
             && a[i].S.F.S <= v && v <= a[i].S.S.S) {
                next[prev[i]] = next[i];
                prev[next[i]] = prev[i];
                res = i;
                break;
            }
            i = next[i];
        }
        printf("%d\n", a[res].F.S);
    }
    return 0;
}
