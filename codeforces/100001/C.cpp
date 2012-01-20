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

const long double PI = acos((long double)-1.0);

struct Point {
    long double x, y;
    Point() {}
    Point(long double x, long double y) : x(x), y(y) {}
    
    Point operator - (Point a) { return Point(x - a.x, y - a.y); }
    
    long double sqlen() { return x*x + y*y; }
} A, B, C;

long double AB, BC, CA, AB2, BC2, CA2;

long double mysqrt(long double x) {
    if (x <= 1e-4) return 0;
    else return sqrt(x);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
    
    AB2 = (B - A).sqlen(); AB = mysqrt(AB2);
    
    BC2 = (C - B).sqlen(); BC = mysqrt(BC2);
    
    CA2 = (A - C).sqlen(); CA = mysqrt(CA2);
    
    long double alpha = acos((AB2 + CA2 - BC2) / 2 / AB / CA);
    long double beta  = acos((BC2 + AB2 - CA2) / 2 / AB / BC);
    long double theta = acos((BC2 + CA2 - AB2) / 2 / BC / CA);
    
    int n = 0;
    FOR(i,3,100) {
        long double a = PI / i;
        if (abs((int) (alpha / a + 1e-4) - alpha / a) <= 1e-4 
         && abs((int) (beta  / a + 1e-4) - beta  / a) <= 1e-4
         && abs((int) (theta / a + 1e-4) - theta / a) <= 1e-4) {
            n = i;
            break;
        }
    }
//    cout << n << endl;
    long double p = (AB + BC + CA) / 2;
    long double S = sqrt(p * (p-AB) * (p - BC) * (p - CA));
//    cout << S << endl;
    long double R = AB * BC * CA / S / 4;
//    cout << R << endl;
    
    cout << (fixed) << setprecision(8) << n * R * R * sin(PI*2 / n) / 2;
    return 0;
}
