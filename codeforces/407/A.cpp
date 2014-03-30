#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

vector< pair<int,int> > ls[1011];

void init() {
    FOR(x,1,1000) FOR(y,1,1000) {
        int a = (int) (round(sqrt(x*x + y*y) + 1e-6));
        if (x*x + y*y == a*a && a <= 1000) {
            // cout << x << ' ' << y << ' ' << a << endl;
            ls[a].push_back(make_pair(x, y));
        }
    }
}

bool good;

void output(int ax, int ay, int bx, int by) {
    good = true;
    cout << "YES\n";
    cout << 0 << ' ' << 0 << endl;
    cout << ax << ' ' << ay << endl;
    cout << bx << ' ' << by << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    init();
    int a, b;
    while (cin >> a >> b) {
        good = false;
        REP(ia,ls[a].size()) REP(ib,ls[b].size()) {
            if (good) break;
            int ax = ls[a][ia].first, ay = ls[a][ia].second;
            int bx = ls[b][ib].first, by = ls[b][ib].second;

            if (ax * bx == ay * by && ay != by) {
                output(ax, ay, -bx, by);
                continue;
            }
            if (ax * bx == ay * by && ax != bx) {
                output(ax, ay, bx, -by);
                continue;
            }
        }
        if (!good) cout << "NO\n";
    }
    return 0;
}
