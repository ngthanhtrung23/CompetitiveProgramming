
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 611;

int nTooth, nGum, p;
vector< pair<int,int> > gum[MN];
int f[MN][MN], tr[MN][MN];

int gumCost[MN];
vector<int> res;

void trace(int i, int j) {
    if (i == 0) return ;
    int cur = tr[i][j];

    REP(x,cur) res.push_back(gum[i][x].second);

    trace(i-1, j - cur);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nTooth >> nGum >> p) {
        FOR(i,1,nGum) cin >> gumCost[i];
        FOR(i,1,nTooth) {
            int pos, c;
            cin >> c >> pos;

            gum[pos].push_back(make_pair(c, i));
        }
        FOR(i,1,nGum) {
            sort(gum[i].begin(), gum[i].end());
            REP(j,SZ(gum[i])) if (j) {
                gum[i][j].first += gum[i][j-1].first;
            }

//            REP(j,SZ(gum[i])) cout << gum[i][j].first << ' ' << gum[i][j].second << "    ";
//            cout << endl;
        }

        FOR(i,0,nGum) FOR(j,0,nTooth) f[i][j] = p + 1;
        f[0][0] = 0;
        FOR(i,1,nGum) {
            FOR(j,0,nTooth) {
                // do not cure any
                f[i][j] = f[i-1][j];
                tr[i][j] = 0;

                // cure some tooth here
                FOR(cur,1,min(SZ(gum[i]), j)) {
                    int t = f[i-1][j - cur] + gumCost[i] + gum[i][cur-1].first;
                    if (t < f[i][j]) {
                        f[i][j] = t;
                        tr[i][j] = cur;
                    }
                }
            }
        }
        int savei = 0, savej = 0;
        FOR(i,1,nGum) FOR(j,0,nTooth) if (f[i][j] <= p && j > savej) {
            savej = j;
            savei = i;
        }
        res.clear();
        cout << savej << endl;
        trace(savei, savej);
        for(int x : res) cout << x << ' '; cout << endl;
    }
}
