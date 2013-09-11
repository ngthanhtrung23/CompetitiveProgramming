#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
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

struct Num {
    long long x, y;

    Num(long long _x = 0, long long _y = 1) {
        long long g = __gcd(llabs(_x), llabs(_y));
        x = _x / g;
        y = _y / g;
        if (y < 0) {
            x = -x;
            y = -y;
        }
    }
};

Num operator + (Num a, Num b) {
    return Num(a.x*b.y + a.y*b.x, a.y*b.y);
}
Num operator - (Num a, Num b) {
    return Num(a.x*b.y - a.y*b.x, a.y*b.y);
}
Num operator * (Num a, Num b) {
    return Num(a.x*b.x, a.y*b.y);
}
Num operator / (Num a, Num b) {
    return Num(a.x*b.y, a.y*b.x);
}
ostream& operator << (ostream &out, Num a) {
    if (a.x == 0) out << '0';
    else if (a.y == 1) out << a.x;
    else out << a.x << '/' << a.y;
    return out;
}

const int MN = 22;

Num p[MN], q[MN], f[MN], a[MN][MN];
int m, n;

void solve() {
    REP(j,n) { // Khu cot j
        int save = j;
        while (a[save][j].x == 0) ++save;

        REP(k,n+1) swap(a[j][k], a[save][k]);

        FOR(i,j+1,n-1) if (a[i][j].x) {
            Num mult = a[i][j] / a[j][j];
            REP(k,n+1)
                a[i][k] = a[i][k] - a[j][k] * mult;
        }
    }
    FORD(i,n-1,0) {
        FOR(j,i+1,n-1)
            a[i][n] = a[i][n] - a[i][j] * q[j];
        q[i] = a[i][n] / a[i][i];
    }
}

void print(Num p[], int n) {
    bool good = false;
    REP(i,n) {
        if (p[i].x) {
            good = true;
            cout << '(' << p[i] << ',' << i << ')' << ' ';
        }
    }
    if (!good) {
        cout << "(0,0)";
    }
    cout << endl;
}

int main() {
    while (cin >> m >> n && m) {
        memset(f, 0, sizeof f);
        memset(p, 0, sizeof p);
        memset(q, 0, sizeof q);
        memset(a, 0, sizeof a);

        REP(i,m+n) {
            cin >> f[i].x; f[i].y = 1;
        }
        // solve q
        REP(i,n) {
            REP(j,n) {
                if (m+j-i >= 0) a[i][n-j-1] = f[m+j-i];
                else a[i][n-j-1] = Num(0, 1);
            }
            a[i][n] = (i == 0) ? Num(1,1) : Num(0, 1);
        }
        solve();

        // solve p
        FORD(i,m-1,0) {
            p[i] = q[0]*f[i];
            for(int j=1; j<n; j++) {
                if (i-j >= 0)
                    p[i] = p[i] + q[j]*f[i-j];
            }
        }
        print(p, m);
        print(q, n);
        cout << endl;
    } 
    return 0;
}
