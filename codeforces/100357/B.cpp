#include <bits/stdc++.h>
using namespace std;

char a[555][555];

int main()
{
  freopen("chip.in", "r", stdin);
  freopen("chip.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int m, n, h, x, ok = 1, row[555], col[555];
  cin >> m >> n >> h;
  
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      a[i][j] = '*';

  for (int i = 1; i <= m; i++)
    cin >> row[i];

  for (int i = 1; i <= n; i++)
    cin >> col[i];

  for (int i = 1; i <= m; i++)
  {
    int colNeed = n - row[i];
    vector < pair<int,int> > cols;
    for (int j = 1; j <= n; j++)
      if (a[i][j] == '*' && col[j])
        cols.push_back({-col[j], j});
      else if (a[i][j] == '+' || a[i][j] == '|')
        colNeed--;

    sort(cols.begin(), cols.end());
    if (cols.size() < colNeed)
    {
      ok = 0;
      break;
    }

    for (int j = 0; j < colNeed; j++)
    {
      int c = cols[j].second;
      col[c]--; 
      a[i][c] = a[i + h - 1][c] = '+';
      for (int ii = i + 1; ii < i + h - 1; ii++)
        a[ii][c] = '|';
    }
  }

  for (int i = 1; i <= n; i++)
    if (col[i])
      ok = 0;

  if (!ok) cout << "inconsistent" << endl;
  else
    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= n; j++)
        cout << a[i][j];
      cout << endl;
    }
}