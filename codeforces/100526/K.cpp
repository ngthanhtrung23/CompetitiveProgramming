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

int n, m, savel;
string ans[33];
int correct[33], a_mask[33];
map< pair<long long, long long>, string > mp;
map< pair<long long, long long>, int > cnt;
long long res = 0;
string solution;

string cur;
int cur_mask;

#define hash hash_
pair<long long, long long> hash(vector<int> x) {
    long long h1 = 0, h2 = 0;
    REP(i,x.size()) {
        h1 = h1 * 31 + x[i];
        h2 = (h2 * 31 + x[i]) % 1000000007;
    }
    return make_pair(h1, h2);
}

void gen(int l, int r, int turn) {
    if (l > r) {
        vector<int> diff; diff.resize(n);
        FOR(i,1,n) {
            diff[i-1] = __builtin_popcount(cur_mask ^ a_mask[i]);
        }

        if (turn == 1) {
            mp[hash(diff)] = cur;
            cnt[hash(diff)] += 1;
        }
        else {
            REP(i,n) diff[i] = m - correct[i+1] - diff[i];
            res += cnt[hash(diff)];
            if (cnt[hash(diff)] > 0 && res == 1) {
                solution = mp[hash(diff)] + cur;
            }
        }
        return ;
    }
    REP(x,2) {
        cur[l-savel] = '0' + x;
        cur_mask = cur_mask * 2 + x;
        gen(l+1, r, turn);
        cur_mask /= 2;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> m;
        FOR(i,1,n) cin >> ans[i] >> correct[i];

        int fromL = 0, toL = (m - 1) / 2;
        int fromR = toL + 1, toR = m - 1;

        mp.clear();
        cnt.clear();
        res = 0;

        cur = ""; FOR(i,fromL, toL) cur += " "; cur_mask = 0;
        FOR(i,1,n) {
            a_mask[i] = 0;
            FOR(x,fromL,toL) {
                a_mask[i] = a_mask[i] * 2 + (ans[i][x] - '0');
            }
            // cout << a_mask[i] << ' ' << ans[i] << endl;
        }
        savel = fromL; gen(fromL, toL, 1);

        cur = ""; FOR(i,fromR, toR) cur += " "; cur_mask = 0;
        FOR(i,1,n) {
            a_mask[i] = 0;
            FOR(x,fromR,toR) {
                a_mask[i] = a_mask[i] * 2 + (ans[i][x] - '0');
            }
            // cout << a_mask[i] << ' ' << ans[i] << endl;
        }
        savel = fromR; gen(fromR, toR, 2);

        if (res != 1) cout << res << " solutions\n";
        else cout << solution << "\n";
    }
    return 0;
}
