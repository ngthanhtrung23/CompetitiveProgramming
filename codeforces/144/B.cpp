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
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    
    Point operator - (Point a) { return Point(x - a.x, y - a.y); }
    
    int sqlen() {
        return x*x + y*y;
    }
} c[1011];
int r[1011], n;

bool warm(Point u) {
    FOR(i,1,n) {
        if ((c[i] - u).sqlen() <= r[i]) return true;
    }
    return false;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    Point a, b;
    scanf("%d%d%d%d", &a.x, &a.y, &b.x, &b.y);
    scanf("%d", &n);
    FOR(i,1,n) {
        scanf("%d%d%d", &c[i].x, &c[i].y, &r[i]);
        r[i] *= r[i];
    }
    
    int res = 0;
    FOR(x, min(a.x,b.x), max(a.x,b.x)) {
        if (!warm(Point(x, a.y))) res++;
        if (!warm(Point(x, b.y))) res++;
    }
    
    FOR(y, min(a.y,b.y) + 1, max(a.y,b.y) - 1) {
        if (!warm(Point(a.x, y))) res++;
        if (!warm(Point(b.x, y))) res++;
    }
    printf("%d", res);
    return 0;
}
