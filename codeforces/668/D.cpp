#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 1000111;

int n;
struct Q {
    int typ;
    int time;
    int x;
    int res;

    void read() {
        scanf("%d%d%d", &typ, &time, &x);
    }
} q[MN];

int cx[MN], ncx;
int ct[MN], nct;
int bit[MN];
vector<int> queryAt[MN];

void RR() {
    ncx = 0;
    FOR(i,1,n) cx[++ncx] = q[i].x;
    sort(cx+1, cx+ncx+1);
    ncx = unique(cx+1, cx+ncx+1) - cx - 1;

    FOR(i,1,n) {
        q[i].x = lower_bound(cx+1, cx+ncx+1, q[i].x) - cx;
    }
}

void update(int u, int val) {
    for(int x = u; x <= nct; x += x & -x)
        bit[x] += val;
}
int get(int u) {
    int res = 0;
    for(int x = u; x > 0; x -= x & -x)
        res += bit[x];
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) q[i].read();
        RR();

        FOR(i,1,n) queryAt[i].clear();
        FOR(i,1,n) queryAt[ q[i].x ].push_back(i);

        FOR(x,1,ncx) {
            // RR
            nct = 0;
            for(int id : queryAt[x]) {
                ct[++nct] = q[id].time;
            }
            sort(ct+1, ct+nct+1);
            nct = unique(ct+1, ct+nct+1) - ct - 1;
            for(int id : queryAt[x]) {
                q[id].time = lower_bound(ct+1, ct+nct+1, q[id].time) - ct;
            }

            // update BIT
            FOR(i,1,nct) bit[i] = 0;

            // answer queries
            for(int id : queryAt[x]) {
                int t = q[id].time;
                int typ = q[id].typ;
                if (typ == 1) update(t, +1);
                else if (typ == 2) update(t, -1);
                else q[id].res = get(t);
            }
        }

        FOR(i,1,n) if (q[i].typ == 3) printf("%d\n", q[i].res);
        puts("");
    }
}
