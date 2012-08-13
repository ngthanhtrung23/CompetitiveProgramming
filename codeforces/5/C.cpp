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
const int MN = 1000111;

int sum[MN], r[MN], st[MN], top;
char tmp[MN];
vector<int> ls[MN*2];

int main() {
    while (gets(tmp)) {
        int n = strlen(tmp);
        string s = ' ' + string(tmp);

        FOR(i,0,2000000) ls[i].clear();

        sum[0] = 1000000; ls[sum[0]].PB(0);
        FOR(i,1,n) {
            if (s[i] == '(') sum[i] = sum[i-1] + 1;
            else sum[i] = sum[i-1] - 1;
            ls[sum[i]].PB(i);
        }

        top = 0; st[0] = n+1;
        FORD(i,n,0) {
            while (top && sum[st[top]] >= sum[i]) --top;
            r[i] = st[top];
            st[++top] = i;
        }

        int res = 0, cnt = 1;
        FOR(i,0,n-1) {
            int j = r[i] - 1;
            if (j <= i) continue;
            int u, sz = ls[sum[i]].size();
            if (ls[sum[i]][sz-1] <= j) {
                u = ls[sum[i]][sz-1];
            }
            else {
                u = lower_bound(ls[sum[i]].begin(), ls[sum[i]].end(), j+1) - ls[sum[i]].begin();
                if (u == 0) continue;
                u = ls[sum[i]][u-1];
            }
            if (u - i > res) {
                res = u - i;
                cnt = 1;
            }
            else if (u - i == res) {
                ++cnt;
            }
        }
        if (res == 0) cnt = 1;
        printf("%d %d\n", res, cnt);
    }
    return 0;
}
