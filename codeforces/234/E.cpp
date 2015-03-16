
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

int n, x, a, b, c;

int next_rand() {
    int y = (x * a + b) % c;
    x = y;
    return x;
}

pair<int,string> teams[111];

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    while (cin >> n) {
        cin >> x >> a >> b >> c;
        FOR(i,1,n) cin >> teams[i].second >> teams[i].first;
        sort(teams+1, teams+n+1);
        reverse(teams+1, teams+n+1);

        vector<string> bask[4];
        int m = n / 4;
        FOR(i,1,n) {
            bask[(i - 1) / m].push_back(teams[i].second);
        }
//        REP(t,4) PR0(bask[t], bask[t].size());

        REP(turn,m) {
            cout << "Group " << (char) ('A' + turn) << ":\n";
            int s = bask[0].size();
            int u = next_rand() % s;
            int v = next_rand() % s;
            int w = next_rand() % s;
            int z = next_rand() % s;

            cout << bask[0][u] << endl << bask[1][v] << endl << bask[2][w] << endl << bask[3][z] << endl;

            bask[0].erase(bask[0].begin() + u);
            bask[1].erase(bask[1].begin() + v);
            bask[2].erase(bask[2].begin() + w);
            bask[3].erase(bask[3].begin() + z);
        }
    }
    return 0;
}
