
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

vector<int> x[100111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,100*1000) x[i].clear();
        FOR(i,1,n) {
            int a; cin >> a;
            x[a].push_back(i);
        }
        vector< pair<int,int> > res;
        FOR(i,1,100*1000) if (!x[i].empty()) {
            if (x[i].size() == 1) res.push_back(make_pair(i, 0));
            else {
                int d = x[i][1] - x[i][0];
                bool ok = true;
                FOR(t,2,x[i].size()-1)
                    if (x[i][t] - x[i][t-1] != d) {
                        ok = false;
                        break;
                    }
                if (ok) res.push_back(make_pair(i, d));
            }
        }
        cout << res.size() << '\n';
        for(auto p : res) cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}
