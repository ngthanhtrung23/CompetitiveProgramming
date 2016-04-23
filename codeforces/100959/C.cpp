#include <bits/stdc++.h>
using namespace std;
const int Z = 100000;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int Q, s, t, n, a[222], dist[2][200200];
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];

  memset(dist, -1, sizeof dist);
  dist[0][Z] = 0;
  queue < pair<int,int> > q;
  q.push({0, 0});
  while (!q.empty())
  {
    int x = q.front().second, u = q.front().first;
    q.pop();
    for (int i = 0; i < n; i++)
    {
      int y = 2 * a[i] - x;
      if (y >= -Z && y <= Z && dist[u ^ 1][y + Z] < 0)
      {
        dist[u ^ 1][y + Z] = dist[u][x + Z] + 1;
        q.push({u ^ 1, y});
      }
    }
  }

  cin >> Q;
  while (Q--)
  {
    cin >> s >> t;
    int ans = -1;
    if (dist[0][t - s + Z] >= 0)
      ans = dist[0][t - s + Z];
    if (dist[1][t + s + Z] >= 0)
      if (ans < 0 || ans > dist[1][t + s + Z])
        ans = dist[1][t + s + Z];
    cout << ans << '\n';
  }
}