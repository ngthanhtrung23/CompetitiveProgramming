
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

const int MN = 1011;
int n, w[MN], h[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> w[i] >> h[i];

        int res = 1000111000;
        REP(turn,2) {
            int bound = n / 2 - turn;
            FOR(i,1,n) { // max h --> i
                if (turn == 1) swap(w[i], h[i]);
                bool ok = true;
                FOR(j,1,n) if (j != i && h[j] > h[i] && w[j] > h[i]) ok = false;

                if (ok) {
                    int must_lie = 0;
                    int sumw = w[i];
                    vector<int> x;
                    FOR(j,1,n) if (j != i) {
                        if (h[j] > h[i]) { // must lie
                            must_lie++;
                            sumw += h[j];
                        }
                        else if (w[j] > h[i]) { // must stand
                            sumw += w[j];
                        }
                        else {
                            sumw += w[j];
                            if (w[j] >= h[j]) x.push_back(w[j] - h[j]);
                        }
                    }
                    sort(x.begin(), x.end());
                    reverse(x.begin(), x.end());

                    if (must_lie <= bound) {
                        res = min(res, sumw * h[i]);
                    }

                    REP(id,x.size()) {
                        if (must_lie + id + 1 > bound) break;
                        sumw -= x[id];
                        res = min(res, sumw * h[i]);
                    }
                }

                if (turn == 1) swap(w[i], h[i]);
            }
        }
        cout << res << endl;
    }
    return 0;
}
