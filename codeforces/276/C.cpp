
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <map>
#include <queue>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <sstream>

#define FOR(i, a, b) for(int i=(a), _b=(b); i<=_b; i++)
#define DOW(i, a, b) for(int i=(a), _b=(b); i>=_b; i--)
#define REP(i, b) for(int i=0; i<b; i++)
#define PB push_back

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

#define MAXN 50111

using namespace std;

const int MN = 200111;

int n, q, a[MN], cnt[MN];

int main() {
  ios::sync_with_stdio(0);
  while (cin >> n >> q) {
      FOR(i,1,n) cin >> a[i];
      memset(cnt, 0, sizeof cnt);
      FOR(i,1,q) {
          int u, v; cin >> u >> v;
          cnt[u]++;
          cnt[v+1]--;
      }
      FOR(i,1,n) cnt[i] += cnt[i-1];
      sort(a+1, a+n+1);
      sort(cnt+1, cnt+n+1);
      long long res = 0;
      FOR(i,1,n) res += cnt[i] * (long long) a[i];
      cout << res << endl;
  }
  return 0;
}
