
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

int nActor, nFav, nMovie;
bool isFav[111];
int maxFav[111], minFav[111];

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    while (cin >> nActor >> nFav) {
        memset(isFav, false, sizeof isFav);
        FOR(i,1,nFav) {
            int u; cin >> u;
            isFav[u] = true;
        }
        cin >> nMovie;
        FOR(i,1,nMovie) {
            string tmp; cin >> tmp;
            int x; cin >> x;
            int fav = 0;

            int leftGood = nFav, leftBad = nActor - nFav, unknown = 0;
            while (x--) {
                int u; cin >> u;
                if (u == 0) {
                    ++unknown;
                    continue;
                }
                if (isFav[u]) {
                    leftGood--;
                    fav++;
                }
                else {
                    leftBad--;
                }
            }

            minFav[i] = maxFav[i] = fav;
            // minFav : try putting all other as bad
            if (unknown > leftBad) minFav[i] += unknown - leftBad;

            // maxFav : try putting all other as good
            if (unknown > leftGood) maxFav[i] += leftGood;
            else maxFav[i] += unknown;
        }
//        PR(minFav, nMovie);
//        PR(maxFav, nMovie);

        FOR(i,1,nMovie) {
            bool ok = true;
            FOR(j,1,nMovie) if (i != j && minFav[i] < maxFav[j]) ok = false;
            if (ok) {
                cout << 0 << endl;
                continue;
            }
            ok = false;
            FOR(j,1,nMovie) if (i != j && maxFav[i] < minFav[j]) ok = true;
            if (ok) {
                cout << 1 << endl;
                continue;
            }
            cout << 2 << endl;
        }
    }
    return 0;
}
