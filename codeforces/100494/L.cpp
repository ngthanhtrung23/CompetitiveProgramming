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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

multiset< pair<pair<int,int>,int> > events;

int getTime() {
    int h, m; scanf("%d:%d", &h, &m);
    return h * 60 + m;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; scanf("%d", &ntest);
    FOR(test,1,ntest) {
        int T; scanf("%d", &T);

        int nA, nB;
        scanf("%d%d", &nA, &nB);
        events.clear();

        FOR(i,1,nA) {
            int from = getTime(), to = getTime();
            events.insert(make_pair(make_pair(from, to), 1));
        }
        FOR(i,1,nB) {
            int from = getTime(), to = getTime();
            events.insert(make_pair(make_pair(from, to), 2));
        }

        int fromA = 0, fromB = 0;
        int hasA = 0, hasB = 0;
        while (!events.empty()) {
            pair< pair<int,int>, int> cur = *events.begin();

            events.erase(events.begin());

            if (cur.second == 1) {
                if (hasA) --hasA;
                else ++fromA;

                events.insert(make_pair(make_pair(cur.first.second + T, -1), -2));
            } else if (cur.second == 2) {
                if (hasB) --hasB;
                else ++fromB;

                events.insert(make_pair(make_pair(cur.first.second + T, -1), -1));
            } else if (cur.second == -1) {
                ++hasA;
            } else if (cur.second == -2) {
                ++hasB;
            } else {
            }
        }
        printf("Case #%d: %d %d\n", test, fromA, fromB);
    }
    return 0;
}
