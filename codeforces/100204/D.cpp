#include <bits/stdc++.h>
using namespace std;

long long f[10][1 << 14];
vector <int> potentialMasks[10], bits[1 << 14];

int main()
{
  ios::sync_with_stdio(0);
  freopen("hex.in", "r", stdin);
  freopen("hex.out", "w", stdout);

  int n;
  cin >> n;  
  if (n == 1)
  {
    cout << 2 << endl;
    return 0;
  }

  for (int j = 0; j < n + 1; j++)
    f[1][1 << j] = 1;

  for (int i = 1; i <= n; i++)
    for (int mask = 0; mask < 1 << n + i; mask++)
      if (__builtin_popcount(mask) == i)
        potentialMasks[i].push_back(mask);

  for (int mask = 0; mask < 1 << n * 2; mask++)
    for (int i = 0; i < n * 2; i++)
      if (mask >> i & 1)
        bits[mask].push_back(i);

  for (int i = 2; i <= n; i++)
    for (auto mask : potentialMasks[i])
      for (auto oldMask : potentialMasks[i - 1])
      {
        int ok = 1;
        for (int j = 0; j < int(bits[oldMask].size()); j++)
          ok &= bits[mask][j] <= bits[oldMask][j] && bits[oldMask][j] < bits[mask][j + 1];
        if (ok) 
          f[i][mask] += f[i - 1][oldMask];
      }

  long long ans = 0;
  for (auto mask : potentialMasks[n])
    for (auto oldMask : potentialMasks[n - 1])
    {
      int ok = 1;
        for (int j = 0; j < int(bits[oldMask].size()); j++)
          ok &= bits[mask][j] <= bits[oldMask][j] && bits[oldMask][j] < bits[mask][j + 1];
        if (ok) 
          ans += f[n][mask] * f[n - 1][oldMask];
    }

  cout << ans << endl;
}