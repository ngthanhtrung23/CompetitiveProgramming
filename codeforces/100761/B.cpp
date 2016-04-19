#include <bits/stdc++.h>
using namespace std;
const int oo = 1 << 30;

int n, m, w[11], t[11], s[11], c[1111], D[1111], d[1111];
int f[1010][1 << 10], done[1010][1 << 10];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> w[i] >> t[i] >> s[i];
  for (int i = 0; i < m; i++)
    cin >> c[i] >> D[i] >> d[i];

  priority_queue < pair<int, pair<int,int> > > q;
  for (int i = 0; i <= m; i++)
    for (int mask = 0; mask < 1 << n; mask++)
      f[i][mask] = oo;
  f[0][0] = 0;
  q.push({0, {0, 0}});
  while (!q.empty())
  {
    auto u = q.top();
    q.pop();
    int i = u.second.first, mask = u.second.second;
    if (done[i][mask]++) continue;

    if (i == m && !mask)
    {
      cout << f[i][mask] << endl;
      break;
    }

    // person j changes place
    for (int j = 0; j < n; j++)
      if (f[i][mask ^ 1 << j] > f[i][mask] + s[j])
      {
        f[i][mask ^ 1 << j] = f[i][mask] + s[j];
        q.push({-f[i][mask ^ 1 << j], {i, mask ^ 1 << j}});
      }

    if (!mask) continue;

    // go to next riffle
    int weight = 0, walk = 0;
    for (int j = 0; j < n; j++)
      if (mask >> j & 1) weight += w[j];
      else walk = max(walk, t[j]);
    int cost = max(walk, weight > c[i] ? D[i] : d[i]);
    if (f[i + 1][mask] > f[i][mask] + cost)
    {
      f[i + 1][mask] = f[i][mask] + cost;
      q.push({-f[i + 1][mask], {i + 1, mask}});
    }
  }
}