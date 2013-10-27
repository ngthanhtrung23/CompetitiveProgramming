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

const int MN = 111;

struct Point {
    long double x, y;
    Point(long double x = 0, long double y = 0) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (long double t) { return Point(x*t, y*t); }

    void read() { cin >> x >> y; }
    long double len() { return sqrt(x*x + y*y); }
};

struct Rect {
    Point A, B, C, D;

    void read() {
        A.read(); B.read();
        C.read(); D.read();
    }
};

struct Card {
    Point A, B, C, D;
    vector < Rect > r;

    void read() {
        A.read(); B.read(); C.read(); D.read();
        int k; cin >> k;
        r.resize(k);
        REP(i,k) {
            r[i].read();
        }
    }
} a[MN];

long double s[MN];
int nCard;

long double area(Point A, Point B, Point C) {
    B = B - A; C = C - A;
    return fabs(B.x*C.y - B.y*C.x);
}

void solve(int t) {
    long double bigarea = 0;
    Point O = (a[t].A + a[t].B) * 0.5;
    long double R1 = (a[t].A - O).len();
    long double R2 = (a[t].C - O).len();

    bigarea = R1 * R2;
    // DEBUG(t);
    // DEBUG(bigarea);

    s[t] = 0;
    REP(i,a[t].r.size()) {
        s[t] += area(a[t].r[i].A, a[t].r[i].B, a[t].r[i].C);
    }
    // DEBUG(s[t]);
    s[t] /= bigarea;
}

struct Double {
    long double x;

    Double(long double x) : x(x) {}
};
bool operator < (const Double &a, const Double &b) {
    if (fabs(a.x - b.x) < 1e-6) return false;
    return a.x < b.x;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nCard) {
        FOR(i,1,nCard) {
            a[i].read();
            solve(i);
        }
        // PR(s, nCard);

        map<Double,int> mp; mp.clear();
        int cnt = 0;
        FOR(i,1,nCard) {
            if (mp.find(s[i]) == mp.end()) {
                mp[s[i]] = ++cnt;
            }
        }
        FOR(i,1,nCard) {
            cout << mp[s[i]] << ' ';
        }
        cout << endl;
    }
    return 0;
}
