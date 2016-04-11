#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9) + 7;

int n, m, k, d, a[22][111];

int solve(int mask, int j)
{
  if (d * 2 + 1 >= k)
    return k;
  int bit = __builtin_popcount(mask);
  map <int,int> cnt;
  cnt[k] = 0;
  for (int i = 0; i < m; i++)
    if (mask >> i & 1)
    {
      int from = (a[i][j] - d + k) % k;
      int to = (a[i][j] + d) % k;
      cnt[from]++;
      cnt[to + 1]--;
      if (from > to)
        cnt[0]++;
    }

  int last = 0, res = 0, cur = 0;
  for (auto u : cnt)
  {
    if (cur == bit) res += u.first - last;
    cur += u.second;
    last = u.first;
  }
  return res;
}

int main()
{
  freopen("cifrul.in", "r", stdin);
  freopen("cifrul.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int test;
  cin >> test;
  while (test--)
  {
    cin >> n >> m >> k >> d;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        cin >> a[i][j];

    long long ans = 0;
    for (int mask = 1; mask < 1 << m; mask++)
    {
      long long ways = 1;
      for (int j = 0; j < n; j++)
        ways = ways * solve(mask, j) % BASE;
      if (__builtin_popcount(mask) % 2) ans = (ans + ways) % BASE;
      else ans = (ans - ways + BASE) % BASE;
    }
    cout << ans << endl;
  }
}