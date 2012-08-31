#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const long double PI = acos((long double) -1.0);
const int MN = 100111;

int n, a[MN], b[MN], ina[MN], inb[MN];
multiset<int> dist;

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) { scanf("%d", &a[i]); ina[a[i]] = i; }
        FOR(i,1,n) { scanf("%d", &b[i]); inb[b[i]] = i; }

        dist.clear();
        FOR(i,1,n) dist.insert(inb[i] - ina[i]);

        FOR(rot,0,n-1) {
            multiset<int> :: iterator it = dist.lower_bound(rot);
            int res = 1000111000;
            if (it != dist.end()) res = min(res, (*it) - rot);

            if (it != dist.begin()) {
                --it;
                res = min(res, rot - (*it));
            }
            printf("%d\n", res);

            int need = b[rot+1];
            dist.erase(dist.find(inb[need] - ina[need]));

            inb[need] = rot + n + 1;
            dist.insert(inb[need] - ina[need]);
        }
    }
    return 0;
}
