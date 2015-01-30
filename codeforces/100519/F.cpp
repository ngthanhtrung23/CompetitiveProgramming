#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    
    void read() { cin >> x >> y; }
    double len() { return sqrt(x*x + y*y); }
};

int ccw(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    long long t = b.x * c.y - b.y * c.x;
    if (t == 0) return 0;
    else if (t < 0) return -1;
    else return 1;
}

int get(string t) {
    int a, b;
    REP(i,t.length()) if (t[i] == ':') t[i] = ' ';
    stringstream ss(t);

    ss >> a >> b;
    return a * 60 + b;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    Point A, B, C;
    while (cin >> A.x >> A.y) {
        B.read(); C.read();
        double D, V, W;
        cin >> D >> V;
        string T, F;
        cin >> T >> F;
        cin >> W;

        V /= 60;
        W /= 60;

        double alex = (C - A).len() / V + D + (B - C).len() / V;
        double dmitry = get(T) - 9 * 60 + get(F);
        double petr = (B - A).len() / W;
        if (ccw(A, B, C) == 0) petr += D;

        if (alex < dmitry && alex < petr) cout << "Alex";
        else if (petr < dmitry) cout << "Petr";
        else cout << "Dmitry";
        cout << endl;
    }
    return 0;
}