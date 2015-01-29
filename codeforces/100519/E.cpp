#include <bits/stdc++.h>
using namespace std;
const long long oo = (long long)1e15;

pair <int,long long> ans(-1, 0);
long long n;
int d;
  
void solve()
{
  long long delta = 1 - 4 * (1 - n / d);
  if (delta < 0) return;
  long long u = (long long)sqrt(delta);
  if (u * u != delta) return;
  if (u % 2 == 0) return;
  long long x = (u - 1) / 2;
  if (x < 2 || x * x + x + 1 != n / d) return;
  ans = max(ans, make_pair(3, -x));
}

int main()
{
  ios::sync_with_stdio(0);
  cin >> n >> d;
  
  if (n < 2)
  {
    cout << 2 << ' ' << (n == d) << endl;
    return 0;
  }
  
  
  for (int b = 2; 1LL * b * b <= oo && b <= n * 2; b++)
  {
    long long x = n;
    int cur = 0;
    while (x)
    {
      if (x % b == d) cur++;
      else break;
      x /= b;
    }
    
    ans = max(ans, make_pair(cur, -1LL * b));
    
    // Case xDD
    long long r = n % (1LL * b * b);
    if (r == (b + 1LL) * d) ans = max(ans, make_pair(2, -1LL * b));
  }
  
  // Case DDD
  if (d && n % d == 0) solve();
  
  // Case DD
  if (d && n % d == 0)
  {
    if (n / d >= 3) ans = max(ans, make_pair(2, -(n / d - 1)));
  }
  
  // Case xD
  if (n - d >= 2)
  {
    if (n - d > d) ans = max(ans, make_pair(1, d - n));
    for (long long i = 2; i * i <= n - d; i++)
      if ((n - d) % i == 0)
      {
        long long j = (n - d) / i;
        if (i > d) ans = max(ans, make_pair(1, -i));        
        if (j > d) ans = max(ans, make_pair(1, -j));
      }
  }
  
  cout << -ans.second << ' ' << ans.first << endl;
}
