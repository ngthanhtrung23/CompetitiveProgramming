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

int n;
#define X first
#define Y second
pair<int,int> a[2011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i].X >> a[i].Y;
        sort(a+1, a+n+1);

        long long res = n * (n-1LL) * (n-2LL) / 6;
        FOR(i,1,n) {
            map< pair<int,int>, int > cnt;
            FOR(j,i+1,n) {
                int dx = a[j].X - a[i].X;
                int dy = a[j].Y - a[i].Y;
                if (dx == 0) dy = 1;
                else if (dy == 0) dx = 1;
                else {
                    if (dy < 0) dy = -dy, dx = -dx;
                    int g = __gcd(abs(dx), abs(dy));
                    dx /= g;
                    dy /= g;
                }

                cnt[make_pair(dx, dy)] += 1;
            }
            for(auto p : cnt) {
                res -= p.second * (p.second - 1LL) / 2LL;
            }
        }
        cout << res << endl;
    }
    return 0;
}

