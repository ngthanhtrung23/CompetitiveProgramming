
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

int a[111], b[111];

bool check() {
    int t, n; scanf("%d%d", &t, &n);
    vector< pair<int,int> > cur;
    FOR(i,0,t) cur.push_back(make_pair(i, 1));

    FOR(i,1,n) {
        scanf("%d%d", &a[i], &b[i]);
    }

    FOR(turn,1,n) {
        vector< pair<int,int> > next;

        int gap = 0;
        if (turn > 1) gap = a[turn] - b[turn-1];
        int len = b[turn] - a[turn];

//        for(auto p : cur) cout << p.first << ' ' << p.second << "   "; cout << endl;

        REP(i,SZ(cur)) {
            int p = cur[i].first, f = cur[i].second;

            int to = p + f * len;
            if (to >= 0 && to <= t) {
                next.push_back(make_pair(to, f));
            }

            if (gap > 0) {
                f = -f;
                int to = p + f * len;
                if (to >= 0 && to <= t) {
                    next.push_back(make_pair(to, f));
                }
            }
        }

        sort(next.begin(), next.end());
        next.resize(unique(next.begin(), next.end()) - next.begin());

        cur = next;
//        for(auto p : cur) cout << p.first << ' ' << p.second << "   "; cout << endl;
    }
    return !cur.empty();
}

int main() {
    ios :: sync_with_stdio(false);
    int nFreq;
    while (scanf("%d", &nFreq) == 1) {
        bool can = true;
        FOR(i,1,nFreq) {
            if (!check()) {
                can = false;
            }
        }
        cout << (can ? "possible" : "impossible") << endl;
    }
}
