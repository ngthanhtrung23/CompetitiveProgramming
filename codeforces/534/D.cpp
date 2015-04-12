
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

multiset<pair<int,int> > s[3];

int n, a[200111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        REP(turn,3) s[turn].clear();

        FOR(i,1,n) {
            cin >> a[i];
            s[a[i] % 3].insert(make_pair(a[i], i));
        }

        bool ok = true;
        vector<int> res;
        int cur = 0;
        REP(turn,n) {
            int need = turn % 3;
            if (s[need].empty()) {
                ok = false;
                break;
            }

            auto it = s[need].begin();
            if (it->first > cur) {
                ok = false;
                break;
            }

            if (s[need].rbegin()->first <= cur) {
                it = s[need].end();
                --it;
            }
            else {
                it = s[need].upper_bound(make_pair(cur+1, 0));
                --it;
            }

            cur = it->first + 1;
            res.push_back(it->second);
            s[need].erase(it);
        }
        if (ok) {
            cout << "Possible" << endl;
            for(int x : res) cout << x << ' ';
            cout << endl;
        }
        else cout << "Impossible" << endl;
    }
    return 0;
}
