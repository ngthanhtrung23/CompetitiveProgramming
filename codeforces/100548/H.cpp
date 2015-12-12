#include <bits/stdc++.h>
using namespace std;
const int oo = 27081993;

struct State
{
  int turn, bob, alice;
};

int n, canMove[111], f[2][111][111], deg[2][111][111];
queue <State> q;

void enqueue(State u, int v)
{
  if (f[u.turn][u.bob][u.alice] < 0)
  {
    f[u.turn][u.bob][u.alice] = v;
    q.push(u);
  }
}

int main()
{
  ios::sync_with_stdio(0);
  int test, m, x, y, bob, alice;
  cin >> test;
  for (int iTest = 1; iTest <= test; iTest++)
  {
    cin >> n >> m;
    vector <int> a[111];
    memset(canMove, 0, sizeof canMove);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        for (int k = 0; k < 2; k++)
        {
          deg[k][i][j] = 0;
          f[k][i][j] = -1;
        }

    while (m--)
    {
      cin >> x >> y;
      a[y].push_back(x);
      canMove[x] = 1;
    }
    cin >> bob >> alice;

    for (int k = 1; k <= n; k++)
      for (auto i : a[k])
        for (int j = 1; j <= n; j++)
          if (i != j)
          {
            deg[0][i][j]++;
            deg[1][j][i]++;
          }

    for (int i = 1; i <= n; i++)
      if (!canMove[i])
        for (int j = 1; j <= n; j++)
          if (i != j)
          {
            enqueue({0, i, j}, 0);
            enqueue({1, j, i}, 0);
          }

    for (int i = 1; i <= n; i++)
    {
      enqueue({0, i, i}, 0);
      enqueue({1, i, i}, 1);
    }

    while (!q.empty())
    {
      auto u = q.front();
      q.pop();

      if (!u.turn)
        for (auto i : a[u.alice])
        {
          if (!f[u.turn][u.bob][u.alice])
            enqueue({1, u.bob, i}, 1);
          else if (!--deg[1][u.bob][i])
            enqueue({1, u.bob, i}, 0);
        }
      else 
        for (auto i : a[u.bob])
        {
          if (!f[u.turn][u.bob][u.alice])
            enqueue({0, i, u.alice}, 1);
          else if (!--deg[0][i][u.alice])
            enqueue({0, i, u.alice}, 0);
        }
    }

    cout << "Case #" << iTest << ": " << (f[0][bob][alice] ? "Yes" : "No") << endl;
  }
}