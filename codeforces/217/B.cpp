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
const int oo = 1000111000;

int turn = 0;
int sum;

int get(int a, int b, bool print = false) {
  if (a == 0 && b == 1) return 0;
  if (a == 1 && b == 0) return 0;
  if (a == 1 && b == 1) {
    if (print) putchar('T');
    turn = 1 - turn;
    ++sum;
    return 0;
  }
  if (a == 0 || b == 0 || a == b) return oo;
  if (a < b) swap(a, b);
  int res = max(0, (a-1) / b - 1);
  sum += (a-1) / b;
  int tmp = (a-1) / b;
  
  a -= tmp * b;
  res += get(a, b, print);
  if (res > oo) res = oo;
  
  if (print) {
    FOR(i,1,tmp) {
      if (turn == 0) putchar('T');
      else putchar('B');
    }
    turn = 1 - turn;
  }
  return res;
}

int main() {
  int n, k;
  while (cin >> n >> k) {
    int res = oo, s = -1;
    FOR(t,1,k) {
      sum = 0;
      int now = get(k, t);
      if (sum != n) continue;
      if (now < res) res = now, s = t;
    }
    if (res == oo) puts("IMPOSSIBLE");
    else {
      printf("%d\n", res);
      get(k, s, true);
      puts("");
    };
  }
  return 0;
}
