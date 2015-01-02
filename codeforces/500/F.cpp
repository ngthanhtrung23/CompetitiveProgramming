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

const int MN = 4011;
const int MQ = 30111;

struct Item {
    int cost, value, time;
} items[MN];
int nItem;

bool operator < (const Item& a, const Item& b) {
    if (a.time != b.time) return a.time < b.time;
    if (a.cost != b.cost) return a.cost < b.cost;
    return a.value < b.value;
}

struct Query {
    int time, value;
    int res;
} queries[MQ];
int nQuery;
vector<int> queryAt[MQ];

int p, f[MN][MN], g[MN][MN];

void init() {
    REP(i,MQ) queryAt[i].clear();
}

void update(int& x, int val) {
    if (x < 0) x = val;
    else x = max(x, val);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> nItem >> p) {
        init();
        FOR(i,1,nItem) cin >> items[i].cost >> items[i].value >> items[i].time;
        sort(items+1, items+nItem+1);
//        FOR(i,1,nItem) cout << items[i].cost << ' ' << items[i].value << endl;

        cin >> nQuery;
        FOR(i,1,nQuery) {
            cin >> queries[i].time >> queries[i].value;
            queryAt[ queries[i].time ].push_back(i);
        }

        vector<int> prev, cur;
        for(int time = p; time <= 20000+p; time += p) {
            int from = time - p + 1, to = time;
            // We will answer all queries with time in the interval [from, to]
            // The items we can use for some queries have time in [from - p, to - p] (prev) or [from, to] (cur)
            // First, we get the list of these items
            cur.clear();
            FOR(i,1,nItem)
                if (from <= items[i].time && items[i].time <= to) {
                    cur.push_back(i);
                }
            // DP:
            // f(i, j) = maximum value if we use i items from cur, and cost <= j
            // g(i, j) = maximum value if we use i items from prev, and cost <= j
            FOR(i,0,cur.size()) memset(f[i], -1, sizeof f[i]);
            FOR(i,0,prev.size()) memset(g[i], -1, sizeof g[i]);

            f[0][0] = 0;
            FOR(i,0,cur.size()-1)
                FOR(j,0,4000)
                    if (f[i][j] >= 0) {
                        update(f[i+1][j], f[i][j]);
                        if (j + items[cur[i]].cost <= 4000)
                            update(f[i+1][j + items[cur[i]].cost], f[i][j] + items[cur[i]].value);
                    }
            g[0][0] = 0;
            FOR(i,0,prev.size()-1)
                FOR(j,0,4000)
                    if (g[i][j] >= 0) {
                        update(g[i+1][j], g[i][j]);
                        if (j + items[prev[i]].cost <= 4000)
                            update(g[i+1][j + items[prev[i]].cost], g[i][j] + items[prev[i]].value);
                    }

            FOR(i,0,cur.size())
                FOR(j,1,4000)
                    f[i][j] = max(f[i][j], f[i][j-1]);
            FOR(i,0,prev.size())
                FOR(j,1,4000)
                    g[i][j] = max(g[i][j], g[i][j-1]);
            // Answer the queries!
            FOR(t,from,to) {
                for(int id : queryAt[t]) {
//                    cout << "Answer query: " << id << endl;
                    int nCur = 0;
                    while (nCur < cur.size() && items[cur[nCur]].time <= queries[id].time) ++nCur;
//                    cout << "cur = "; FOR(i,1,nCur) cout << cur[i-1] << ' '; cout << endl;
                    int nPrev = 0;
                    while (nPrev < prev.size() && items[prev[nPrev]].time >= queries[id].time - p + 1) ++nPrev;
//                    cout << "prev = "; FOR(i,1,nPrev) cout << prev[i-1] << ' '; cout << endl;

                    int res = 0;
                    FOR(left,0,queries[id].value)
                        res = max(res, f[nCur][left] + g[nPrev][queries[id].value - left]);
                    queries[id].res = res;
                }
            }
            prev = cur;
            reverse(prev.begin(), prev.end());
        }
        FOR(i,1,nQuery) cout << queries[i].res << "\n";
    }
    return 0;
}
