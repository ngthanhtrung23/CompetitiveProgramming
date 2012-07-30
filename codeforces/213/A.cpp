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
using namespace std;

const double PI = acos(-1.0);

int n, c[1011], vao[1011], save[1011];
vector<int> ke[1011];
bool mark[1011];

int get(int start) {
    FOR(i,1,n) vao[i] = save[i];
    int done = 0, res = 0;
    memset(mark, false, sizeof mark);

    while (done < n) {
        int inc = 0;
        FOR(i,1,n)
        if (!mark[i] && vao[i] == 0 && c[i] == start) {
            mark[i] = true;
            ++done; ++inc;
            REP(x,ke[i].size()) {
                int u = ke[i][x];
                vao[u]--;
            }
        }

        if (done == n) break;
        if (!inc) {
            if (start == 3) start = 1;
            else ++start;
            ++res;
        }
    }
    return res;
}

int main() {
    scanf("%d", &n); FOR(i,1,n) scanf("%d", &c[i]);
    FOR(i,1,n) {
        scanf("%d", &save[i]);
        FOR(x,1,save[i]) {
            int u; scanf("%d", &u);
            ke[u].PB(i);
        }
    }
    int res = n*4;
    FOR(start,1,3) {
        res = min(res, get(start));
    }
    cout << res + n << endl;
    return 0;
}
