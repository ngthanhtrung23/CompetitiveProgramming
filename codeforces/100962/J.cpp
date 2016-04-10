#include <bits/stdc++.h>
using namespace std;

int n, l, f[500500], g[500500], trF[500500], trG[500500];
string s;
vector < pair<int, char> > a[500500];

void visit(int x, int par)
{
  trF[x] = trG[x] = x;
  for (auto u : a[x])
  {
    int y = u.first;
    char z = u.second;
    if (y == par)
      continue;
    visit(y, x);

    int curF = f[y] + (f[y] < l && z == s[f[y] + 1]);
    int curG = g[y] + (g[y] < l && z == s[l - g[y]]);

    if (curF + g[x] >= l)
    {
      cout << trF[y] << ' ' << trG[x] << endl;
      exit(0);
    }

    if (curG + f[x] >= l)
    {
      cout << trF[x] << ' ' << trG[y] << endl;
      exit(0);
    }

    if (curF > f[x])
    {
      f[x] = curF;
      trF[x] = trF[y];
    }
    if (curG > g[x])
    {
      g[x] = curG;
      trG[x] = trG[y];
    }
  }
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int x, y;
  char z;
  cin >> n >> l;
  for (int i = 1; i < n; i++)
  {
    cin >> x >> y >> z;
    a[x].push_back({y, z});
    a[y].push_back({x, z});
  }
  cin >> s;
  s = " " + s;

  visit(1, 0);
  cout << "-1 -1" << endl;
}