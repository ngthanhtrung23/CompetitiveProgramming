
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 1000111;

struct Cycle {
    vector<int> x;
};

bool operator < (const Cycle& a, const Cycle& b) {
    return SZ(a.x) < SZ(b.x);
}

int n, a[MN], res[MN];
bool visited[MN];

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        vector<Cycle> even;
        memset(visited, 0, sizeof visited);

        FOR(i,1,n) if (!visited[i]) {
            int u = i;
            visited[u] = true;
            Cycle cur;
            cur.x.clear();
            cur.x.push_back(u);

            while (!visited[a[u]]) {
                u = a[u];
                cur.x.push_back(u);
                visited[u] = true;
            }

//            PR0(cur.x, SZ(cur.x));

            if (SZ(cur.x) % 2) {
                // odd cycle: expand it to res
                vector<int> t;
                t.resize(SZ(cur.x));
                int v = 0;
                REP(u,SZ(cur.x)) {
                    t[v] = cur.x[u];
                    v = (v + 2) % SZ(cur.x);
                }

                REP(u,SZ(t)) {
                    int v = (u + 1) % SZ(t);
                    res[t[u]] = t[v];
                }
            }
            else {
                even.push_back(cur);
            }
        }
        if (SZ(even) % 2) {
            cout << -1 << endl;
            continue;
        }
        sort(even.begin(), even.end());
        bool ok = true;
        for(int i = 0; i < SZ(even); i += 2) {
            if (SZ(even[i].x) != SZ(even[i+1].x)) {
                ok = false;
                break;
            }
            vector<int> t;
            REP(j,SZ(even[i].x)) {
                t.push_back(even[i].x[j]);
                t.push_back(even[i+1].x[j]);
            }
            REP(u,SZ(t)) {
                int v = (u + 1) % SZ(t);
                res[t[u]] = t[v];
            }
        }
        if (!ok) {
            cout << -1 << endl;
            continue;
        }
        FOR(i,1,n) printf("%d ", res[i]);
        puts("");
    }
}
