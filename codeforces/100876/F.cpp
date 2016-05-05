#include <bits/stdc++.h>
using namespace std;

int m, n, mm, nn, saveM, saveN;
string s[111], t[111], ss[111];
double area[111][111];

void rotate(string s[])
{
  string tmp[111];
  for (int i = 1; i <= n; i++)
    tmp[i] = " ";
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      tmp[j] += s[m - i + 1][j];
  swap(m, n);
  for (int i = 1; i <= m; i++)
    s[i] = tmp[i];
}

void ver(string s[])
{
  for (int i = 1; i <= m / 2; i++)
    swap(s[i], s[m - i + 1]);
}

void hor(string s[])
{
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n / 2; j++)
      swap(s[i][j], s[i][n - j + 1]);
}

int match(string s[])
{
  for (int i = 1; i <= mm; i++)
    for (int j = 1; j <= nn; j++)
      area[i][j] = 0;

  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      if (s[i][j] == '1')
      {
        int x = (i - 1) * mm / m, xx = (i * mm + m - 1) / m;
        int y = (j - 1) * nn / n, yy = (j * nn + n - 1) / n;
        for (int ii = x + 1; ii <= xx; ii++)
          for (int jj = y + 1; jj <= yy; jj++)
          {
            double minX = max((i - 1.) * mm / m, ii - 1.);
            double maxX = min(1. * i * mm / m, 1. * ii);
            double minY = max((j - 1.) * nn / n, jj - 1.);
            double maxY = min(1. * j * nn / n, 1. * jj);
            area[ii][jj] += (maxY - minY) * (maxX - minX);
          }
      }

  for (int i = 1; i <= mm; i++)
    for (int j = 1; j <= nn; j++)
      if (fabs(area[i][j] - 0.5) > 1e-8)
        if (area[i][j] > 0.5 ^ ss[i][j] == '1')
          return 0;
  
  return 1;
}

int check()
{
  for (int h = 0; h < 2; h++)
    for (int v = 0; v < 2; v++)
    {
      m = saveM;
      n = saveN;
      for (int i = 1; i <= m; i++)
        t[i] = s[i];
      if (h)
        hor(t);
      if (v)
        ver(t);
      for (int r = 0; r < 4; r++)
      {
        if (match(t))
          return 1;
        rotate(t);
      }
    }
  return 0;
}

int main()
{
  freopen("images.in", "r", stdin);
  freopen("images.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> m >> n;
  saveM = m;
  saveN = n;
  for (int i = 1; i <= m; i++)
  {
    cin >> s[i];
    s[i] = " " + s[i];
  }
  cin >> mm >> nn;
  for (int i = 1; i <= mm; i++)
  {
    cin >> ss[i];
    ss[i] = " " + ss[i];
  }

  if (check())
  {
    cout << "YES" << endl;
    return 0;
  }

  m = saveM;
  n = saveN;
  swap(m, mm);
  swap(n, nn);
  saveM = m;
  saveN = n;
  for (int i = 1; i <= max(m, mm); i++)
    swap(s[i], ss[i]);

  if (check())
  {
    cout << "YES" << endl;
    return 0;
  }

  cout << "NO" << endl;
}