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

struct Mole {
    int x[4], y[4], a, b;
} moles[11];

int res;

void rotate(int x, int y, int a, int b, int &x_new, int &y_new) {
    x -= a;
    y -= b;

    x_new = -y + a;
    y_new = x + b;
}

pair<long long,long long> pnts[11];
long long len[111];

#define sqr(x) ((x) * (x))
void attempt(int i, int total) {
    if (i == 5) {
        int cnt = 0;
        FOR(u,1,4) FOR(v,u+1,4)
            len[++cnt] = sqr(pnts[u].first - pnts[v].first) + sqr(pnts[u].second - pnts[v].second);

        sort(len+1, len+cnt+1);
        // PR(len, 6);
        if (len[1] > 0 && len[1] == len[4]
                && len[4] * 2 == len[5] && len[5] == len[6]
                ) {
            if (res < 0) res = total;
            else res = min(res, total);
        }
        return ;
    }
    REP(turn,4) {
        pnts[i] = make_pair(moles[i].x[turn], moles[i].y[turn]);
        attempt(i+1, total + turn);
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    int test; cin >> test;
    while (test--) {
        FOR(i,1,4) {
            cin >> moles[i].x[0] >> moles[i].y[0] >> moles[i].a >> moles[i].b;

            FOR(turn,1,3) {
                rotate(moles[i].x[turn-1], moles[i].y[turn-1], moles[i].a, moles[i].b, 
                    moles[i].x[turn], moles[i].y[turn]);
            }
        }

        res = -1;
        attempt(1, 0);
        cout << res << endl;
    }
    return 0;
}