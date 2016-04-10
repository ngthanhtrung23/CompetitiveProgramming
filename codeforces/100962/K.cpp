#include <bits/stdc++.h>
using namespace std;

int n, cnt, low[500500], num[500500], par[500500], numChild[500500], flag[500500];
vector <int> a[500500];
set <int> cut;

void visit(int x)
{
  num[x] = low[x] = ++cnt;
  numChild[par[x]]++;
  for (int y : a[x])
    if (y != par[x])
    {
      if (num[y]) low[x] = min(low[x], num[y]);
      else 
      {
        par[y] = x;
        visit(y);
        low[x] = min(low[x], low[y]);
      }
    }
}

void dfs(int x, int par, int bad)
{
  if (flag[x]++)
  {
    cout << 0 << endl;
    exit(0);
  }

  for (int y : a[x])
    if (y != bad && y != par)
      dfs(y, x, bad);
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int x, y, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    cin >> x >> y;
    a[x].push_back(y);
    a[y].push_back(x);
  }

  for (int i = 1; i <= n; i++)
    if (a[i].size() % 2)
    {
      cout << 0 << endl;
      return 0;
    }

  visit(1);
  for (int i = 1; i <= n; i++)
    if (par[i] && low[i] >= num[par[i]] && (par[par[i]] || numChild[par[i]] >= 2))
      cut.insert(par[i]);

  if (cut.size() >= 2)
  {
    cout << 0 << endl;
    return 0;
  }

  if (cut.size() == 1)
  {
    int bad = *cut.begin();
    for (int i = 1; i <= n; i++)
      if (i != bad && !flag[i])
        dfs(i, 0, bad);
    cout << 1 << endl << bad << endl;
    return 0;
  }

  vector <int> ans;
  for (int i = 1; i <= n; i++)
    if (a[i].size() + n - 2 == m)
      ans.push_back(i);

  cout << ans.size() << endl;
  for (int x : ans)
    cout << x << ' ';
}