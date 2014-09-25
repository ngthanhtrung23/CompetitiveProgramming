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

#define DEBUG(x) { cout << #x << " = '"; cout << (x) << "'" << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int n;
long long a[111][10111];
int match[111], len[111];
long long code[10111];
int lenCode;
string filename[111];

void init() {
    memset(match, 0, sizeof match);
    memset(len, 0, sizeof len);
    lenCode = 0;
}

#define hash hash_
long long hash(const string &s) {
    long long res = 0;
    REP(i,s.length()) {
        res = res * 301 + s[i];
    }
    return res;
}

char res[311];
string compress(string s) {
    memset(res, 0, sizeof res);
    int cur = 0;
    REP(i,s.length()) {
        if (s[i] == ' ') {
            if (!cur || res[cur-1] == ' ') continue;
            else res[cur++] = s[i];
        } else {
            res[cur++] = s[i];
        }
    }
    if (res[cur-1] == ' ') res[cur-1] = 0;
    return string(res);
}

char tmp[100111];
long long power[10111];
const long long B = 1000000007LL;

bool check(int l) {
    power[0] = 1;
    FOR(i,1,10000) power[i] = power[i-1] * B;

    set< long long > s;
    long long curHash = 0;
    int savep = 0;
    // DEBUG(l);
    // PR(code, lenCode);

    FORD(to,lenCode,1) {
        int from = to - l + 1;
        if (from < 1) break;

        if (to == lenCode) {
            for(int i = from, p = 0; i <= to; ++i, ++p) {
                curHash += code[i] * power[p];
                savep = p;
            }
        } else {
            curHash -= code[to+1] * power[savep];
            curHash *= B;
            curHash += code[from];
        }

        // DEBUG(curHash);

        s.insert(curHash);
    }

    bool res = false;
    FOR(turn,1,n) {
        // PR(a[turn], len[turn]);
        curHash = 0;
        FORD(to,len[turn],1) {
            int from = to - l + 1;
            if (from < 1) break;

            if (to == len[turn]) {
                for(int i = from, p = 0; i <= to; ++i, ++p) {
                    curHash += a[turn][i] * power[p];
                }
            } else {
                curHash -= a[turn][to+1] * power[savep];
                curHash *= B;
                curHash += a[turn][from];
            }

            // DEBUG(curHash);

            if (s.count(curHash)) {
                match[turn] = l;
                res = true;
                break;
            }
        }
    }
    return res;
}

int solve() {
    int l = 1, r = lenCode, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d\n", &n) == 1) {
        init();
        FOR(i,1,n) {
            gets(tmp);
            filename[i] = string(tmp);
            // DEBUG(filename[i]);
            len[i] = 0;

            string s;
            while (true) {
                gets(tmp);
                s = string(tmp);
                s = compress(s);
                if (s == "") continue;
                if (s == "***END***") break;

                // DEBUG(s);
                a[i][++len[i]] = hash(s);
            }
        }

        while (true) {
            gets(tmp);
            string s = string(tmp);
            s = compress(s);

            if (s == "") continue;
            if (s == "***END***") break;

            // DEBUG(s);
            code[++lenCode] = hash(s);
        }

        // PR(code, lenCode);
        // FOR(i,1,n) {
            // PR(a[i], len[i]);
        // }

        int res = solve();

        cout << res;
        if (res) {
            FOR(i,1,n) if (match[i] == res) {
                cout << ' ' << filename[i];
            }
        }
        cout << endl;
    }
    return 0;
}
