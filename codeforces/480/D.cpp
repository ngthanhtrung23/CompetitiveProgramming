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

struct Parcel {
    int in, out, w, s, val;
} a[511];

bool operator < (const Parcel &a, const Parcel &b) {
    if (a.in != b.in) return a.in < b.in;
    return a.out > b.out;
}

int f[511][1011], best[1011];
vector<int> endAt[1011];
int n, S;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> S) {
        FOR(i,0,1000) endAt[i].clear();

        a[0].in = 0; a[0].out = 1000;
        a[0].w = 0; a[0].s = S;
        a[0].val = 0;

        FOR(i,1,n) {
            cin >> a[i].in >> a[i].out;
            cin >> a[i].w >> a[i].s >> a[i].val;
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) {
            endAt[a[i].out].push_back(i);
        }

        memset(f, 0, sizeof f);
        FORD(i,n,0) {
            FOR(S,0,a[i].s) {
                FOR(t,a[i].in,a[i].out) best[t] = 0;
                FOR(t,a[i].in,a[i].out) {
                    if (t == a[i].in) best[t] = a[i].val;
                    else best[t] = best[t-1];

                    REP(x,endAt[t].size()) {
                        int j = endAt[t][x];
                        if (j == i) continue;

                        if (S >= a[j].w)
                            best[t] = max(best[t], f[j][min(S - a[j].w, a[j].s)] + best[a[j].in]);
                    }
                }

                f[i][S] = best[a[i].out];
            }
        }
        cout << f[0][S] << endl;
    }
    return 0;
}
