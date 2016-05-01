#include <bits/stdc++.h>
using namespace std;
const int oo = 1 << 30;

int n, k, W, a[444][444], c[444][444], f[444][444];

void dp(int mask)
{
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
    {
      f[i][j] = oo;
      if (mask >> c[i][j] & 1)
        f[i][j] = min(f[i - 1][j], f[i][j - 1]) + a[i][j];
    }
}

int main()
{
  scanf("%d%d%d", &n, &k, &W);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      scanf("%d", a[i] + j);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
    {
      scanf("%d", c[i] + j);
      c[i][j]--;
    }

  for (int i = 2; i <= n; i++)
    f[i][0] = f[0][i] = oo;

  int ans = oo, bestMask = -1;
  for (int mask = 1; mask < 1 << k; mask++)
  {
    if (!(mask >> c[1][1] & 1) || !(mask >> c[n][n] & 1)) 
      continue;
    int bit = __builtin_popcount(mask);
    if (bit < ans)
    {
      dp(mask); 
      if (f[n][n] <= W)
      {
        ans = bit;
        bestMask = mask;
      }
    }
  }

  if (ans == oo) cout << -1 << endl;
  else
  {
    cout << ans << endl;
    dp(bestMask);
    vector <int> path;
    for (int i = n, j = n; i && j;)
    {
      path.push_back(j);
      path.push_back(i);
      if (f[i][j] == f[i - 1][j] + a[i][j]) i--;
      else j--;
    }
    reverse(path.begin(), path.end());
    for (auto x : path)
      printf("%d ", x);
    puts("");
  }
}