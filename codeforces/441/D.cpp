#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 3011;

int n, need, a[MN], cycle[MN], cycleSize[MN], nCycle, current;

void init() {
    current = 0;
    nCycle = 0;
    memset(cycle, 0, sizeof cycle);

    FOR(i,1,n)
    if (!cycle[i]) {
        ++nCycle;
        cycleSize[nCycle] = 0;

        int u = i;
        cycle[i] = nCycle;
        while (a[u] != i) {
            cycle[u] = nCycle;
            ++cycleSize[nCycle];
            u = a[u];
        }
        cycle[u] = nCycle;

        current += cycleSize[nCycle];
    }

    // PR(cycle, n);
    // PR(cycleSize, nCycle);
    // DEBUG(current);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        cin >> need;

        vector<int> res; res.clear();

        while (true) {
            // PR(a, n);
            init();
            if (current == need) break;

            if (current < need) {
                FOR(i,2,n)
                if (cycle[i] != cycle[1]) {
                    res.push_back(1);
                    res.push_back(i);
                    swap(a[1], a[i]);
                    break;
                }
            }
            else {
                FOR(i,1,n)
                if (cycleSize[cycle[i]] > 0) {
                    FOR(j,1,n)
                    if (j != i && cycle[j] == cycle[i]) {
                        res.push_back(i);
                        res.push_back(j);
                        swap(a[i], a[j]);
                        break;
                    }
                    break;
                }
            }
        }

        cout << res.size() / 2 << endl;
        REP(i,res.size()) cout << res[i] << ' ';
        cout << endl;
    }
    return 0;
}
