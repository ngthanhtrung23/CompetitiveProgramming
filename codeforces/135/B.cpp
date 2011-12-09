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

const double PI = acos(-1.0);

struct Point {
    int x, y;
    Point() {x = y = 0;}
    Point(int x, int y) : x(x), y(y) {}
    
    Point operator - (Point a) { return Point(x - a.x, y - a.y); }
    int len() { return x*x + y*y; }
    int operator * (Point a) { return x * a.x + y * a.y; }
} p[10];

bool mark[10];
int x[10];

bool square2(int a, int b, int c, int d) {
    return ((p[a] - p[b]).len() == (p[b] - p[c]).len())
            && ((p[b] - p[c]).len() == (p[c] - p[d]).len())
            && ((p[c] - p[d]).len() == (p[d] - p[a]).len());
}

bool square(int a, int b, int c, int d) {
    return (square2(a, b, c, d)
        || square2(a, b, d, c)
        || square2(a, c, b, d));
}

bool rect2(int a, int b, int c, int d) {
    return ((p[b] - p[a]) * (p[d] - p[a]) == 0)
            && ((p[c] - p[b]) * (p[a] - p[b]) == 0)
            && ((p[d] - p[c]) * (p[b] - p[c]) == 0);
}

bool rect(int a, int b, int c, int d) {
    return (rect2(a, b, c, d)
        || rect2(a, b, d, c)
        || rect2(a, c, b, d));
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    FOR(i,1,8) scanf("%d %d", &p[i].x, &p[i].y);
    
    FOR(a,1,8)
    FOR(b,a+1,8)
    FOR(c,b+1,8)
    FOR(d,c+1,8) {
        memset(mark, 0, sizeof mark);
        mark[a] = mark[b] = mark[c] = mark[d] = 1;
        int cnt  = 0;
        FOR(i,1,8) if (!mark[i]) {
            x[++cnt] = i;
        }
        
        if (square(a, b, c, d) && rect(a, b, c, d) && rect(x[1], x[2], x[3], x[4])) {
            puts("YES");
            printf("%d %d %d %d\n", a, b, c, d);
            printf("%d %d %d %d\n", x[1], x[2], x[3], x[4]);
            return 0;
        }
    }
    puts("NO");
    return 0;
}
