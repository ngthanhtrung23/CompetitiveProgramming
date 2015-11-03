
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

const int MN = 100111;

int nCanon, nWall;
long double V;
pair<long double,long double> result[MN];
set< pair<long double,int> > alpha;
pair<long double,long double> wall[MN];

long double PI = acos(-1.0);

long double getY(long double mid, long double x) {
    long double vx = V * cos(mid);
    long double t = x / vx;
    return V * sin(mid) * t - 9.8 * t * t / 2.0;
}

long double read() {
    double x;
    scanf("%lf", &x);
    return x;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &nCanon) == 1) {
        V = read();

        alpha.clear();
        FOR(i,1,nCanon) {
            long double x = read();
            alpha.insert(make_pair(x, i));
        }
        scanf("%d", &nWall);
        FOR(i,1,nWall) {
            wall[i].first = read();
            wall[i].second = read();
        }
        sort(wall+1, wall+nWall+1);

        memset(result, 0, sizeof result);
        FOR(i,1,nWall) {
            long double x = wall[i].first;
            long double y = wall[i].second;

            long double l = 0.0, r = PI / 4; long double res = r;
            REP(turn,70) {
                long double mid = (l + r) / 2.0;
                long double y = getY(mid, x);

                if (y >= 0) {
                    res = mid;
                    r = mid;
                }
                else l = mid;
            }
            long double minAngle = res;

            l = 0.0, r = PI / 4, res = 0;
            REP(turn,70) {
                long double mid = (l + r) / 2.0;
                long double cury = getY(mid, x);

                if (cury <= y) {
                    res = mid;
                    l = mid;
                }
                else r = mid;
            }
            long double maxAngle = res;

            // get all canon that got stuck in this wall
            auto it = alpha.lower_bound(make_pair(minAngle - 1e-9, 0));
            while (it != alpha.end() && it->first <= maxAngle + 1e-9) {
                int id = it->second;
                long double a = it->first;
                result[id] = make_pair(x, getY(a, x));
                alpha.erase(it);

                it = alpha.lower_bound(make_pair(minAngle - 1e-9, 0));
            }
        }
        while (!alpha.empty()) {
            auto it = alpha.begin();
            int id = it->second;
            long double a = it->first;

            long double t = V * sin(a) * 2 / 9.8;
            result[id] = make_pair(V * cos(a) * t, 0);

            alpha.erase(it);
        }
        FOR(id,1,nCanon) printf("%.9f %.9f\n", (double) result[id].first, (double) result[id].second);
    }
}

