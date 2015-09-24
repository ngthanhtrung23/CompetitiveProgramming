#include <bits/stdc++.h>
using namespace std;

int n, num[44], coef[44], id[44][44], f[44][11][11][22], res[10][10];
int tr[44][11][11][22];
vector < vector <int> > rest;

void update(int &x, int y, int &t, int type)
{
  if (y > x)
  {
    x = y;
    t = type;
  }
}

int fill(vector <int> ids)
{
  int sz = ids.size();
  for (int i = 0; i < 10; i++)
    for (int j = 0; j + sz <= 4; j++)
    {
      int ok = 1;
      for (int k = 0; k < sz; k++)
        if (res[i][j + k])
          ok = 0;

      if (ok)
      {
        for (int k = 0; k < sz; k++)
          res[i][j + k] = ids[k];
        return 1;
      }
    }

  return 0;
}

vector <int> group(int i, int j, int sz = 1)
{
  vector <int> res;
  for (int k = 0; k < sz; k++)
    res.push_back(id[i][j + k]);
  return res;
}

void trace(int i, int n4, int n3, int n2)
{
  if (!i) return;
  switch (tr[i][n4][n3][n2]) {
    case 0:
      for (int j = 0; j < num[i]; j++)
        rest.push_back(group(i, j));
      trace(i - 1, n4, n3, n2);
      break;
    case 1:
      assert(fill(group(i, 0, 2)));
      for (int j = 2; j < num[i]; j++)
        rest.push_back(group(i, j));
      trace(i - 1, n4, n3, n2 - 1);
      break;
    case 2:
      assert(fill(group(i, 0, 3)));
      for (int j = 3; j < num[i]; j++)
        rest.push_back(group(i, j));
      trace(i - 1, n4, n3 - 1, n2);
      break;
    case 3:
      assert(fill(group(i, 0, 2)));
      assert(fill(group(i, 2, 2)));
      trace(i - 1, n4, n3, n2 - 2);
      break;
    case 4:
      assert(fill(group(i, 0, 4)));
      trace(i - 1, n4 - 1, n3, n2);
  }
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("tickets.in", "r", stdin);
  freopen("tickets.out", "w", stdout);

  cin >> n;
  for (int i = 1; i <= n; i++)
  {
    cin >> num[i] >> coef[i];
    for (int j = 0; j < num[i]; j++)
      cin >> id[i][j];
  }

  int ans = 0, r4 = 0, r3 = 0, r2 = 0;
  for (int i = 1; i <= n; i++)
    for (int n4 = 0; n4 < 10; n4++)
      for (int n3 = 0; n3 + n4 < 10; n3++)
        for (int n2 = 0; (n2 + 1) / 2 + n3 + n4 < 10; n2++)
        {
          int &F = f[i][n4][n3][n2], &T = tr[i][n4][n3][n2];
          F = f[i - 1][n4][n3][n2];
          if (num[i] >= 2 && n2)
            update(F, f[i - 1][n4][n3][n2 - 1] + coef[i] * 2, T, 1);
          if (num[i] >= 3 && n3)
            update(F, f[i - 1][n4][n3 - 1][n2] + coef[i] * 6, T, 2);
          if (num[i] >= 4)
          {
            if (n2 >= 2)
              update(F, f[i - 1][n4][n3][n2 - 2] + coef[i] * 4, T, 3);
            if (n4)
              update(F, f[i - 1][n4 - 1][n3][n2] + coef[i] * 12, T, 4);
          }

          if (F > ans && i == n)
          {
            ans = F;
            r4 = n4;
            r3 = n3;
            r2 = n2;
          }
        }

  cout << ans << endl;
  trace(n, r4, r3, r2);
  for (auto g : rest) {
    assert(fill(g));
  }

  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 4; j++)
      cout << res[i][j] << (j == 3 ? '\n' : ' ');
  cout << endl;
}
