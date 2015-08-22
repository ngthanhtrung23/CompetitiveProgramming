#include <bits/stdc++.h>
using namespace std;

int n, S, T, d[444];
vector <int> a[444], ans[500000];
pair <int,int> edges[500000];

int main()
{
  ios::sync_with_stdio(0);
  freopen("defence.in", "r", stdin);
  freopen("defence.out", "w", stdout);
  int x, y, m;
  cin >> n >> m >> S >> T;
  for (int i = 0; i < m; i++)
  {
    cin >> x >> y;
    edges[i] = make_pair(x, y);
    a[x].push_back(y);
    a[y].push_back(x);
  } 

  queue <int> q;
  q.push(S);
  d[S] = 1;
  while (!q.empty())
  {
    int x = q.front();
    q.pop();
    for (auto y : a[x])
      if (!d[y])
      {
        d[y] = d[x] + 1;
        q.push(y);
      }
  }

  cout << d[T] - 1 << endl;
  for (int i = 0; i < m; i++)
  {
    int type = min(d[edges[i].first], d[edges[i].second]);
    ans[type].push_back(i + 1);
  }

  for (int i = 1; i < d[T]; i++)
  {
    cout << ans[i].size() << ' ';
    for (auto e : ans[i])
      cout << e << ' ';
    cout << '\n';
  }
}