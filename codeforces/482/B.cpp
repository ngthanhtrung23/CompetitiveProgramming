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

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
int n, q, a[MN], need[MN], sumNeed[MN];
struct Query {
    int l, r, k;
} queries[MN];

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> q) {
        FOR(i,1,n) a[i] = 0;
        FOR(i,1,q) cin >> queries[i].l >> queries[i].r >> queries[i].k;


        bool good = true;
        // Consider 1 bit at a time
        REP(bit,30) {
            // If query contain a bit --> mark the segment
            memset(need, 0, sizeof need);
            FOR(i,1,q) if (CONTAIN(queries[i].k, bit)) {
                need[queries[i].l]++;
                need[queries[i].r+1]--;
            }

            // Calculate if each position has the bit
            FOR(i,1,n) need[i] += need[i-1];

            // Calculate sum
            sumNeed[0] = 0;
            FOR(i,1,n) {
                sumNeed[i] = sumNeed[i-1];
                if (need[i] > 0) ++sumNeed[i];
            }

            // If a query does not have the bit on, check the sum
            FOR(i,1,q) if (!CONTAIN(queries[i].k, bit)) {
                if (sumNeed[queries[i].r] - sumNeed[queries[i].l-1] == queries[i].r - queries[i].l + 1) {
                    good = false;
                    break;
                }
            }

            FOR(i,1,n) if (need[i] > 0) a[i] += TWO(bit);
        }
        if (!good) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            FOR(i,1,n) cout << a[i] << ' '; cout << endl;
        }
    }
    return 0;
}
