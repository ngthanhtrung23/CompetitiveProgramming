#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
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
//End of buffer reading

int n;
long long a[22];

bool check1() {
    if (!a[1] || a[2] % a[1]) return false;

    long long d = a[2] / a[1];
    FOR(i,2,n)
        if (a[i] != a[i-1] * d) return false;

    cout << a[n] * d << endl;

    return true;
}

bool solve(long long a11, long long a12, long long a13, long long a21, long long a22, long long a23, long long &x, long long &y) {
    long long u = a11*a22 - a21*a12;
    long long v = a13*a22 - a12*a23;
    if (!v || u % v) return false;
    y = u / v;

    if (!a12 || (a11 - a13*y) % a12) return false;
    x = (a11 - a13*y) / a12;

    return true;
}

bool check2() {
    long long x, y;
    if (!a[1] || !a[2]) return false;
    if (!solve(a[3], a[2], a[1], a[4], a[3], a[2], x, y)) return false;

    FOR(i,3,n)
        if (a[i] != x * a[i-1] + y * a[i-2]) return false;

    cout << a[n] * x + a[n-1] * y << endl;

    return true;
}

bool check3() {
    long long x, y, z;
    x = y = z = 0;
    if (!solve(a[4]*a[4] - a[5]*a[3], a[2]*a[4] - a[3]*a[3], a[1]*a[4] - a[2]*a[3],
            a[5]*a[5] - a[6]*a[4], a[3]*a[5] - a[4]*a[4], a[2]*a[5] - a[3]*a[4],
            y, z)) {
        solve(a[6]*a[6] - a[7]*a[5], a[4]*a[6] - a[5]*a[5], a[3]*a[6] - a[4]*a[5],
            a[7]*a[7] - a[8]*a[6], a[5]*a[7] - a[6]*a[6], a[4]*a[7] - a[5]*a[6],
            y, z);
    }

    x = (a[4] - y*a[2] - z*a[1]) / a[3];
    cout << a[n] * x + a[n-1] * y + a[n-2] * z << endl;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n; FOR(i,1,n) cin >> a[i];
        if (check1()) continue;
        if (check2()) continue;
        check3();
    }
    return 0;
}
