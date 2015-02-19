
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

struct Room {
    int len, wid, hei;
} rooms[511];

struct Paper {
    int len, wid, price;
} papers[511];

int main() {
    int nRoom, nPaper;
    while (cin >> nRoom) {
        FOR(i,1,nRoom) cin >> rooms[i].len >> rooms[i].wid >> rooms[i].hei;
        cin >> nPaper;
        FOR(i,1,nPaper) cin >> papers[i].len >> papers[i].wid >> papers[i].price;

        ll res = 0;
        FOR(i,1,nRoom) {
            ll best = 1e15;

            int per = (rooms[i].len + rooms[i].wid) * 2;

            FOR(j,1,nPaper) if (papers[j].len >= rooms[i].hei) {
                int width = papers[j].wid * (papers[j].len / rooms[i].hei);
                int need = per / width; if (per % width) ++need;

                best = min(best, papers[j].price * (ll) need);
            }
            res += best;
        }
        cout << res << endl;
    }
    return 0;
}
