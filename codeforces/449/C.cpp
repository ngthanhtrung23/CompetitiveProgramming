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

int n;
bool used[100111], sieve[100111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        memset(sieve, false, sizeof sieve);
        memset(used, false, sizeof used);

        vector< pair<int,int> > res;
        for(int i = 3; i < n; ++i)
            if (!sieve[i] && i % 2) {
                vector<int> cur;
                for(int j = i; j <= n; j += i) {
                    sieve[j] = false;
                    if (!used[j]) cur.push_back(j);
                }
                if (SZ(cur) == 1) continue;
                if (SZ(cur) % 2 == 1) {
                    cur.erase(cur.begin() + 1);
                }
                for(int i = 0; i < SZ(cur) - 1; i += 2) {
                    res.push_back(make_pair(cur[i], cur[i+1]));
                    used[cur[i]] = true;
                    used[cur[i+1]] = true;
                }
            }

        vector<int> cur;
        for(int i = 2; i <= n; i += 2)
            if (!used[i]) {
                cur.push_back(i);
            }
        for(int i = 0; i < (int) SZ(cur) - 1; i += 2)
            res.push_back(make_pair(cur[i], cur[i+1]));

        cout << res.size() << "\n";
        REP(i,res.size())
            cout << res[i].first << ' ' << res[i].second << "\n";
    }
    return 0;
}
