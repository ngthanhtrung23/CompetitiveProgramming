
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

int n, r, m;
pair<int,int> val[111];
vector<int> dices[22];
long long f[6011], g[6011];
const long long oo = 1000111000111000LL;
int res[111], minSum;
bool hasSol;

int turn = 0;
void attempt(int pos) {
    ++turn; if (turn > 10111) return ;
    if (hasSol) return ;
    if (pos > r) {
        bool can = true;
        FOR(i,1,m)
            if (f[val[i].first] != val[i].second) {
                can = false;
                break;
            }
        if (can) {
            cout << "Final die face values are";
            FOR(i,1,r) cout << ' ' << res[i];
            cout << endl;
            hasSol = true;
        }
        return ;
    }
    FOR(cur,res[pos-1],50) {
        res[pos] = cur;
        FOR(j,0,5000)
            f[j+cur] += g[j];

        bool can = true;
        FOR(i,1,m) {
            if (f[val[i].first] > val[i].second) {
                can = false;
                break;
            }
            if (f[val[i].first] < val[i].second && val[i].first < minSum + cur) {
                can = false;
                break;
            }
        }

        if (can) attempt(pos+1);
        FOR(j,0,5000)
            f[j+cur] -= g[j];
        if (hasSol) return;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n && n) {
        minSum = 0;
        FOR(i,1,n) {
            int t; cin >> t;
            dices[i].clear();
            FOR(tt,1,t) {
                int u; cin >> u;
                dices[i].push_back(u);
            }
            sort(dices[i].begin(), dices[i].end());
//            PR0(dices[i], dices[i].size());
            minSum += dices[i][0];
        }

        memset(f, 0, sizeof f); f[0] = 1;
        memset(g, 0, sizeof g);
        memset(res, 0, sizeof res);
        FOR(i,1,n) {
            FOR(j,0,5000) g[j] = f[j];

            memset(f, 0, sizeof f);
            FOR(j,0,50*i-50)
                for(auto u : dices[i]) {
                    f[j+u] += g[j];
                    if (f[j+u] > oo) f[j+u] = oo;
                }
        }
//        PR(f, 100);

        cin >> r >> m;
        FOR(i,1,m) {
            cin >> val[i].first >> val[i].second;
        }
//        DEBUG(r);

        FOR(j,0,5000) g[j] = f[j];
        memset(f, 0, sizeof f);

        hasSol = false;
        memset(res, 0, sizeof res);
        res[0] = 1;
        turn = 0;
        attempt(1);
        if (!hasSol) cout << "Impossible" << endl;
    }
    return 0;
}

