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

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

map<string, multiset<string> > mp;
string need, a[111];
int n;

void add(const string &a, const string &b) {
    // cout << a << " --> " << b << "." << endl;
    mp[a].insert(b);
}

int f[111];

void update(int &x, const int k) {
    x = min(x, k);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        mp.clear();
        FOR(i,1,n) cin >> a[i];
        cin >> need;

        FOR(i,1,n) {
            REP(x,a[i].length()+1) {
                string cur = a[i].substr(0, x);
                add(cur, a[i]);
            }
        }

        int lneed = need.length();
        FOR(i,0,lneed) f[i] = i;

        FOR(i,0,lneed-1) {
            update(f[i+1], f[i] + 1);

            string cur = need.substr(0, i);
            int pos = 0;
            for(__typeof(mp[cur].begin()) it = mp[cur].begin(); it != mp[cur].end(); ++it) {
                ++pos;
                string next = *it;
                int lnext = next.length();
                if (lnext > lneed || next != need.substr(0, lnext)) continue;

                update(f[lnext], f[i] + pos);
            }
        }

        cout << f[lneed] + 1 << endl;
    }
    return 0;
}
