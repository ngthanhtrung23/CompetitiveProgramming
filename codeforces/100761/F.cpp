#include <bits/stdc++.h>
using namespace std;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int n, m, a[222][222];

void solve()
{
  int stop = 1;
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      if (a[i][j])
      {
        stop = 0;
        if (a[i][j] == 1)
        {
          for (int k = 0; k < 4; k++)
          {
            int ii = i + dx[k], jj = j + dy[k];
            if (ii && jj && ii <= m && jj <= n && a[ii][jj])
            {
              if (a[ii][jj] == 1)
              {
                cout << "No solution" << endl;
                exit(0);
              }
              a[ii][jj]--;
            }
          }
          a[i][j]--;
          solve();
          cout << i << ' ' << j << '\n';
          return;
        }
      }

  if (!stop)
  {
    cout << "No solution" << endl;
    exit(0);
  }
}

int main()
{
  cin >> m >> n;
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      cin >> a[i][j];
  solve();
}