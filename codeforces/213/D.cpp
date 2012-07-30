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
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const long double PI = acos((long double) -1.0);

struct Point {
    long double x, y;
    Point() { x = y = 0; }
    Point(long double x, long double y) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    Point rotate(long double alpha) {
        long double sina = sin(alpha);
        long double cosa = cos(alpha);
        return Point(x*cosa - y*sina, x*sina + y*cosa);
    }

    void print() {
        cout << x << ' ' << y << endl;
    }

    long double sqlen() {
        return x*x + y*y;
    }
    long double len() {
        return sqrt(sqlen());
    }
};

int main() {
    long double size = sqrt(200 - cos(3*PI/5) * 2 * 10 * 10);
    Point A(0,0);
    Point B(size,0);
    Point C = (A - B).rotate(PI/5) + B;
    Point D = (B - A).rotate(-PI/5) + A;
    Point E = (B - C).rotate(PI/5) + C;

    cout << (fixed) << setprecision(10);

    int n; cin >> n;
    cout << n*4 + 1 << endl;
    A.print();
    FOR(i,1,n) (A + Point(size*i, 0)).print();
    FOR(i,0,n-1) (E + Point(size*i, 0)).print();
    FOR(i,0,n-1) {
        (C + Point(size*i,0)).print();
        (D + Point(size*i,0)).print();
    }
    FOR(i,1,n) {
        cout << i << ' ';
        cout << n+i+1 << ' ';
        cout << i+1 << ' ';
        cout << i*2 + n+n+1 << ' ';
        cout << i*2 + n+n << endl;
    }
    cout << 1;
    FOR(i,2,n+1) cout << ' ' << i;
    FORD(i,n,1) {
        cout << ' ' << 2*i+n+n;
        cout << ' ' << i+n+1;
        cout << ' ' << 2*i+n+n+1;
        cout << ' ' << i;
    }
    cout << endl;
    return 0;
}
