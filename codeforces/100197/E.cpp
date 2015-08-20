#include <bits/stdc++.h>
using namespace std;
const int oo = 1000111000;

int n, x[1010], q[133][133], s, m, f[1010][133], tr[1010][133], id[1010];

int main()
{
  ios::sync_with_stdio(0);
  freopen("quant.in", "r", stdin);
  freopen("quant.out", "w", stdout);

  cin >> n;
  for (int i = 0; i < n; i++) 
    cin >> x[i];

  cin >> m >> s;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < s; j++)
      cin >> q[i][j];

  for (int j = 0; j < s; j++)
    f[0][j] = abs(q[0][j] - x[0]);

  for (int i = 1; i < n; i++)
  {
    for (int j = 0; j < s; j++)
      f[i][j] = oo;

    for (int j = 0; j < s; j++)
      for (int k = 0; k < s; k++)
      {
        int v = f[i - 1][j] + abs(q[j & (m - 1)][k] - x[i]);
        if (v < f[i][k])
        {
          f[i][k] = v;
          tr[i][k] = j;
        }
      }
  }

  int ans = oo;
  for (int j = 0; j < s; j++)
    if (f[n - 1][j] < ans)
    {
      ans = f[n - 1][j];
      id[n - 1] = j;
    }

  cout << ans << endl;
  for (int i = n - 1; i; i--)
    id[i - 1] = tr[i][id[i]];
  for (int i = 0; i < n; i++)
    cout << id[i] << (i == n - 1 ? '\n' : ' ');
}