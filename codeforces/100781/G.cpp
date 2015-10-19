
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

const int MN = 10111;

int mysqrt[MN];
vector< pair<int,int> > segs[MN];
vector<int> queryAt[MN];
int good[MN];

int res[100111];
int nGobl;
pair<int,int> gobl[100111];

int nCircle;
pair< pair<int,int>, int > circle[20111];

int main() {
    ios :: sync_with_stdio(false);

    FOR(i,1,200) {
        if (i*i < MN) {
            mysqrt[i*i] = i;
        }
    }
    FOR(i,1,MN-1) if (!mysqrt[i]) mysqrt[i] = mysqrt[i-1];

    while (scanf("%d", &nGobl) == 1) {
        FOR(i,1,nGobl) scanf("%d%d", &gobl[i].first, &gobl[i].second);
        scanf("%d", &nCircle);
        FOR(i,1,nCircle) scanf("%d%d%d", &circle[i].first.first, &circle[i].first.second, &circle[i].second);

        REP(i,MN) {
            segs[i].clear();
            queryAt[i].clear();
        }
        FOR(i,1,nGobl) {
            queryAt[ gobl[i].second ].push_back(i);
        }

        FOR(i,1,nCircle) {
            int r = circle[i].second;
            int x = circle[i].first.first;
            int y = circle[i].first.second;

            FOR(dy,-r,r) {
                int yy = y + dy;
                if (yy < 0 || yy >= MN) continue;

                int dx = mysqrt[r*r - dy*dy];
                segs[yy].push_back(make_pair(
                            max(0, x - dx),
                            min(MN-2, x + dx)));
            }
        }

        REP(y,MN) {
            memset(good, 0, sizeof good);

            REP(i,SZ(segs[y])) {
                good[segs[y][i].first]++;
                good[segs[y][i].second+1]--;
            }
            FOR(i,1,MN-1) good[i] += good[i-1];

            REP(i,SZ(queryAt[y])) {
                int id = queryAt[y][i];
                if (good[ gobl[id].first ]) res[id] = 0;
                else res[id] = 1;
            }
        }

        int sum = 0;
        FOR(i,1,nGobl) sum += res[i];
        cout << sum << endl;
    }
}
