#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-8;

int main()
{
  freopen("bujor.in", "r", stdin);
  freopen("bujor.out", "w", stdout);
  int test, n, used[222];
  double a[222][222], b[222][222];
  cin >> test;
  while (test--)
  {
    cin >> n;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        scanf("%lf", a[i] + j);
        b[i][j] = i == j ? 1 : 0;
      }

    memset(used, -1, sizeof used);
    for (int j = 0; j < n; j++)
    {
      int row = -1;
      for (int i = 0; i < n; i++)
        if (used[i] < 0 && fabs(a[i][j]) > EPS)
        {
          row = i;
          break;
        }

      if (row < 0) continue;
      used[row] = j;

      for (int i = 0; i < n; i++)
        if (used[i] < 0 && fabs(a[i][j]) > EPS)
        {
          double coef = 1. * a[i][j] / a[row][j];
          for (int jj = j; jj < n; jj++)
            a[i][jj] -= coef * a[row][jj];
          for (int jj = 0; jj < n; jj++)
            b[i][jj] -= coef * b[row][jj];
        }
    }

    for (int j = n - 1; j >= 0; j--)
    {
      int row = -1;
      for (int i = 0; i < n; i++)
        if (used[i] == j)
        {
          row = i;
          break;
        }

      if (row < 0)
        continue;

      double cur = a[row][j];
      for (int jj = 0; jj < n; jj++)
      {
        a[row][jj] /= cur;
        b[row][jj] /= cur;
      }

      for (int i = 0; i < n; i++)
        if (used[i] < j)
        {
          double coef = a[i][j];
          for (int jj = 0; jj <= n; jj++) 
          {
            a[i][jj] -= coef * a[row][jj];
            b[i][jj] -= coef * b[row][jj];
          }
        }
    }

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        printf("%.12lf%c", b[i][j], (j == n - 1 ? '\n' : ' '));
  }
}