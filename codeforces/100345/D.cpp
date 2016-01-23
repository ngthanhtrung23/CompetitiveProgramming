#include <bits/stdc++.h>
using namespace std;

long long f[22][66666][2], fAll[22], fact[22];
int p[22];

long long calc(long long n)
{
  if (n < 100)
    return n;

  int len = 0, a[20];
  while (n)
  {
    a[len++] = n % 10;
    n /= 10;
  }

  long long res = 0;
  for (int i = 1; i < len; i++)
    res += fAll[i];

  memset(f, 0, sizeof f);
  for (int j = 1; j <= a[len - 1]; j++)
    f[len - 1][p[j]][j < a[len - 1]] = 1;

  for (int i = len - 2; i >= 0; i--)
    for (int mask = 0; mask < p[10]; mask++)
      for (int less = 0; less <= 1; less++)
        for (int j = 0; j < 10; j++)
        {
          int cnt = mask / p[j] % 3;
          if (cnt < 2 && (less || j <= a[i]))
            f[i][mask + p[j]][less | (j < a[i])] += f[i + 1][mask][less];
        }

  for (int mask = 0; mask < p[10]; mask++)
    for (int less = 0; less <= 1; less++)
      res += f[0][mask][less];

  return res;
}

int main()
{
  freopen("exchange.in", "r", stdin);
  freopen("exchange.out", "w", stdout);
  
  p[0] = 1;
  for (int i = 1; i <= 10; i++)
    p[i] = p[i - 1] * 3;

  fact[0] = 1;
  for (int i = 1; i <= 18; i++)
    fact[i] = fact[i - 1] * i;

  for (int mask = 0; mask < p[10]; mask++)
  {
    int cnt[10] = {0}, sumCnt = 0, divide = 1;
    for (int i = 0; i < 10; i++)
    {
      cnt[i] = mask / p[i] % 3;
      divide *= fact[cnt[i]];
      sumCnt += cnt[i];
    }

    for (int i = 1; i < 10; i++)
      if (cnt[i] < 2 && sumCnt + 1 <= 18)
        fAll[sumCnt + 1] += fact[sumCnt] / divide;
  }

  long long l, r;
  cin >> l >> r;
  cout << calc(r) - calc(l - 1) << endl;
}