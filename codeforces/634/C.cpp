
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;

int n, k, limit[2], q;
int x[2][MN], bit[2][MN];

int get(int t, int u) {
    int res = 0;
    for(int x = u; x > 0; x -= x & -x)
        res += bit[t][x];
    return res;
}
void update(int t, int u, int val) {
    for(int x = u; x < MN; x += x & -x)
        bit[t][x] += val;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> k >> limit[1] >> limit[0] >> q) {
        memset(x, 0, sizeof x);
        memset(bit, 0, sizeof bit);
        FOR(i,1,q) {
            int typ; cin >> typ;
            if (typ == 1) {
                int day, val; cin >> day >> val;
                REP(t,2) {
                    update(t, day, -x[t][day]);
                    x[t][day] += val;
                    if (x[t][day] > limit[t]) x[t][day] = limit[t];
                    update(t, day, x[t][day]);
                }
            }
            else {
                int day; cin >> day;
                int res = get(0, day - 1);
                // 1 --> day: limit[0]
                // day --> day + k - 1: 0
                // day + k --> MAXN: limit[1]
                res += get(1, n) - get(1, day + k - 1);

                cout << res << '\n';
            }
        }
    }
}
