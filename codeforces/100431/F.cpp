#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9) + 7;

int start[333];
long long f[333][333], c[333][333];

long long dp(int l, int r)
{
  if (l >= r) return 1;
  long long &res = f[l][r];
  if (res >= 0) return res;
  res = 0;

  if (!start[l + 1])
    res += dp(l + 1, r);

  for (int i = l + 1; i <= r; i++)
    if (start[i] && (i == r || !start[i + 1]))
      res = (res + dp(l, i - 1) * dp(i + 1, r) % BASE * c[r - l][i - l]) % BASE;

  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("monotonic.in", "r", stdin);
  freopen("monotonic.out", "w", stdout);

  int n, k, x;
  cin >> n >> k;
  for (int i = 1, cur = 1; i <= k; i++)
  {
    start[cur] = 1;
    cin >> x;
    cur += x;
  }

  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= i; j++)
      c[i][j] = j ? (c[i - 1][j] + c[i - 1][j - 1]) % BASE : 1;

  memset(f, -1, sizeof f);
  cout << dp(1, n) << endl;
}