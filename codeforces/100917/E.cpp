#include <bits/stdc++.h>
using namespace std;

long long f[15][1 << 13][15];

int isEmpty(int mask, int pos)
{
  return mask >> pos & 1 ^ 1;
}

int choose(int n, int k)
{
  int res = 1;
  for (int i = 1; i <= k; i++)
    res = res * (n - i + 1);
  return res;
}

int main()
{
  int n, canPut[33][33] = {0}, has[33] = {0}, a[33];
  cin >> n;
  int k = n / 2;
  for (int i = 1; i <= n; i++)
  {
    cin >> a[i];
    if (!a[i]) continue;
    if ((a[i] > k) ^ (i % 2))
    {
      cout << 0 << endl;
      return 0;
    }
    has[a[i]] = i;
  }

  for (int i = 2; i <= n; i += 2)
    if (a[i]) canPut[a[i]][i] = 1;
    else
      for (int j = 1; j <= k; j++)
        if (!has[j])
        {
          canPut[j][i] = 1;
          if (a[i - 1] && a[i - 1] < j * 2)
            canPut[j][i] = 0;
          if (a[i + 1] && a[i + 1] < j * 2)
            canPut[j][i] = 0;
        }

  f[k + 1][0][0] = 1;
  for (int i = k; i; i--)
    for (int mask = 0; mask < 1 << k; mask++)
      for (int available = 0; available <= k + 1; available++)
      {
        long long ways = f[i + 1][mask][available];
        if (!ways) continue;
        for (int pos = 0; pos < k; pos++)
          if (isEmpty(mask, pos) && canPut[i][(pos + 1) * 2])
          {
            int empty = (!pos || isEmpty(mask, pos - 1)) && !a[pos * 2 + 1];
            empty += (pos == k - 1 || isEmpty(mask, pos + 1)) && !a[pos * 2 + 3];
            int newAvailabe = available;
            for (int j = i * 2; j <= i * 2 + 1; j++)
              newAvailabe += j > k && !has[j];
            if (newAvailabe < empty) continue;

            f[i][mask | 1 << pos][newAvailabe - empty] += ways * choose(newAvailabe, empty);
          }
      }

  cout << f[1][(1 << k) - 1][0] << endl;
}