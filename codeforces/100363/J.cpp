#include <bits/stdc++.h>
using namespace std;
const int BASE = int(1e9);

long long f[222][222][2];
vector <int> a[222];
int n, sz[222];

void addMod(long long &x, long long y)
{ 
  x = (x + y) % BASE;
}

void visit(int x, int par)
{
  sz[x] = 1;
  f[x][0][0] = f[x][1][1] = 1;
  for (int y : a[x])
    if (y != par)
    {
      visit(y, x);
      sz[x] += sz[y];

      long long oldF[222][2];
      for (int i = 0; i <= sz[x]; i++)
        for (int u = 0; u < 2; u++)
          oldF[i][u] = f[x][i][u];

      for (int i = sz[x]; i; i--)
        for (int j = min(sz[y], i); j; j--)
          for (int u = 0; u < 2; u++)
            for (int v = 0; v < 2; v++)
            {
              addMod(f[x][i][u], f[y][j][v] * oldF[i - j][u]);
              if (u && v)
                addMod(f[x][i][u], f[y][j][v] * oldF[i - j + 1][v]);
            }
    }
}

int main()
{
  freopen("subtrees.in", "r", stdin);
  freopen("subtrees.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);

  int x, y;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    cin >> x >> y;
    a[x].push_back(y);
    a[y].push_back(x);
  }

  visit(1, 0);
  for (int i = 1; i <= n; i++)
    cout << (f[1][i][0] + f[1][i][1]) % BASE << endl;
}