#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

struct P
{
    long long x, y;
    P(long long x = 0, long long y = 0) : x(x), y(y) {}

    P operator + (P a) { return P(x+a.x, y+a.y); }
    P operator - (P a) { return P(x-a.x, y-a.y); }

    double len() {
        return sqrt(x*x + y*y);
    }
};

bool operator == (const P &a, const P &b) {
    return a.x == b.x && a.y == b.y;
}

double best;
P A, B, C, D;

void update(P a, P b, P c, P d) {
    if (a == b) return ;
    if (a == c) return ;
    if (a == d) return ;
    if (b == c) return ;
    if (b == d) return ;
    if (c == d) return ;

    double cur = (b - a).len() + (c - b).len() + (d-c).len();

    if (cur > best) {
        best = cur;
        A = a;
        B = b;
        C = c;
        D = d;
    }
}

int X, Y;
bool inside(int x, int y) {
    return x >= 0 && y >= 0 && x <= X && y <= Y;
}

P a[1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> X >> Y) {
        best = 0.0;

        int n = 0;
        REP(x,3) REP(y,3) {
            if (inside(x,y)) a[++n] = P(x,y);
            if (inside(x,Y-y)) a[++n] = P(x,Y-y);
            if (inside(X-x,y)) a[++n] = P(X-x,y);
            if (inside(X-x,Y-y)) a[++n] = P(X-x,Y-y);
        }

        FOR(i,1,n) FOR(j,1,n) FOR(k,1,n) FOR(l,1,n)
            update(a[i], a[j], a[k], a[l]);

        cout << A.x << ' ' << A.y << endl;
        cout << B.x << ' ' << B.y << endl;
        cout << C.x << ' ' << C.y << endl;
        cout << D.x << ' ' << D.y << endl;
    }
    return 0;
}
