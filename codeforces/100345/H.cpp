#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9) + 7;

int a[222][222];
long long ways[222][222];

int main()
{
  freopen("settling.in", "r", stdin);
  freopen("settling.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m, q, x, y;
  char t;

  cin >> n >> m;
  while (m--)
  {
    cin >> x >> y;
    a[x][y] = 1;
  }

  int ans = 0;
  for (int x = n; x; x--)
  {
    ways[x][x] = 1;
    for (int y = x + 1; y <= n; y++)
      if (a[x][y])
        for (int z = y; z <= n; z++)
          ways[x][z] = (ways[x][z] + ways[y][z]) % BASE;

    for (int y = x + 1; y <= n; y++)
      ans += ways[x][y] > 0;
  }

  cout << ans << endl;
  cin >> q;
  while (q--)
  {
    cin >> t >> x >> y;
    if (t == '?') cout << (ways[x][y] ? "YES" : "NO") << '\n';
    else if (t == '+')
    {
      if (!a[x][y])
        for (int u = 1; u <= x; u++)
          for (int v = y; v <= n; v++)
          {
            ans -= ways[u][v] > 0;
            ways[u][v] = (ways[u][v] + ways[u][x] * ways[y][v]) % BASE;
            ans += ways[u][v] > 0;
          }
      a[x][y] = 1;
      cout << ans << '\n';
    }
    else
    {
      if (a[x][y])
        for (int u = 1; u <= x; u++)
          for (int v = y; v <= n; v++)
          {
            ans -= ways[u][v] > 0;
            ways[u][v] = (ways[u][v] - ways[u][x] * ways[y][v] % BASE + BASE) % BASE;
            ans += ways[u][v] > 0;
          }
      a[x][y] = 0;
      cout << ans << '\n';
    }
  }
}