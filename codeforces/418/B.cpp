#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

struct People {
    int mask;
    long long money, nMonitor;
} people[111];
bool operator < (const People &a, const People &b) {
    return a.nMonitor < b.nMonitor;
}
int nPeople, nProb, monitorCost;
long long f[2][TWO(20)];

void update(long long &x, long long val) {
    if (val < 0) return ;
    if (x < 0) x = val;
    else x = min(x, val);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nPeople >> nProb >> monitorCost) {
        FOR(i,1,nPeople) {
            people[i].mask = 0;
            int can;
            cin >> people[i].money >> people[i].nMonitor >> can;
            while (can--) {
                int u; cin >> u;
                people[i].mask |= TWO(u-1);
            }
        }
        sort(people+1, people+nPeople+1);
        memset(f, -1, sizeof f);
        f[0][0] = 0;
        long long cur = 0, res = -1;
        FOR(i,1,nPeople) {
            REP(mask,TWO(nProb))
                if (f[cur][mask] >= 0) {
                    update(f[1-cur][mask | people[i].mask], f[cur][mask] + people[i].money);
                    update(f[1-cur][mask], f[cur][mask]);
                }
            int mask = TWO(nProb) - 1;
            if (f[1-cur][mask] >= 0) {
                update(res, f[1-cur][mask] + people[i].nMonitor * monitorCost);
            }
            cur = 1 - cur;
        }
        cout << res << endl;
    }
    return 0;
}
