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

const double PI = acos(-1.0);
const int MN = 100111;

#define SET multiset< pair<int,int> > 

int m, n;
pair<int,int> a[MN], b[MN];
SET s;
bool mark[MN];

int main() {
    while (scanf("%d%d", &m, &n) == 2) {
        s.clear();
        FOR(i,1,m) {
            scanf("%d%d", &a[i].S, &a[i].F);
            s.insert(a[i]);
        }

        int r1 = 0, r2 = 0;
        memset(mark, false, sizeof mark);
        FOR(i,1,n) {
            scanf("%d%d", &b[i].S, &b[i].F);
            SET :: iterator it = s.find(b[i]);
            if (it != s.end()) {
                mark[i] = true;
                ++r1;
                ++r2;
                s.erase(it);
            }
        }
        FOR(i,1,n) if (!mark[i]) {
            SET :: iterator it = s.lower_bound(MP(b[i].F, 0));
            if (it != s.end() && it->F == b[i].F) {
                ++r1;
                s.erase(it);
            }
        }
        cout << r1 << ' ' << r2 << endl;
    }
    return 0;
}
