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

int a[222];

int main() {
  int n, k;
  while (cin >> n >> k) {
    FOR(i,1,2*n+1) cin >> a[i];
    int cnt = 0;
    for(int i = 2; i <= 2*n; i += 2) {
      if (a[i] > a[i-1] + 1 && a[i] > a[i+1] + 1 && cnt < k) {
        ++cnt;
        --a[i];
      }
    }
    FOR(i,1,2*n+1) printf("%d ", a[i]); puts("");
  }
  return 0;
}
