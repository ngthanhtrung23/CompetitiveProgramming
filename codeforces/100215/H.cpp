#include <bits/stdc++.h>
using namespace std;
const int oo = 27081993;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int m, n, r, cost[1111], d[555][555], region[555][555], label[1111];
vector < pair<int,int> > a[1111];

int get(int x)
{
  return label[x] == x ? x : label[x] = get(label[x]);
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("police.in", "r", stdin);
  freopen("police.out", "w", stdout);

  int x, y;
  cin >> m >> n >> r;
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
    {
      region[i][j] = -1;
      d[i][j] = oo;  
    }

  queue < pair<int,int> > q;
  for (int i = 0; i < r; i++)
  {
    cin >> x >> y >> cost[i];
    d[x][y] = 0;
    region[x][y] = i;
    q.push({x, y});
  }

  while (!q.empty())
  {
    auto u = q.front();
    q.pop();  
    for (int i = 0; i < 4; i++)
    {
      int x = u.first + dx[i], y = u.second + dy[i];
      if (x > 0 && x <= m && y > 0 && y <= n)
      {
        if (d[x][y] == oo)
        {
          d[x][y] = d[u.first][u.second] + 1;
          region[x][y] = region[u.first][u.second];
          q.push({x, y});
        }
        else if (d[x][y] == d[u.first][u.second] + 1)
          region[x][y] = -1;
      }
    }
  }

  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      if (region[i][j] >= 0)
        a[cost[region[i][j]]].push_back({i, j + m});

  for (int i = 1; i <= m + n; i++)
    label[i] = i;

  int ans = 0, cnt = 0;
  vector < pair<int,int> > choose;
  for (int v = 1; v <= 1000; v++)
    for (auto u : a[v])
    {
      int x = get(u.first), y = get(u.second);
      if (x != y)
      {
        cnt++;
        ans += v;
        choose.push_back({u.first, u.second - m});
        label[x] = y;
      }
    }

  if (cnt < n + m - 1) cout << -1 << endl;
  else 
  {
    cout << cnt << ' ' << ans << endl;
    for (auto u : choose) 
      cout << u.first << ' ' << u.second << endl;
  }
}