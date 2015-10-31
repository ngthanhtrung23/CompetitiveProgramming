#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  freopen("princess.in", "r", stdin);
  freopen("princess.out", "w", stdout);
  int n;
  cin >> n;
  if (n == 1)
  {
    cout << 1.0 << endl;
    return 0;
  }
  long double ans = 0;
  for (int r = 1; r < n; r++)
  {
    long double p = 0;
    for (int i = r; i <= n - 1; i++)
      p += 1.0 / i;
    p = p * r / n;
    ans = max(ans, p);
  }  
  cout << fixed << setprecision(12) << ans << endl;
}