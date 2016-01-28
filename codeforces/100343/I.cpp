#include <bits/stdc++.h>
using namespace std;

int main()
{
  freopen("video.in", "r", stdin);
  freopen("video.out", "w", stdout);
  long long d, b, t, p;
  cin >> d >> b >> t >> p;
  long long buffer = d * p;
  long long noPause = (t * (b - d) + buffer - 1) / buffer;
  
  long long low = 1, high = buffer - 1, ans = buffer;
  while (low <= high)
  {
    long long mid = (low + high) / 2;
    if ((t * (b - d) + mid - 1) / mid == noPause)
    {
      ans = mid;
      high = mid - 1;
    }
    else low = mid + 1;
  }

  cout << ans << endl;
}