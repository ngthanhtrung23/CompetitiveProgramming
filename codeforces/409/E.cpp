#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

double x;
void solve() {
    int prod = 1000111;
    int savea = 10, saveh = 10;
    FOR(a,1,10) FOR(h,1,10) {
        double area = a * h;
        double hyp = sqrt(4*h*h + a*a);
        double r = area / hyp;

        if (abs(r - x) <= 1e-6) {
            cout << a << ' ' << h << endl;
            return ;
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> x) {
        solve();
    }
    return 0;
}
