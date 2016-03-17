#include <bits/stdc++.h>
using namespace std;

short f[3333][3333], g[3333][3333];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("subpair.in", "r", stdin);
  freopen("subpair.out", "w", stdout);

  string a, b;
  cin >> a >> b;
  int m = a.size(), n = b.size();
  a = " " + a;
  b = " " + b;
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      f[i][j] = a[i] == b[j] ? f[i - 1][j - 1] + 1 : 0;

  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
    {
      f[i][j] = max(f[i][j], f[i - 1][j]);
      f[i][j] = max(f[i][j], f[i][j - 1]);
    }

  int ans = -1, x, y;
  for (int i = m; i; i--)
    for (int j = n; j; j--)
    {
      g[i][j] = a[i] == b[j] ? g[i + 1][j + 1] + 1 : 0;
      if (g[i][j] + f[i - 1][j - 1] > ans)
      {
        ans = g[i][j] + f[i - 1][j - 1];
        x = i;
        y = j;
      }
    }

  string alpha = "", beta = "";
  if (g[x][y])
    beta = a.substr(x, g[x][y]);

  if (f[--x][--y])
  {
    while (1)
    {
      if (f[x][y] == f[x - 1][y]) x--;
      else if (f[x][y] == f[x][y - 1]) y--;
      else break;
    }
    alpha = a.substr(x - f[x][y] + 1, f[x][y]);
  }

  cout << alpha << endl << beta << endl;
}