#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp
{
  vector <int> leftMatch, rightMatch, dist, cur;
  vector < vector <int> > a;
  int m, n;

  HopcroftKarp() {}
  HopcroftKarp(int m, int n)
  {
    this -> m = m;
    this -> n = n;
    a = vector < vector <int> >(m);
    leftMatch = vector <int>(n, -1);
    rightMatch = vector <int>(m, -1);
    dist = vector <int>(m, -1);
    cur = vector <int>(m, -1);
  }

  void addEdge(int x, int y)
  {
    a[x].push_back(y);
  }

  int bfs()
  {
    int found = 0;
    queue <int> q;
    for (int i = 0; i < m; i++)
      if (rightMatch[i] < 0) dist[i] = 0, q.push(i);
      else dist[i] = -1;

    while (!q.empty())
    {
      int x = q.front(); q.pop();
      for (int i = 0; i < int(a[x].size()); i++)
      {
        int y = a[x][i];
        if (leftMatch[y] < 0) found = 1;
        else
          if (dist[leftMatch[y]] < 0)
            dist[leftMatch[y]] = dist[x] + 1, q.push(leftMatch[y]);
      }
    }

    return found;
  }

  int dfs(int x)
  {
    for (; cur[x] < int(a[x].size()); cur[x]++)
    {
      int y = a[x][cur[x]];
      if (leftMatch[y] < 0 || (dist[leftMatch[y]] == dist[x] + 1 && dfs(leftMatch[y])))
      {
        leftMatch[y] = x; rightMatch[x] = y;
        return 1;
      }
    }
    return 0;
  }

  int maxMatching()
  {
    int match = 0;
    while (bfs())
    {
      for (int i = 0; i < m; i++) cur[i] = 0;
      for (int i = 0; i < m; i++)
        if (rightMatch[i] < 0) match += dfs(i);
    }
    return match;
  }
};

int n, onTable;
vector < pair<int,char> > a[2];
char trump;

int getRank(char c)
{
  if (c <= '9') return c - '6';
  if (c == 'T') return 4;
  if (c == 'J') return 5;
  if (c == 'Q') return 6;
  if (c == 'K') return 7;
  return 8;
}

int canCover(pair <int,int> u, pair <int,int> v)
{
  if (u.second == v.second) return u.first < v.first;
  return v.second == trump;
}

int ok(int mask)
{
  vector < pair<int,char> > b[2];
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < n; j++)
      if (mask >> a[i][j].first & 1)
        b[i].push_back(a[i][j]);
  HopcroftKarp hk(b[0].size(), b[1].size());
  for (int i = 0; i < b[0].size(); i++)
    for (int j = 0; j < b[1].size(); j++)
      if (canCover(b[0][i], b[1][j]))
        hk.addEdge(i, j);
  return hk.maxMatching() == b[0].size();
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("fool.in", "r", stdin);
  freopen("fool.out", "w", stdout);

  string s;
  cin >> n >> trump;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < n; j++)
    {
      cin >> s;
      if (s[2] == '*')
      {
        s = s.substr(0, 2);
        onTable |= 1 << getRank(s[0]);
      }
      a[i].push_back({getRank(s[0]), s[1]});
    } 

  for (int mask = 0; mask < 1 << 9; mask++)
    if (mask & onTable && ok(mask))
    {
      cout << "COVER" << endl;
      return 0;
    }

  cout << "TAKE" << endl;
}