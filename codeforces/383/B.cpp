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

const int MN = 100111;
int n, m, cx[MN], sx;
pair<int,int> a[MN];
vector<int> block[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m) {
        FOR(i,1,m) cin >> a[i].first >> a[i].second;
        sx = 0; cx[++sx] = 1; cx[++sx] = n;
        FOR(i,1,m) cx[++sx] = a[i].first;
        sort(cx+1, cx+sx+1);
        sx = unique(cx+1, cx+sx+1) - cx - 1;
        // PR(cx, sx);

        FOR(i,1,sx) block[i].clear();

        FOR(i,1,m) {
            int x = lower_bound(cx+1, cx+sx+1, a[i].first) - cx;
            block[x].push_back(a[i].second);
        }
        FOR(i,1,sx) sort(block[i].begin(), block[i].end());

        set< pair<int, int> > cur;
        if (block[1].empty()) cur.insert(make_pair(1, n));
        else cur.insert(make_pair(1, block[1][0] - 1));

        FOR(t,2,sx) {
            if (cur.empty()) break;
            // DEBUG(cx[t]);
            // for(auto seg : cur) cout << seg.first << ' ' << seg.second << "   "; cout << endl;

            set< pair<int,int> > next;
            int last = 0;
            if (cx[t] > cx[t-1] + 1) {
                int u = cur.begin()->first;
                cur.clear();
                cur.insert(make_pair(u, n));
            }
            for(auto seg : cur) {
                if (last >= seg.second) continue;
                if (last >= seg.first) {
                    seg.first = last + 1;
                }

                auto it = lower_bound(block[t].begin(), block[t].end(), seg.first);
                while (true) {
                    if (it == block[t].end()) {
                        next.insert(make_pair(seg.first, n));
                        last = n;
                        break;
                    }
                    int u = *it;
                    if (u == seg.first) {
                        ++it;
                        ++seg.first;
                    }
                    else {
                        next.insert(make_pair(seg.first, u - 1));
                        last = u - 1;
                        ++it;
                        seg.first = u + 1;
                    }
                    if (seg.first > seg.second) break;
                }
            }
            cur = next;
            // for(auto seg : cur) cout << seg.first << ' ' << seg.second << "   "; cout << endl;
        }
        bool ok = false;
        for(auto seg : cur) {
            if (seg.first <= n && n <= seg.second) ok = true;
        }

        if (ok) cout << n + n - 2 << endl;
        else cout << -1 << endl;
    }
    return 0;
}

