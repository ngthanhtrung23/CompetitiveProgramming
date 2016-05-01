#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9) + 7;

int n, c[2020][2020], tree[2020][2020];
long long f[2020];

long long power(long long x, int y)
{
  if (!y) return 1;
  long long res = power(x, y / 2);
  res = res * res % BASE;
  if (y % 2)
    res = res * x % BASE;
  return res;
}

void add(int k, int x, int v)
{
  for (int i = x; i <= n; i += i & -i)
  {
    tree[k][i] += v;
    if (tree[k][i] >= BASE)
      tree[k][i] -= BASE;
  }
}

int get(int k, int x)
{
  int res = 0;
  for (int i = x; i; i -= i & -i)
  {
    res += tree[k][i];
    if (res >= BASE)
      res -= BASE;
  }
  return res;
}

int main()
{
  int x;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> x;
    for (int k = i; k; k--)
      add(k + 1, x, get(k, x - 1)); 
    add(1, x, 1);
  }

  for (int i = 0; i <= n; i++)
  {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++)
    {
      c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
      if (c[i][j] >= BASE)
        c[i][j] -= BASE;
    }
  }

  f[1] = 1;
  for (int i = 2; i <= n; i++)
  {
    f[i] = power(i, n);
    for (int j = 1; j < i; j++)
      f[i] = (f[i] - f[j] * c[i][j] % BASE + BASE) % BASE;
  }

  long long ans = 0;
  for (int i = 1; i <= n; i++)
    ans = (ans + get(i, n) * f[i]) % BASE;
  cout << ans << endl;
}