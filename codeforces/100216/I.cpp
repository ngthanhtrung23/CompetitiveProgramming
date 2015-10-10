#include <bits/stdc++.h>
using namespace std;

long long f[2][1 << 8][1 << 8];
int m, n;

int bit(int x)
{
  return 1 << x;
}

int solidMask(int mask)
{
  int prev = -1, res = 0;
  mask = bit(n) | (bit(n) - 1 - mask);
  for (int i = 0; i <= n; i++)
    if (mask & bit(i))
    {
      if ((i - prev - 1) % 2) return -1;
      for (int j = prev + 1; j < i; j += 2)
        res |= bit(j);
      prev = i;
    }
  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("solid.in", "r", stdin);
  freopen("solid.out", "w", stdout);

  cin >> n >> m;
  for (int mask = 0; mask < bit(n); mask++)
  {
    int solid = solidMask(mask);
    if (solid < 0) continue;
    f[0][mask][solid] = 1;
  }

  int z = 0;
  for (int i = 1; i < m; i++)
    for (int j = 0; j < n; j++)
    {
      z ^= 1;
      memset(f[z], 0, sizeof f[z]);
      for (int mask = 0; mask < bit(n); mask++)
        for (int solid = 0; solid < bit(n - 1); solid++)
        {
          long long &ways = f[z ^ 1][mask][solid];
          if (!ways) continue;
          if (!j && mask == bit(n) - 1) continue;

          if (mask & bit(0))
          {
            f[z][mask >> 1][solid] += ways;
            if (j && !(mask & bit(n - 1)))
              f[z][(mask >> 1) | bit(n - 1) | bit(n - 2)][solid | bit(j - 1)] += ways;
          }
          else f[z][mask >> 1 | bit(n - 1)][solid] += ways;
        }
    }

  cout << f[z][bit(n) - 1][bit(n - 1) - 1] << endl;
}