
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

long long lcm(long long a, long long b) {
    long long g = __gcd(a, b);
    return a * b / g;
}
int n, a[211], inCycle[211];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        memset(inCycle, 0, sizeof inCycle);

        long long cycleProd = 1;
        FOR(i,1,n) {
            int u = i;
            int cycle = -1;
            FOR(turn,1,200) {
                u = a[u];
                if (u == i) {
                    cycle = turn;
                    break;
                }
            }
            if (cycle >= 0) cycleProd = lcm(cycleProd, cycle);
            else continue;

            inCycle[i] = 1;
            u = i;
            FOR(turn,1,200) {
                u = a[u];
                inCycle[u] = 1;
                if (u == i) break;
            }
        }
//        PR(inCycle, n);

        long long maxChain = 0;
        FOR(i,1,n) if (!inCycle[i]) {
            int u = i;
            int chain = 0;

            while (!inCycle[u]) {
                u = a[u];
                ++chain;
            }

//            cout << i << ' ' << chain << endl;
            maxChain = max(maxChain, chain - 0LL);
        }
        
        long long res = cycleProd;
        while (res < maxChain) res += cycleProd;
        cout << res << endl;
    }
    return 0;
}

