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

const int MN = 100111;
const int MOD = 1000000007;

string s;
pair<char, string> q[MN];
long long len[11], val[11];
int n;
char tmp[MN];

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1);
    mid = (mid * mid) % MOD;
    if (k & 1) return mid * x % MOD;
    else return mid;
}

int main() {
    while (gets(tmp)) {
        s = string(tmp);
        // DEBUG(s);
        scanf("%d\n", &n);
        FOR(i,1,n) {
            gets(tmp);
            q[i].first = tmp[0];
            q[i].second = string(&tmp[3]);

            // cout << q[i].first << " '" << q[i].second << "'" << endl;
        }

        REP(i,10) {
            len[i] = 1;
            val[i] = i;
        }

        FORD(i,n,1) {
            int u = q[i].first - '0';
            
            int newVal = 0, newLen = 0;

            FORD(x,q[i].second.length()-1,0) {
                int v = q[i].second[x] - '0';
                newVal = (newVal + power(10, newLen) * val[v]) % MOD;
                newLen = (newLen + len[v]) % (MOD - 1);
            }

            val[u] = newVal;
            len[u] = newLen;
            // PR0(val, 10);
            // PR0(len, 10);
        }

        long long res = 0, right = 0;
        FORD(i,s.length()-1,0) {
            int u = s[i] - '0';

            res = (res + val[u] * power(10, right)) % MOD;

            right = (right + len[u]) % (MOD - 1);
        }
        cout << res << endl;
    }
    return 0;
}
