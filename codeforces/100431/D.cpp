#include <bits/stdc++.h>
using namespace std;

int n, a[222], id[222], active[222][222], deg[222];
vector <int> edge[222];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("bubble.in", "r", stdin);
  freopen("bubble.out", "w", stdout);
  cin >> n;
  for (int i = 1; i < n; i++)
    for (int j = 1; j <= i; j++)
      cin >> active[i][j];

  for (int i = 1; i <= n; i++)
    id[i] = i;

  for (int i = 1; i < n; i++)
    for (int j = n - 1; j >= i; j--)
      if (active[j][i])
      {
        edge[id[j + 1]].push_back(id[j]);
        deg[id[j]]++;
        swap(id[j], id[j + 1]);
      }
      else 
      {
        edge[id[j]].push_back(id[j + 1]);
        deg[id[j + 1]]++;
      }

  queue <int> q;
  for (int i = 1; i <= n; i++)
    if (!deg[i])
      q.push(i);

  for (int i = 1; i <= n; i++)
    if (q.empty())
    {
      cout << "NO" << endl;
      return 0;
    }
    else
    {
      int x = q.front();
      a[x] = i;
      q.pop();
      for (int y : edge[x])
        if (!--deg[y])
          q.push(y);
    }

  cout << "YES" << endl;
  for (int i = 1; i <= n; i++)
    cout << a[i] << ' ';
}