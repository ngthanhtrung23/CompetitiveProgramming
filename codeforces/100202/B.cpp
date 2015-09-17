#include <bits/stdc++.h>
using namespace std;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

map < pair<int,int>, int > dist;
set < pair<int,int> > civilized;

int main()
{
  freopen("control.in", "r", stdin);
  freopen("control.out", "w", stdout);
  int n, x, y, r;

  cin >> n;
  while (n--)
  {
    cin >> x >> y >> r;
    queue < pair<int,int> > q;
    dist.clear();
    for (int i = x - 1; i <= x + 1; i++)
      for (int j = y - 1; j <= y + 1; j++)
      {
        dist[{i, j}] = 0;
        civilized.insert({i, j});
        q.push({i, j});
      }

    while (!q.empty())
    {
      auto u = q.front();
      q.pop();
      if (dist[u] == r) continue;
      for (int i = 0; i < 4; i++)
      {
        pair <int,int> v(u.first + dx[i], u.second + dy[i]);
        if (dist.count(v)) continue;
        civilized.insert(v);
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }  

  while (1)
  {
    int found = 0;

    for (auto u : civilized)
      for (int i = 0; i < 4; i++)
      {
        pair <int,int> v(u.first + dx[i], u.second + dy[i]);
        if (civilized.count(v)) continue;
        int ok = 0;
        for (int xx = v.first - 1; xx <= v.first; xx++)
          for (int yy = v.second - 1; yy <= v.second; yy++)
          {
            int cnt = 0;
            for (int dx = 0; dx <= 1; dx++)
              for (int dy = 0; dy <= 1; dy++)
                cnt += civilized.count({xx + dx, yy + dy});

            if (!cnt) 
            {
              ok = 1;
              break;
            }
          }

        if (!ok)
        {
          found = 1;
          civilized.insert(v);
        }
      }

    if (!found) break;
  }

  cout << civilized.size() << endl;
}