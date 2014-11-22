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

const int MN = 200111;
int X, Y, nFriends, nRest;
int cy[MN], sy;
long long res[MN];

struct Friend {
    int x, y;
} friends[MN];

struct Rest {
    int x, y, id;
} rest[MN];

int nEvent;
struct Event {
    int x, y, typ;
} events[MN];

long long bit[MN];
const long long oo = 1000111000111LL;
#define _(X) ((X) & (-(X)))
void update(int u, long long val) {
    while (u <= sy) {
        bit[u] = min(bit[u], val);
        u += _(u);
    }
}

long long get(int u) {
    long long res = oo;
    while (u > 0) {
        res = min(res, bit[u]);
        u -= _(u);
    }
    return res;
}

void solve() {
    sy = 0;
    FOR(i,1,nFriends) cy[++sy] = friends[i].y;
    FOR(i,1,nRest) cy[++sy] = rest[i].y;

    sort(cy+1, cy+sy+1);
    sy = unique(cy+1, cy+sy+1) - cy - 1;
    FOR(i,1,nFriends) friends[i].y = lower_bound(cy+1, cy+sy+1, friends[i].y) - cy;
    FOR(i,1,nRest) rest[i].y = lower_bound(cy+1, cy+sy+1, rest[i].y) - cy;

    // PR(cy, sy);
    nEvent = 0;
    FOR(i,1,nFriends) {
        ++nEvent;
        events[nEvent].x = friends[i].x;
        events[nEvent].y = friends[i].y;
        events[nEvent].typ = -1;
    }

    FOR(i,1,nRest) {
        ++nEvent;
        events[nEvent].x = rest[i].x;
        events[nEvent].y = rest[i].y;
        events[nEvent].typ = rest[i].id;
    }

    FOR(i,1,sy) bit[i] = oo;
    FOR(i,1,nEvent) {
        if (events[i].typ == -1) {
            update(events[i].y, events[i].x + cy[events[i].y]);
        }
        else {
            long long cur = get(events[i].y);
            if (cur < oo) {
                res[events[i].typ] = max(res[events[i].typ], (events[i].x + cy[events[i].y]) - cur);
            }
        }
    }
    FOR(i,1,nFriends) friends[i].y = cy[friends[i].y];
    FOR(i,1,nRest) rest[i].y = cy[rest[i].y];
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> X >> Y) {
        cin >> nFriends;
        FOR(i,1,nFriends) cin >> friends[i].x >> friends[i].y;
        cin >> nRest;
        FOR(i,1,nRest) {
            cin >> rest[i].x >> rest[i].y;
            rest[i].id = i;
        }
        memset(res, 0, sizeof res);
        REP(t1,2) {
            REP(t2,2) {
                solve();
                FOR(i,1,nFriends) friends[i].y = -friends[i].y;
                FOR(i,1,nRest) rest[i].y = -rest[i].y;
            }
            FOR(i,1,nFriends) friends[i].x = -friends[i].x;
            FOR(i,1,nRest) rest[i].x = -rest[i].x;
        }
        long long best = oo;
        FOR(i,1,nRest) if (res[i] < best) best = res[i];
        cout << best << endl;
        FOR(i,1,nRest) if (res[i] == best) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
