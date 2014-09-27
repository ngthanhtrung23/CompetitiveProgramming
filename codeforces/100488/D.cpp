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

const int MN = 300111;
int a[MN];
map<int,int> cnt;
int n, q;
multiset<int> all;
pair<int,int> queries[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        cnt.clear();
        all.clear();
        
        FOR(i,1,n) {
            ++cnt[a[i]];
            all.insert(cnt[a[i]]);
        }

        cin >> q;
        FOR(i,1,q) cin >> queries[i].first >> queries[i].second;
        if (*all.rbegin() == n) {
            cout << 0 << endl;
            continue;
        }

        bool ok = false;
        FOR(qq,1,q) {
            int i = queries[qq].first, val = queries[qq].second;
            all.erase(all.find(cnt[a[i]]));
            cnt[a[i]]--;

            a[i] = val;
            cnt[a[i]]++;
            all.insert(cnt[a[i]]);

            if (*all.rbegin() == n) {
                ok = true;
                cout << qq << endl;
                break;
            }
        }
        if (!ok) cout << -1 << endl;
    }
    return 0;
}
