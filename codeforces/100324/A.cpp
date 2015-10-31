#include <bits/stdc++.h>
using namespace std;

long long power[20], f[10][2][3][2];
int flag[10][2][3][2], iteration, a[20], len;

long long dp(int i, int l, int r, int dif)
{
  int j = len - 1 - i;
  if (i > j) return l || r < 2;

  long long &res = f[i][l][r][dif];
  if (flag[i][l][r][dif] == iteration)
    return res;

  flag[i][l][r][dif] = iteration;
  res = 0;

  if (i == j)
  {
    for (int x = (i ? 0 : 1); x < 10; x++)
    {
      if (!l && x > a[i]) continue;
      int ll = l | (x < a[i]);
      if (ll || r < 2) res++;
    }
    return res;
  }

  for (int x = (i ? 0 : 1); x < 10; x++)
    if (l || x <= a[i])
      for (int y = 0; y < 10; y++)
      {
        int rr = r;
        if (y < a[j]) rr = 1;
        if (y > a[j]) rr = 2;
        int newDif = dif + (x != y);
        if (newDif <= 1)
          res += dp(i + 1, l | (x < a[i]), rr, newDif);
      }

  return res;
}

long long almostPalin(int len)
{
  if (len == 1) return 9;
  return power[(len - 1) / 2] * 9 * (1 + 9 * (len / 2));
}

long long solve(long long n)
{
  len = 0;
  while (n)
  {
    a[len++] = n % 10;
    n /= 10;
  }
  reverse(a, a + len);

  long long res = 0;
  for (int i = 1; i < len; i++)
    res += almostPalin(i);

  iteration++;
  return res + dp(0, 0, 0, 0);
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("almost.in", "r", stdin);
  freopen("almost.out", "w", stdout);

  for (int i = 0; i <= 18; i++)
    power[i] = i ? power[i - 1] * 10 : 1;

  long long n;
  while (cin >> n, n)
    cout << solve(n) << endl; 
}