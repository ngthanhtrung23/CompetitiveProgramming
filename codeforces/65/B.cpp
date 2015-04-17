
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int a[1011], b[1011];

int get(int from, int least) {
    int res = -1;
    stringstream ss; ss << from;
    string s = ss.str();

    REP(pos,4) REP(to,10) {
        string cur = s;
        cur[pos] = '0' + to;

        stringstream ss(cur);
        int x; ss >> x;
        if (x < least) continue;
        if (x > 2011) continue;

        if (res < 0) res = x;
        else res = min(res, x);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        int last = 1000;
        bool ok = true;
        FOR(i,1,n) {
            b[i] = get(a[i], last);
            last = b[i];
            if (b[i] < 0) ok = false;
        }
        if (!ok) cout << "No solution" << endl;
        else {
            FOR(i,1,n) cout << b[i] << endl;
        }
    }
    return 0;
}
