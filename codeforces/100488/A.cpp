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
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

#define double long double

double get(double c, double a, double b) {
    return acos( (a*a + b*b - c*c) / 2 / a / b);
}

double r;
double cal(double a) {
    double x = r / tan(a / 2.0);
    return x * r - r*r*(acos(-1.0) - a) / 2;
}

double area(double a, double b, double c) {
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p-a) * (p-b) * (p-c));
}

int main() {
    ios :: sync_with_stdio(false);
    double AB, BC, CA;
    while (cin >> BC >> CA >> AB >> r) {
        double a = get(BC, CA, AB);
        double b = get(CA, AB, BC);
        double c = get(AB, BC, CA);

        double res = area(AB, BC, CA);
        double S = res;
        res -= (cal(a) + cal(b) + cal(c));

        cout << (fixed) << setprecision(15) << (res / S) << endl;
    }
    return 0;
}

