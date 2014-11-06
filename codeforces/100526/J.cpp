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

string s;
char a[311][311];
int maxu, maxv, minu, minv;

void open(int u, int v) {
    a[u][v] = '.';
    maxv = max(maxv, v);
    maxu = max(maxu, u);
    minu = min(minu, u);
    minv = 150;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    cout << ntest << endl;
    while (ntest--) {
        cin >> s;
        memset(a, '#', sizeof a);
        int u = 150, v = 150;
        int di = 0, dj = 1;
        open(u, v);
        minu = maxu = minv = maxv = 150;
        vector< pair<int,int> > path;
        path.push_back(make_pair(u, v));
        REP(i,s.length()) {
            if (s[i] == 'F') {
                u += di; v += dj;
                open(u, v);
            }
            else if (s[i] == 'L') {
                swap(di, dj); di = -di;
                u += di; v += dj;
                open(u, v);
            }
            else if (s[i] == 'R') {
                swap(di, dj); dj = -dj;
                u += di; v += dj;
                open(u, v);
            }
            else {
                int uu = path[path.size()-2].first;
                int vv = path[path.size()-2].second;
                di = uu - u;
                dj = vv - v;
                u = uu;
                v = vv;
            }
            path.push_back(make_pair(u, v));
        }
        cout << (maxu - minu + 3) << ' ' <<  (maxv - minv + 2) << endl;
        FOR(i,minu-1,maxu+1) {
            FOR(j,minv,maxv+1) cout << a[i][j];
            cout << "\n";
        }
    }
    return 0;
}
