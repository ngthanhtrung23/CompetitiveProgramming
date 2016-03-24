#include <bits/stdc++.h>
using namespace std;
const int oo = 27081993;

struct edge
{
  int x, y, cap, flow;
};

struct DinicFlow
{
  int n, S, T;
  vector < vector <int> > a;
  vector <int> cur, d;
  vector <edge> e;

  DinicFlow() {}
  DinicFlow(int n, int S, int T)
  {
    this -> n = n;
    this -> S = S;
    this -> T = T;
    a = vector < vector <int> >(n + 1);
    cur = vector <int>(n + 1);
    d = vector <int>(n + 1);
  }

  void addEdge(int x, int y, int cap)
  {
    edge e1 = {x, y, cap, 0};
    edge e2 = {y, x, 0, 0};
    a[x].push_back(e.size()); e.push_back(e1);
    a[y].push_back(e.size()); e.push_back(e2);
  }

  int bfs()
  {
    queue <int> q;
    for (int i = 1; i <= n; i++) d[i] = -1;
    q.push(S); d[S] = 0;
    while (!q.empty() && d[T] < 0)
    {
      int x = q.front(); q.pop();
      for (int i = 0; i < int(a[x].size()); i++)
      {
        int id = a[x][i], y = e[id].y;
        if (d[y] < 0 && e[id].flow < e[id].cap)
          q.push(y), d[y] = d[x] + 1;
      }
    }
    return d[T] >= 0;
  }

  int dfs(int x, int val)
  {
    if (!val) return 0;
    if (x == T) return val;
    for (; cur[x] < int(a[x].size()); cur[x]++)
    {
      int id = a[x][cur[x]], y = e[id].y;
      if (d[y] != d[x] + 1) continue;
      int pushed = dfs(y, min(val, e[id].cap - e[id].flow));
      if (pushed)
      {
        e[id].flow += pushed;
        e[id ^ 1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  int maxFlow()
  {
    int res = 0;
    while (bfs())
    {
      for (int i = 1; i <= n; i++) cur[i] = 0;
      while (1)
      {
        int val = dfs(S, oo);
        if (!val) break;
        res += val;
      }
    }
    return res;
  } 

  int minCut()
  {
    maxFlow();
    int res = 0;
    for (int x = 1; x <= n; x++)
      if (d[x] >= 0)
        for (int i = 0; i < int(a[x].size()); i++)
        {
          int id = a[x][i], y = e[id].y;
          if (d[y] < 0) res += e[id].cap;
        }
    return res;
  }
};

int n, numPair, point[33], match[33][33], id[33][33];
string name[33];

vector <int> blockingSet(int x)
{
  int maxPoint = point[x];
  for (int i = 1; i <= n; i++)
    maxPoint += match[x][i];
  int S = n + numPair + 1, T = S + 1, totalMatch = 0;
  DinicFlow f(T, S, T);
  for (int i = 1; i <= n; i++)
  {
    if (i == x) continue;
    if (point[i] > maxPoint)
      return vector<int>(1, i);
    if (point[i] < maxPoint)
      f.addEdge(i, T, maxPoint - point[i]);
    for (int j = i + 1; j <= n; j++)
      if (j != x && match[i][j])
      {
        totalMatch += match[i][j];
        f.addEdge(S, n + id[i][j], match[i][j]);
        f.addEdge(n + id[i][j], i, match[i][j]);
        f.addEdge(n + id[i][j], j, match[i][j]);
      }
  }

  if (f.maxFlow() == totalMatch)
    return vector<int>();

  vector <int> bs;
  for (int i = 1; i <= n; i++)
    if (f.d[i] >= 0)
      bs.push_back(i);
  return bs;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("high.in", "r", stdin);
  freopen("high.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> name[i] >> point[i];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> match[i][j];

  for (int i = 1; i < n; i++)
    for (int j = i + 1; j <= n; j++)
      if (match[i][j])
        id[i][j] = ++numPair;

  for (int i = 1; i <= n; i++)
  {
    vector <int> s = blockingSet(i);
    if (s.empty()) cout << name[i] << " can win\n";
    else
    {
      cout << name[i] << " cannot win because of the following teams:\n  ";
      for (int j = 0; j < s.size(); j++)
      {
        if (j) cout << ", ";
        cout << name[s[j]];
      }
      cout << "\n";
    }
  }
}