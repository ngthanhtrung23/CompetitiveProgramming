#include <bits/stdc++.h>
using namespace std;
const int oo = 1 << 29;

struct Edge
{
  int x, y, cap, flow;
};

struct DinicFlow
{
  int n, S, T;
  vector < vector <int> > a;
  vector <int> cur, d;
  vector <Edge> e;
  
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
    Edge e1 = {x, y, cap, 0};
    Edge e2 = {y, x, 0, 0};
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
};

struct Segment
{
  int x, y, yy;
};

vector <Segment> h[26], v[26], ansH[26], ansV[26];
vector < pair<int,int> > ansS[26];
int m, n, hCost, vCost, sCost, idH[33][33], idV[33][33];
string a[33];

int main()
{
  ios::sync_with_stdio(0);
  freopen("painter.in", "r", stdin);
  freopen("painter.out", "w", stdout);

  cin >> m >> n >> hCost >> vCost >> sCost;
  for (int i = 0; i < m; i++)
    cin >> a[i];

  for (int i = 0; i < m; i++)
    for (int j = 0; j < n;)
    {
      int jj = j + 1;
      while (jj < n && a[i][jj] == a[i][j]) jj++;
      h[a[i][j] - 'a'].push_back({i, j, jj - 1});
      j = jj;
    }  

  for (int j = 0; j < n; j++)
    for (int i = 0; i < m;)
    {
      int ii = i + 1;
      while (ii < m && a[ii][j] == a[i][j]) ii++;
      v[a[i][j] - 'a'].push_back({j, i, ii - 1});
      i = ii;
    }

  int ans = 0, cnt = 0;
  for (int c = 0; c < 26; c++)
    if (!h[c].empty() || !v[c].empty())
    {
      int S = h[c].size() + v[c].size() + 1, T = S + 1;
      DinicFlow f(T, S, T);
      for (int i = 0; i < h[c].size(); i++)
        f.addEdge(S, i + 1, hCost);
      for (int i = 0; i < v[c].size(); i++)
        f.addEdge(h[c].size() + i + 1, T, vCost);

      memset(idH, 0, sizeof idH);
      for (int i = 0; i < h[c].size(); i++)
        for (int y = h[c][i].y; y <= h[c][i].yy; y++)
          idH[h[c][i].x][y] = i + 1;

      memset(idV, 0, sizeof idV);
      for (int i = 0; i < v[c].size(); i++)
        for (int x = v[c][i].y; x <= v[c][i].yy; x++)
          idV[x][v[c][i].x] = h[c].size() + i + 1;

      for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
          if (idH[i][j])
            f.addEdge(idH[i][j], idV[i][j], sCost);

      ans += f.maxFlow();
      f.bfs();

      for (int i = 1; i <= h[c].size(); i++)
        if (f.d[i] < 0)
        {
          ansH[c].push_back(h[c][i - 1]);
          cnt++;
        }

      for (int i = 1; i <= v[c].size(); i++)
        if (f.d[i + h[c].size()] >= 0)
        {
          ansV[c].push_back(v[c][i - 1]); 
          cnt++;
        }

      for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
          if (idH[i][j] && f.d[idH[i][j]] >= 0 && f.d[idV[i][j]] < 0)
          {
            ansS[c].push_back({i + 1, j + 1}); 
            cnt++;
          }
    }

  cout << ans << ' ' << cnt << endl;
  for (int c = 0; c < 26; c++)
  {
    char ch = char(c + 'a');
    for (auto seg : ansH[c])
      cout << "h " << seg.x + 1 << ' ' << seg.y + 1 << ' ' << seg.x + 1 << ' ' << seg.yy + 1 << ' ' << ch << endl;
    for (auto seg : ansV[c])
      cout << "v " << seg.y + 1 << ' ' << seg.x + 1 << ' ' << seg.yy + 1 << ' ' << seg.x + 1 << ' ' << ch << endl;
    for (auto u : ansS[c])
      cout << "s " << u.first << ' ' << u.second << ' ' << ch << endl;
  }
}