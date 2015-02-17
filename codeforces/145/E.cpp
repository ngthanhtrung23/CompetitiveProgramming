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

char a[1000111];
int c4[6000111], c7[6000111], f4[6000111], f7[6000111];
bool cov[6000111];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void update(int i) {
    c4[i] = c4[CT(i)] + c4[CP(i)];
    c7[i] = c7[CT(i)] + c7[CP(i)];
    f4[i] = c4[CT(i)] + c7[CP(i)];
    f4[i] = max(c4[CT(i)] + f4[CP(i)], f4[CT(i)] + c7[CP(i)]);
    f7[i] = max(c7[CT(i)] + f7[CP(i)], f7[CT(i)] + c4[CP(i)]);
}

void cover(int i) {
    if (!cov[i]) return ;
    cov[CT(i)] = !cov[CT(i)];
    swap(c4[CT(i)], c7[CT(i)]);
    swap(f4[CT(i)], f7[CT(i)]);
    
    cov[CP(i)] = !cov[CP(i)];
    swap(c4[CP(i)], c7[CP(i)]);
    swap(f4[CP(i)], f7[CP(i)]);
    cov[i] = !cov[i];
}

void build(int i, int l, int r) {
    if (l == r) {
        if (a[l] == '4') c4[i] = 1; else c4[i] = 0;
        if (a[l] == '7') c7[i] = 1; else c7[i] = 0;
        f4[i] = f7[i] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
    update(i);
}

void query(int i, int l, int r, int a, int b) {
    if (l > r) return ;
    if (b < l || r < a) return ;
    if (a <= l && r <= b) {
        cov[i] = !cov[i];
        swap(c4[i], c7[i]);
        swap(f4[i], f7[i]);
        return ;
    }
    cover(i);
    int mid = (l + r) >> 1;
    query(CT(i), l, mid, a, b);
    query(CP(i), mid+1, r, a, b);
    update(i);
}

char tmp[100];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m; scanf("%d%d\n", &n, &m);
    scanf("%s\n", &a[1]);
    build(1,1,n);
    while (m--) {
        char c; scanf("%c", &c);
        if (c == 'c') {
            printf("%d\n", f4[1]);
            gets(tmp);
        }
        else {
            int a, b; scanf("witch %d %d\n", &a, &b);
            query(1, 1, n, a, b);
        }
    }
    return 0;
}