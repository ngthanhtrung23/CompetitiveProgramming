
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

struct Index {
    int cnt;
    int i;
};

int n, m;
bool operator < (const Index& a, const Index& b) {
    if (a.cnt != b.cnt) return a.cnt < b.cnt;
    int d1 = abs((m + 1) - 2*a.i);
    int d2 = abs((m + 1) - 2*b.i);
    if (d1 != d2) return d1 < d2;
    return a.i < b.i;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        set<Index> s;
        FOR(i,1,m) {
            Index cur;
            cur.cnt = 0;
            cur.i = i;
            s.insert(cur);
        }
        FOR(i,1,n) {
            Index cur = *s.begin();
            s.erase(s.begin());

            cout << cur.i << '\n';
            cur.cnt++;
            s.insert(cur);
        }
    }
    return 0;
}
