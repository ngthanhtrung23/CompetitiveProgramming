#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9) + 7;

long long fact[1000100], invFact[1000100];

long long power(long long x, long long y)
{
  if (!y) return 1;
  long long res = power(x, y / 2);
  res = res * res % BASE;
  if (y % 2)
    res = res * x % BASE;
  return res;
}

long long c(int n, int k)
{
  return fact[n] * invFact[k] % BASE * invFact[n - k] % BASE;
}

int main()
{
  freopen("azerah.in", "r", stdin);
  freopen("azerah.out", "w", stdout);

  for (int i = 0; i <= 1000000; i++) 
  {
    fact[i] = i ? fact[i - 1] * i % BASE : 1;
    invFact[i] = power(fact[i], BASE - 2);
  }

  int test, x;
  scanf("%d", &test);
  while (test--)
  {
    int n, odd = 0, even = 0;
    scanf("%d", &n);
    while (n--)
    {
      scanf("%d", &x);
      if (x % 2) odd++;
      else even++;
    }

    long long ways = power(2, even);
    long long ans = (ways - 1 + BASE) % BASE;
    for (int i = 2; i <= odd; i += 2)
      ans = (ans + c(odd, i) * ways) % BASE;
    printf("%d\n", int(ans));
  }
}