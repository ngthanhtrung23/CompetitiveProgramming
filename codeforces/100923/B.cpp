#include <bits/stdc++.h>
using namespace std;
const long long oo = 1LL << 60;

struct Edge
{
  int y, z, id;
};

int n, m, tr[100100], id[100100], flag[200200];
long long dist[100100];
vector <Edge> a[100100];

void dijkstra()
{
  int done[100100] = {0};
  for (int i = 1; i <= n; i++)
    dist[i] = oo;
  dist[1] = 0;
  priority_queue < pair<long long,int> > q;
  q.push({0, 1});
  while (!q.empty())
  {
    int x = q.top().second;
    q.pop();
    if (done[x]++) continue;

    for (auto u : a[x])
      if (!done[u.y] && dist[u.y] > dist[x] + u.z)
      {
        dist[u.y] = dist[x] + u.z;
        tr[u.y] = u.id;
        q.push({-dist[u.y], u.y});
      }
  }
}

bool cmp(int u, int v)
{
  return dist[u] < dist[v];
}

int main()
{
  freopen("algoritm.in", "r", stdin);
  freopen("algoritm.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);

  int test, x, y, z;
  cin >> test;
  while (test--)
  {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
      a[i].clear();
      id[i] = i;
    }
    for (int i = 1; i <= m; i++)
    {
      cin >> x >> y >> z;
      a[x].push_back({y, z, i});
      flag[i] = 0;
    }
    dijkstra();

    sort(id + 1, id + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
      int x = id[i], y = tr[x];
      if (y && !flag[y])
      {
        flag[y] = 1;
        cout << y << ' ';
      }
    }

    for (int i = 1; i <= m; i++)
      if (!flag[i])
        cout << i << ' ';
    cout << endl;
  }
}