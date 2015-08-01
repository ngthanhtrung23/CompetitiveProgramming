
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

int nBox, nNo;
ll a[2][1011];

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n, f, b; cin >> n >> f >> b;

        nBox = nNo = 0;
        FOR(i,1,n) {
            int pos, has; cin >> pos >> has;
            if (has == 1) {
                nBox++;
                a[1][nBox] = f + pos;
            }
            else {
                nNo++;
                a[0][nNo] = f - pos;
            }
        }
        sort(a[0]+1, a[0]+nNo+1);
        sort(a[1]+1, a[1]+nBox+1);
        queue< pair<int,ll> > qu; // pos, time
        FORD(i,nBox,1) {
            qu.push(make_pair(a[1][i], 0));
        }
        FORD(i,nNo,1) {
            if (b == 0) break;
            --b;
            qu.push(make_pair(a[0][i], 0));
        }

        ll res = 0;

        while (b > 0 || !qu.empty()) {
            auto cur = qu.front(); qu.pop();
            ll arrive = cur.second + (2*f - cur.first);
            res = max(res, arrive);

            if (b > 0) {
                qu.push(make_pair(0, arrive));
                --b;
            }
        }

        cout << res << endl;
    }
}
