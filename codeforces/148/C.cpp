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

int n, a, b, c, res[111], cur = 0;

void case1() {
    int sum = 0;
    cur = 0;
    FOR(i,1,1) {
        res[++cur] = 1;
        sum++;
    }
    FOR(i,1,b) {
        res[++cur] = sum + 1;
        sum += sum + 1;
    }
    FOR(i,1,a) {
        int x = res[cur];
        res[++cur] = x+1;
        sum += x+1;
    }
    FOR(i,2,c) {
        res[++cur] = 1;
        sum++;
    }
}

void norm() {
    int sum = 0;
    cur = 0;
    FOR(i,1,c) {
        res[++cur] = 1;
        sum++;
    }
    FOR(i,1,b) {
        res[++cur] = sum + 1;
        sum += sum + 1;
    }
    FOR(i,1,a) {
        int x = res[cur];
        res[++cur] = x+1;
        sum += x+1;
    }
    FOR(i,1,n) if (res[i] > 50000) case1();
}

bool check() {
    int x = 0, y = 0;
    int sum = 0, ln = 0;
    FOR(i,1,n) {
        if (i > 1) {
            if (res[i] > sum) y++;
            else if (res[i] > ln) x++;
        }
        sum += res[i]; ln = max(ln, res[i]);
        if (res[i] > 50000) return false;
    }
    return (x == a && y == b);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> n >> a >> b;
    cur = 0;
    c = n - a - b;
    if (c <= 0) { puts("-1");
    }
    else if (n == 1) {
        puts("1");
    }
    else if (c == 1 && b == 0) { puts("-1");
    }
    else norm();
    FOR(i,1,cur) cout << res[i] << ' ';
    return 0;
}
