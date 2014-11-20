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

string s;
struct Hash {
    long long x, y;
    Hash(long long x = 0, long long y = 0) : x(x), y(y) {}
};

const long long MOD = 1000000007;
Hash operator + (const Hash &a, const Hash &b) {
    return Hash(a.x + b.x, (a.x + b.x) % MOD);
}
Hash operator * (const Hash &a, const Hash &b) {
    return Hash(a.x * b.x, (a.x * b.x) % MOD);
}
bool operator < (const Hash &a, const Hash &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

Hash f[1011][1011];

Hash code(char c) {
    return Hash(c, c);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        int n = s.length();
        FORD(j,n-1,0) FORD(i,j-1,0) {
            int k = i + j + 1;
            if (k >= n) f[i][j] = code(s[j]) * 311 + code(s[i]);
            else f[i][j] = f[j][k] * 311 + code(s[i]);
        }
        set<Hash> s;
        REP(i,n) FOR(j,i+1,n-1)
            s.insert(f[i][j]);

        cout << s.size() << endl;
    }
    return 0;
}
