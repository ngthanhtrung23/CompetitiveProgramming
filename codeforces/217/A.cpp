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

bool mark[1011];
pair<int,int> a[1011];
int n;
int qu[1011];

void bfs(int u) {
    int first = 1, last = 1;
    qu[1] = u; mark[u] = true;
    
    while (first <= last) {
        int u = qu[first++];
        FOR(v,1,n) if (a[u].F == a[v].F || a[u].S == a[v].S) {
            if (mark[v]) continue;

            mark[v] = true;
            qu[++last] = v;
        }
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d%d", &a[i].F, &a[i].S);
        memset(mark, false, sizeof mark);

        int res = 0;
        FOR(i,1,n) if (!mark[i]) {
            ++res;
            bfs(i);
        }
        printf("%d\n", res - 1);
    }
    return 0;
}
