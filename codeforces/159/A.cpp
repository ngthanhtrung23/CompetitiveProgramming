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

vector< pair<string,string> > res;
int n, d;
pair< pair<string,string>, int > a[1011];

int main() {
    ios :: sync_with_stdio(false);
    cin >> n >> d;
    FOR(i,1,n) {
        cin >> a[i].F.F >> a[i].F.S >> a[i].S;
    }

    FOR(i,1,n)
    FOR(j,i+1,n)
        if (a[i].S != a[j].S && a[j].S - a[i].S <= d && a[i].F.F == a[j].F.S && a[i].F.S == a[j].F.F) {
            res.PB(MP(min(a[i].F.F, a[i].F.S), max(a[i].F.F, a[i].F.S)));
        }

    sort(res.begin(), res.end());
    res.resize(unique(res.begin(), res.end()) - res.begin());
    cout << res.size() << endl;
    REP(i,res.size()) {
        printf("%s %s\n", res[i].F.c_str(), res[i].S.c_str());
    }
    return 0;
}
