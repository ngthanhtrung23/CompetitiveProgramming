
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

int f[30111][711], a[30111], n, d, res;

int encode(int x) {
    return 350 + (x - d);
}

int decode(int x) {
    return x - 350 + d;
}

void update(int& x, int val) {
    x = max(x, val);
    res = max(res, val);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> d) {
        memset(a, 0, sizeof a);
        FOR(i,1,n) {
            int pos; cin >> pos;
            a[pos]++;
        }
        res = 0;
        memset(f, -1, sizeof f);
        update(f[d][encode(d)], a[d]);
        FOR(pos,d,30000) FOR(last,1,700) if (f[pos][last] >= 0) {
            int last_d = decode(last);
            FOR(cur_d,max(1, last_d-1),last_d+1) {
                int new_pos = pos + cur_d;
                if (new_pos <= 30000) 
                    update(f[new_pos][encode(cur_d)], f[pos][last] + a[new_pos]);
            }
        }
        cout << res << endl;
    }
    return 0;
}
