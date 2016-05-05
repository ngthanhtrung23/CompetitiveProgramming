#include <bits/stdc++.h>
using namespace std;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int m, n, sx, sy, fx, fy, dist[2][222][222], cnt[44444];
string a[222];

void bfs(int dist[222][222], int sx, int sy)
{
  dist[sx][sy] = 0;
  queue < pair<int,int> > q;
  q.push({sx, sy});
  while (!q.empty())
  {
    int x = q.front().first, y = q.front().second;
    q.pop();
    for (int i = 0; i < 4; i++)
    {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx >= 0 && xx < m && yy >= 0 && yy < n && a[xx][yy] != 'B')
        if (dist[xx][yy] < 0)
        {
          dist[xx][yy] = dist[x][y] + 1;
          q.push({xx, yy});
        }
    }
  }
}

int main()
{
  freopen("labyrinth.in", "r", stdin);
  freopen("labyrinth.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> m >> n;
  for (int i = 0; i < m; i++)
  {
    cin >> a[i];
    for (int j = 0; j < n; j++)
      if (a[i][j] == 'R')
      {
        sx = i;
        sy = j;
      }
      else if (a[i][j] == 'S')
      {
        fx = i;
        fy = j;
      }
  }

  memset(dist, -1, sizeof dist);
  bfs(dist[0], sx, sy);
  bfs(dist[1], fx, fy);
  int minDist = dist[0][fx][fy];

  if (minDist < 0)
  {
    cout << 2 << endl;
    return 0;
  }

  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (dist[0][i][j] + dist[1][i][j] == minDist)
        cnt[dist[0][i][j]]++;

  int ans = 0;
  ans = cnt[minDist / 2] > 1;
  if (minDist % 2) ans &= cnt[minDist / 2 + 1] > 1;
  cout << ans + 1 << endl;
}