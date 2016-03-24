#include <bits/stdc++.h>
using namespace std;
const long long oo = 1LL << 60;

int main()
{
  freopen("bigset.in", "r", stdin);
  freopen("bigset.out", "w", stdout);
  long long m, n;
  cin >> m >> n;
  long long low = 1, high = m, ans = m;
  while (low <= high)
  {
    long long mid = (low + high) / 2, sum = 0;
    for (int i = 1; i <= n; i++)
      sum = min(oo, sum + mid / i);
    if (sum >= m) 
    {
      ans = mid;
      high = mid - 1;
    }
    else low = mid + 1;
  }
  cout << ans << endl;
}