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

multiset<int> wash, dry, fold;
int k, n1, n2, n3, t1, t2, t3;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> k >> n1 >> n2 >> n3 >> t1 >> t2 >> t3) {
        wash.clear(); dry.clear(); fold.clear();
        REP(i,n1) wash.insert(0);
        REP(i,n2) dry.insert(0);
        REP(i,n3) fold.insert(0);

        int res = 0;
        REP(turn,k) {
            int canWash = *wash.begin();
            int canDry = *dry.begin();
            int canFold = *fold.begin();

            canDry = max(canDry, canFold - t2);
            canWash = max(canWash, canDry - t1);

            res = max(res, canWash + t1 + t2 + t3);
            wash.erase(wash.begin()); wash.insert(canWash + t1);
            dry.erase(dry.begin()); dry.insert(canWash + t1 + t2);
            fold.erase(fold.begin()); fold.insert(canWash + t1 + t2 + t3);
        }
        cout << res << endl;
    }
    return 0;
}
