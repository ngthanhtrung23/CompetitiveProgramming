#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

int n, k, d[MN];
vector<int> ls[MN];
vector< pair<int,int> > res;

bool solve() {
    res.clear();

    if (ls[0].size() != 1) return false;
    FOR(turn,1,n) {
        int j = 0;
        REP(i,ls[turn-1].size()) {
            int u = ls[turn-1][i], bound;

            if (turn == 1) bound = k;
            else bound = k-1;

            while (bound--) {
                if (j == ls[turn].size()) break;
                int v = ls[turn][j++];
                res.push_back(make_pair(u, v));
            }
        }
        if (j < ls[turn].size()) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k) {
        FOR(i,0,n) ls[i].clear();

        FOR(i,1,n) {
            cin >> d[i];
            ls[d[i]].push_back(i);
        }

        if (!solve()) puts("-1");
        else {
            printf("%d\n", res.size());
            REP(i,res.size()) printf("%d %d\n", res[i].first, res[i].second);
        }
    }
    return 0;
}
