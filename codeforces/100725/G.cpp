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

const int MN = 511;

int f[MN][MN], g[MN], a[MN], b[MN], na, nb;
pair<int,int> trace[MN][MN];
int tracej[MN];

void visit(int i, int j) {
    if (!i) return ;

    auto prev = trace[i][j];
    visit(prev.first, prev.second);
    cout << a[i] << ' ';
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("gcis.in", "r", stdin);
    freopen("gcis.out", "w", stdout);

    while (cin >> na) {
        FOR(i,1,na) cin >> a[i];
        cin >> nb;
        FOR(i,1,nb) cin >> b[i];

        FOR(i,0,na) FOR(j,0,nb) f[i][j] = -MN;

        f[0][0] = 0;
        FOR(i,1,na) {
            FOR(ii,0,i) g[ii] = -MN;
            g[0] = 0;
            tracej[0] = 0;

            FOR(j,1,nb) {
                if (a[i] == b[j]) {
                    f[i][j] = 1;
                    trace[i][j] = make_pair(0, 0);

                    FOR(ii,0,i-1) if (a[ii] < a[i]) {
                        if (g[ii] + 1 > f[i][j]) {
                            f[i][j] = g[ii] + 1;
                            trace[i][j] = make_pair(ii, tracej[ii]);
                        }
                    }
                }

                FOR(ii,0,i) {
                    if (f[ii][j] > g[ii]) {
                        g[ii] = f[ii][j];
                        tracej[ii] = j;
                    }
                }
            }
        }
        int res = 0, savei = 0, savej = 0;
        FOR(i,0,na) FOR(j,0,nb) if (f[i][j] > res) {
            res = f[i][j];
            savei = i;
            savej = j;
        }
        cout << res << endl;
        if (res) {
            visit(savei, savej);
        }
        cout << endl;
    }
}

