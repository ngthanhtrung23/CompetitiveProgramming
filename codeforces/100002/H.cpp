
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

int N, HP_H, MP_H, HP_M, N_M, V, dH, L[111];
int f[2][111][111][11];
int trt[2][111][111][11];
int trh[2][111][111][11];
int trm[2][111][111][11];
int trp[2][111][111][11];
int trx[2][111][111][11];
char trc[2][111][111][11];

pair< pair<int,int>, pair<int,int> >
        get(int isFirst, int hero, int monster, int pos, int c) {

    if (!isFirst) {
        // monster moves
        pos -= min(V, pos - 1);

        // monster attack
        if (pos == 1) {
            int K = monster / HP_M;
            if (monster % HP_M) ++K;
            hero -= K;
            if (hero <= 0) return make_pair(make_pair(-1, -1), make_pair(-1, -1));
        }
    }

    // lightning
    if (c == 0) {
        return make_pair(make_pair(0, hero), make_pair(monster - L[pos], pos));
    }
    if (c == 1) {
        return make_pair(make_pair(0, hero), make_pair(monster, pos));
    }
    if (c == 2) {
        return make_pair(make_pair(0, min(hero + dH, HP_H)), make_pair(monster, pos));
    }
}

void trace(int t, int h, int m, int p) {
    if (trc[t][h][m][p] == ' ') return ;

    trace(trt[t][h][m][p],
          trh[t][h][m][p],
          trm[t][h][m][p],
          trp[t][h][m][p]);
    cout << trc[t][h][m][p];
    if (trc[t][h][m][p] == 'T') {
        cout << ' ' << trx[t][h][m][p];
    }
    cout << '\n';
}
const char moves[3] = {'L', 'T', 'H'};

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("heroes.in", "r", stdin);
    freopen("heroes.out", "w", stdout);
    while (cin >> N >> HP_H >> MP_H >> HP_M >> N_M >> V >> dH) {
        FOR(i,1,N) cin >> L[i];
        
        memset(f, -1, sizeof f);
        memset(trc, ' ', sizeof trc);
        queue<int> qt, qh, qm, qp;
        qt.push(1);
        qh.push(HP_H);
        qm.push(N_M * HP_M);
        qp.push(N);
        f[1][HP_H][N_M * HP_M][N] = 0;

        bool ok = false;
        while (!qt.empty()) {
            int t = qt.front(); qt.pop();
            int h = qh.front(); qh.pop();
            int m = qm.front(); qm.pop();
            int p = qp.front(); qp.pop();

            if (m == 0) {
                ok = true;
                cout << "VICTORIOUS" << endl;
                trace(t, h, m, p);
                cout << endl;
                break;
            }

            if (f[t][h][m][p] >= MP_H) continue;

            REP(c,3) FOR(x,1,N) if (c == 1 || x == N) {
                int tt, hh, mm, pp;
                auto next = get(t, h, m, p, c);
                tt = next.first.first;
                hh = next.first.second;
                mm = next.second.first;
                pp = next.second.second;

                if (c == 1) pp = x;

                if (tt < 0) continue;

                if (f[tt][hh][mm][pp] < 0) {
                    f[tt][hh][mm][pp] = f[t][h][m][p] + 1;
                    trt[tt][hh][mm][pp] = t;
                    trh[tt][hh][mm][pp] = h;
                    trm[tt][hh][mm][pp] = m;
                    trp[tt][hh][mm][pp] = p;
                    trc[tt][hh][mm][pp] = moves[c];
                    trx[tt][hh][mm][pp] = x;

                    qt.push(tt);
                    qh.push(hh);
                    qm.push(mm);
                    qp.push(pp);
                }
            }
        }
        if (!ok) cout << "DEFEATED" << endl;
    }
}
