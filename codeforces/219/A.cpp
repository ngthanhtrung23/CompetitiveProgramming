#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const long double PI = acos((long double) -1.0);

int k;
char s[1011];
int cnt[333];

int main() {
    while (scanf("%d\n", &k) == 1) {
        gets(s);
        int l = strlen(s);
        memset(cnt, 0, sizeof cnt);
        REP(i,l) ++cnt[s[i]];

        bool ok = true;
        FOR(c,'a','z') if (cnt[c] % k) ok = false;
        if (!ok) {
            puts("-1");
            continue;
        }
        REP(turn,k) {
            FOR(c,'a','z')
            REP(t,cnt[c] / k) putchar(c);
        }
        puts("");
    }
    return 0;
}