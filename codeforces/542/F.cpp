
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

vector<int> ls[111];
int n, T, q[1011], t[1011];

int getMax(int depth) {
    if (depth > 15) return n;
    else return 1 << depth;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> T) {
        FOR(i,0,T) ls[i].clear();

        FOR(i,1,n) {
            cin >> t[i] >> q[i];

            ls[T - t[i]].push_back(q[i]);
        }

        multiset<int> last, cur;
        FORD(i,T-1,0) {
            int can = getMax(i);
//            DEBUG(i);
//            PR0(ls[i], ls[i].size());

            cur.clear();
            if (last.size() % 2 == 1) {
                int x = *last.begin(); last.erase(last.begin());
                cur.insert(x);
            }
            while (!last.empty()) {
                int x = *last.begin(); last.erase(last.begin());
                int y = *last.begin(); last.erase(last.begin());
                cur.insert(x + y);
            }

            for(int x : ls[i]) {
                cur.insert(x);
                if (cur.size() > can) cur.erase(cur.begin());
            }
            last = cur;
        }
        int res = 0;
        for(auto x : cur) {
            res += x;
        }
        cout << res << endl;
    }
    return 0;
}
