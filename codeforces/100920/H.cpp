#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
const int MV = 2000111;
pair<int,int> a[MN];
int n;
int cntX[MV], cntY[MV], used[MN], xGroupId[MV], yGroupId[MV];
map< int, int > id[MV];
int nGroup;
vector<int> groups[MN];

void init() {
    memset(cntX, 0, sizeof cntX);
    memset(cntY, 0, sizeof cntY);
    memset(used, 0, sizeof used);

    memset(xGroupId, 0, sizeof xGroupId);
    memset(yGroupId, 0, sizeof yGroupId);

    nGroup = 0;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d", &n) == 1) {
        init();
        FOR(i,1,n) {
            scanf("%d%d", &a[i].first, &a[i].second);
            a[i].first += 1000000;
            a[i].second += 1000000;

            cntX[a[i].first]++;
            cntY[a[i].second]++;
        }

        // assign points to groups using X-coordinates
        FOR(i,1,n) {
            int x = a[i].first;
            if (cntX[x] <= 333) {
                int g = xGroupId[x];
                if (g == 0) {
                    xGroupId[x] = ++nGroup;
                    groups[nGroup].clear();
                    g = xGroupId[x];
                }
                used[i] = g;
                id[a[i].first][a[i].second] = g;
                groups[g].push_back(i);
            }
        }
        // assign remaining points to groups using Y-coordinates
        FOR(i,1,n) if (!used[i]) {
            int y = a[i].second;
            int g = yGroupId[y];
            if (g == 0) {
                yGroupId[y] = ++nGroup;
                groups[nGroup].clear();
                g = yGroupId[y];
            }
            used[i] = g;
            id[a[i].first][a[i].second] = g;
            groups[g].push_back(i);
        }

        ll res = 0;
        ll duplicated = 0;
        // for each group
        FOR(g,1,nGroup) {
//            PR0(groups[g], SZ(groups[g]));
            // count number of squares with 2 vertices in this group
            REP(id1,SZ(groups[g])) {
                FOR(id2,id1+1,SZ(groups[g])-1) {
                    int i = groups[g][id1], j = groups[g][id2];

                    if (a[i].first == a[j].first) {
                        // same x

                        // left
                        int side = abs(a[i].second - a[j].second);
                        auto u = make_pair(a[i].first - side, a[i].second);
                        auto v = make_pair(a[j].first - side, a[j].second);

                        if (u.first >= 0) {
                            if (id[u.first].count(u.second) && id[v.first].count(v.second)) {
                                if (id[u.first][u.second] == id[v.first][v.second]) ++duplicated;
                                ++res;
                            }
                        }
                        // right
                        u = make_pair(a[i].first + side, a[i].second);
                        v = make_pair(a[j].first + side, a[j].second);
                        if (u.first < MV) {
                            if (id[u.first].count(u.second) && id[v.first].count(v.second)) {
                                if (id[u.first][u.second] == id[v.first][v.second]) ++duplicated;
                                ++res;
                            }
                        }
                    }
                    else {
                        // same y

                        // down
                        int side = abs(a[i].first - a[j].first);
                        auto u = make_pair(a[i].first, a[i].second - side);
                        auto v = make_pair(a[j].first, a[j].second - side);

                        if (id[u.first].count(u.second) && id[v.first].count(v.second)) {
                            if (id[u.first][u.second] == id[v.first][v.second]) ++duplicated;
                            ++res;
                        }
                        // up
                        u = make_pair(a[i].first, a[i].second + side);
                        v = make_pair(a[j].first, a[j].second + side);
                        if (id[u.first].count(u.second) && id[v.first].count(v.second)) {
                            if (id[u.first][u.second] == id[v.first][v.second]) ++duplicated;
                            ++res;
                        }
                   }
                }
            }
        }
        cout << res - duplicated / 2 << endl;
    }
}
