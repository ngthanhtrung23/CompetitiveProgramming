#include <bits/stdc++.h>
using namespace std;

int main()
{
  long long n;
  cin >> n;
  long long ans = 0;
  for (int i = 2; i <= n; i++)
    ans += n % i == 0;

  for (long long b = 2; b < n; b++)
  {
    long long p = b, sum = b + 1;
    while (sum <= n)
    {
      ans += n % sum == 0;
      p *= b;
      sum += p;
    }
  }

  cout << ans << endl;
}