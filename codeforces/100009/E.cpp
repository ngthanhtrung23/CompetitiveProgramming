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

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
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

long double r;

long double mysin(long double x) {
    return sin(x * PI / 180.0);
}

long double mycos(long double x) {
    return cos(x * PI / 180.0);
}

struct Point {
    long double x, y, z;
    
    Point() { x = y = z = 0; }
    
    Point(long double theta, long double gamma) {
        theta = 90 - theta;
        if (gamma = 360) gamma = 0;
        
        x = r * mysin(theta) * mycos(gamma);
        y = r * mysin(theta) * mysin(gamma);
        z = r * mycos(theta);
    }
    
    Point(long double x, long double y, long double z) : x(x), y(y), z(z) {}
    
    Point operator + (Point a) { return Point(x+a.x, y+a.y, z+a.z); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y, z-a.z); }
    Point operator * (long double k) { return Point(x*k, y*k, z*k); }
    
    long double sqlen() { return x*x + y*y + z*z; }
    long double len() { return sqrt(sqlen()); }
    
    Point normalize() { long double l = len(); return Point(x/l, y/l, z/l); }
    
    void print() { cout << x << ' ' << y << ' ' << z << endl; }
} A, B;

char name[100111];
vector<string> res;

#define sqr(x) ((x)*(x))

bool outside(Point P, Point A, Point B) {
    if (P.x < min(A.x, B.x) || P.x > max(A.x, B.x)) return true;
    if (P.y < min(A.y, B.y) || P.y > max(A.y, B.y)) return true;
    if (P.z < min(A.z, B.z) || P.z > max(A.z, B.z)) return true;
    return false;
}

bool check() {
    long double a = sqr(B.x - A.x) + sqr(B.y - A.y) + sqr(B.z - A.z);
    long double b = A.x * (B.x - A.x) + A.y * (B.y - A.y) + A.z * (B.z - A.z);
    long double k = - b / a;
    
    if (k < 0 || k > 1) return true;
    
    Point P = A + (B - A) * k;
    
    long double mindist = r * 2;
    if (outside(P, A, B)) {
        mindist = min(A.len(), B.len());
    }
    else mindist = P.len();
    return mindist > r + 1e-6;
}

int main() {
    cin >> r; r /= 2.0;
    long double height; cin >> height;
    long double theta, gamma; cin >> theta >> gamma;
    A = Point(theta, gamma);
    
    A = A + A.normalize() * height;
    while (cin >> height >> theta >> gamma) {
        char c; scanf("%c", &c);
        B = Point(theta, gamma);
        B = B + B.normalize() * height;
        
        gets(name);
        if (check()) res.PB(string(name));
    }
    sort(res.begin(), res.end());
    REP(i,res.size()) cout << res[i] << endl;
    return 0;
}
