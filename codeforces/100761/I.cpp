#include <bits/stdc++.h>
using namespace std;
const int oo = 27081993;

int n, h[55], f[55][6666], tr[55][6666], initialP;

int main()
{
  int sumH = 0;
  cin >> n;
  for (int i = 1; i <= n; i++)
  {
    cin >> h[i];
    sumH += h[i];
    initialP += abs(h[i] - h[i - 1]);
  }
  initialP += h[n] + n * 2;

  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= 6000; j++)
      f[i][j] = oo;

  for (int i = 1; i <= n; i++)
  {
    f[i][h[i] * 2 + 2] = h[i];
    for (int p = 2; p <= 6000; p++)
      if (f[i][p] != oo)
        for (int j = i + 1; j <= n; j++)
        {
          int newP = p - h[i] + h[j] + abs(h[j] - h[i]) + 2;
          if (f[j][newP] > f[i][p] + h[j])
          {
            f[j][newP] = f[i][p] + h[j];
            tr[j][newP] = i;
          }
        }
  }

  int ans = 0, bestI, bestP;
  for (int i = 1; i <= n; i++)
    for (int p = (initialP + 1) / 2; p <= 6000; p++)
      if (ans < sumH - f[i][p])
      {
        ans = sumH - f[i][p];
        bestI = i;
        bestP = p;
      }

  cout << ans << endl;
  if (!ans)
  {
    cout << 0 << endl;
    return 0;
  }
  
  set <int> keep;
  for (int i = bestI, p = bestP; i;)
  {
    keep.insert(i);
    int oldI = tr[i][p];
    p = p - 2 - h[i] + h[oldI] - abs(h[i] - h[oldI]);
    i = oldI;
  }

  cout << n - keep.size() << endl;
  for (int i = 1; i <= n; i++)
    if (!keep.count(i))
      cout << i << ' ';
}