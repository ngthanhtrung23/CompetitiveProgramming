//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int need, n, a[1011], b[1011];

int main() {
  while (cin >> need >> n) {
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) b[i] = a[i];
    
    int ln = 0, nn = 0;
    
    REP(d,2) {
      FOR(i,1,n) a[i] = b[i];
      REP(turn,need) {
        int x = -1, y = -1;
        FOR(i,1,n) if (a[i]) {
          if (d == 0) {
            if (x == -1) x = a[i];
            else x = max(x, a[i]);
          }
          else {
            if (y == -1) y = a[i];
            else y = min(y, a[i]);
          }
        }
        if (d == 0) {
          ln += x;
          FOR(i,1,n) if (a[i] == x) {
            --a[i];
            break;
          }
        }
        else {
          nn += y;
          FOR(i,1,n) if (a[i] == y) {
            --a[i];
            break;
          }
        }
      }
    }
    
    printf("%d %d\n", ln, nn);
  }
  return 0;
}
