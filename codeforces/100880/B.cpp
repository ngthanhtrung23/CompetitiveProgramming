
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

const int MN = 1011;
int x[MN], f[MN][MN][2], g[MN][MN], cost[MN][MN];
int m, n, k;
string a[MN];
string tmp;

int getHorDir(char c) {
    if (c == 'A' || c == 'D') return 0;
    return 1;
}
int getVerDir(char c) {
    if (c == 'A' || c == 'B') return 0;
    return 1;
}

void updateMin(int& x, int val) {
    x = min(x, val);
}

void init(int n) {
    REP(i,n+1) REP(bad,MN) REP(dir,2) f[i][bad][dir] = MN;

    f[0][0][0] = 0;
    FOR(i,0,n-1) FOR(bad,0,i) REP(dir,2) {
        int t = f[i][bad][dir];
        if (t == MN) continue;

        REP(next,2) {
            int t2 = t;
            if (next != x[i+1]) ++t2;

            int bad2 = bad;
            if (dir == 1 && next == 0) ++bad2;

            updateMin(f[i+1][bad2][next], t2);
        }
    }
}

int solve() {
    int nc = 0;
    int mn = max(m, n);
    FOR(row,1,m) {
        FOR(j,1,n) {
            x[j] = getHorDir(a[row][j]);
        }
        init(n);

        ++nc;
        FOR(j,0,mn) {
            cost[nc][j] = MN;
            REP(dir,2)
                updateMin(cost[nc][j], f[n][j][dir]);
        }
    }
    FOR(col,1,n) {
        FOR(i,1,m) {
            x[i] = getVerDir(a[i][col]);
        }
        init(m);

        ++nc;
        FOR(i,0,mn) {
            cost[nc][i] = MN;
            REP(dir,2)
                updateMin(cost[nc][i], f[m][i][dir]);
        }
    }
//    FOR(i,1,nc) {
//        PR0(cost[i], 3);
//    }

    FOR(i,0,k) g[0][i] = 0;
    FOR(i,1,nc) FOR(j,0,k) g[i][j] = 1e9;

    FOR(i,1,nc) {
        FOR(j,0,k) {
            FOR(bad,0,mn) {
                int j2 = j + cost[i][bad];
                if (j2 <= k)
                    updateMin(g[i][j2], g[i-1][j] + bad);
            }
        }
        FOR(j,1,k) updateMin(g[i][j], g[i][j-1]);
    }

    return g[nc][k];
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> m >> n >> k;
        FOR(i,1,m) {
            cin >> tmp;
            a[i] = " " + tmp + " ";
        }
        cout << "Case #" << test << ": " << solve() << endl;
        cerr << test << endl;
    }
}
