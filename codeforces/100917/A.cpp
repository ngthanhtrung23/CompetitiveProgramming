#include <bits/stdc++.h>
using namespace std;

int n, row[3333][256], col[3333][256], numRow[3333], numCol[3333], flagRow[3333], flagCol[3333];
string a[3333];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    for (int j = 0; j < n; j++)
      if (a[i][j] != '?')
      {
        if (!row[i][a[i][j]]++) numRow[i]++;
        if (!col[j][a[i][j]]++) numCol[j]++;
      }
  }

  queue <int> qRow, qCol;
  for (int i = 0; i < n; i++)
    if (numRow[i] <= 1)
    {
      flagRow[i] = 1;
      qRow.push(i);
    }
  for (int i = 0; i < n; i++)
    if (numCol[i] <= 1)
    {
      flagCol[i] = 1;
      qCol.push(i);
    }

  vector < pair<int,char> > ans;
  while (!qCol.empty() || !qRow.empty())
    if (!qRow.empty())
    {
      int x = qRow.front();
      qRow.pop();
      char c = 'a';
      if (numRow[x])
      {
        while (!row[x][c]) c++;
        for (int i = 0; i < n; i++)
          if (!flagCol[i] && a[x][i] == c)
            if (!--col[i][c])
              if (--numCol[i] <= 1)
              {
                flagCol[i] = 1;
                qCol.push(i);
              }
      }
      ans.push_back({x + 1, c});
    }
    else
    {
      int x = qCol.front();
      qCol.pop();
      char c = 'a';
      if (numCol[x])
      {
        while (!col[x][c]) c++;
        for (int i = 0; i < n; i++)
          if (!flagRow[i] && a[i][x] == c)
            if (!--row[i][c])
              if (--numRow[i] <= 1)
              {
                flagRow[i] = 1;
                qRow.push(i);
              }
      }
      ans.push_back({- x - 1, c});
    }

  reverse(ans.begin(), ans.end());
  for (auto u : ans)
    if (u.first > 0) cout << "h " << u.first << ' ' << u.second << '\n';
    else cout << "v " << -u.first << ' ' << u.second << '\n';
}