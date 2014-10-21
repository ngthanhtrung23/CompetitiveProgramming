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

const double PI = acos(-1.0);
const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int m, n;
char c, a[111][111];
bool mark[300];

int main() {
    while (cin >> m >> n >> c) {
        memset(a, 0, sizeof a);
        memset(mark, false, sizeof mark);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        FOR(i,1,m) FOR(j,1,n) {
            bool ok = false;
            REP(dir,4) {
                if (a[i+di[dir]][j+dj[dir]] == c) {
                    ok = true;
                    break;
                }
            }
            if (ok) mark[a[i][j]] = true;
        }

        int res = 0;
        FOR(x,'A','Z') if (mark[x] && x != c) {
            ++res;
        }
        printf("%d\n", res);
    }
    return 0;
}