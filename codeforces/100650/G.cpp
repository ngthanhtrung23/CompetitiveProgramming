
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
int n;
pair<int,int> a[MN];

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> n && n) {
        FOR(i,1,n) cin >> a[i].first >> a[i].second;

        int ln = 0;
        FOR(i,1,n) {
            // pivot at i
            map< pair<int,int>, int> cnt;

            FOR(j,1,n) if (a[j] > a[i]) {
                int dx = a[j].first - a[i].first;
                int dy = a[j].second - a[i].second;

                int g;
                if (dx == 0) g = dy;
                else if (dy == 0) g = dx;
                else g = __gcd(dx, dy);

                dx /= g;
                dy /= g;

                cnt[make_pair(dx, dy)] += 1;
            }
            for(auto p : cnt) {
                ln = max(ln, p.second + 1);
            }
        }
        if (ln < 4) ln = 0;
        cout << "Photo " << ++test << ": " << ln << " points eliminated\n";
    }
    return 0;
}
