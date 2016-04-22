#include <bits/stdc++.h>
using namespace std;
const long long oo = 1LL << 60;
const string DIRECTION = "URDL";
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

struct Robot
{
  int x, y;
  char d;
} a[100100];

int n, done[100100];
long long T, t[100100];
vector <int> edge[100100];
map < int, vector< pair<int,int> > > row, col;

void initGraph()
{
  for (auto u : row)
  {
    vector< pair<int,int> > v = u.second;
    sort(v.begin(), v.end());
    int last = -1;
    for (auto p : v)
    {
      int i = p.second;
      if (last >= 0)
        edge[last].push_back(i);
      if (a[i].d == 'R')
        last = i;
    }
    last = -1;
    reverse(v.begin(), v.end());
    for (auto p : v)
    {
      int i = p.second;
      if (last >= 0)
        edge[last].push_back(i);
      if (a[i].d == 'L')
        last = i;
    }
  }

  for (auto u : col)
  {
    vector< pair<int,int> > v = u.second;
    sort(v.begin(), v.end());
    int last = -1;
    for (auto p : v)
    {
      int i = p.second;
      if (last >= 0)
        edge[last].push_back(i);
      if (a[i].d == 'U')
        last = i;
    }
    last = -1;
    reverse(v.begin(), v.end());
    for (auto p : v)
    {
      int i = p.second;
      if (last >= 0)
        edge[last].push_back(i);
      if (a[i].d == 'D')
        last = i;
    }
  }
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int x, y;
  char d;
  cin >> n >> T;
  for (int i = 0; i < n; i++)
  {
    cin >> x >> y >> d;
    a[i] = {x, y, d};
    t[i] = oo;
    if (!row.count(y))
      row[y] = vector< pair<int,int> >();
    row[y].push_back({x, i});
    if (!col.count(x))
      col[x] = vector< pair<int,int> >();
    col[x].push_back({y, i});
  }

  initGraph();

  t[0] = 0;
  priority_queue < pair<long long,int> > q;
  q.push({0, 0});
  while (!q.empty())
  {
    int u = q.top().second;
    q.pop();
    if (done[u]) continue;
    done[u] = 1;

    for (auto v : edge[u])
    {
      long long cost = abs(a[u].x + a[u].y - a[v].x - a[v].y);
      if (!done[v] && t[v] > t[u] + cost)
      {
        t[v] = t[u] + cost;
        q.push({-t[v], v});
      }
    }
  }

  for (int i = 0; i < n; i++)
    if (t[i] > T) cout << a[i].x << ' ' << a[i].y << '\n';
    else
      for (int j = 0; j < 4; j++)
        if (DIRECTION[j] == a[i].d)
          cout << a[i].x + (T - t[i]) * dx[j] << ' ' << a[i].y + (T - t[i]) * dy[j] << '\n';
}