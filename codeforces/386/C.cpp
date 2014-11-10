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

const int MN = 300111;
#define next next_
int next[MN][30];
string s;
int n;
long long res[30];
int cnt[300];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        n = s.length();
        memset(cnt, 0, sizeof cnt);
        int ndiff = 0;
        REP(i,n) {
            if (!cnt[s[i]]) ++ndiff;
            cnt[s[i]]++;
        }

        FOR(c,0,'z'-'a') next[n][c] = n;
        FORD(i,n-1,0) {
            FOR(c,0,'z'-'a') next[i][c] = next[i+1][c];
            next[i][s[i] - 'a'] = i;
        }

        FOR(i,0,n-1) {
            vector<int> cur; cur.resize(26);
            FOR(c,0,'z'-'a') cur[c] = next[i][c];
            sort(cur.begin(), cur.end());
            if (cur.back() != n) cur.push_back(n);

            // DEBUG(i);
            // PR0(cur, cur.size());

            FOR(i,1,cur.size() - 1) {
                res[i] += cur[i] - cur[i-1];
            }
            // PR(res, 4);
        }
        cout << ndiff << endl;
        FOR(i,1,ndiff) {
            cout << res[i] << endl;
        }
        memset(res, 0, sizeof res);
    }
    return 0;
}
