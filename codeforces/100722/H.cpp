#include <bits/stdc++.h>
using namespace std;

int n, L, x[555], y[555], minY[555];
double area[555];

double calcY(int i, double xMid)
{
  int dx = x[i + 1] - x[i], dy = abs(y[i + 1] - y[i]);
  if (y[i] < y[i + 1])
  {
    double h = 1. * (xMid - x[i]) * dy / dx;
    return h + y[i];
  }
  else
  {
    double h = 1. * (x[i + 1] - xMid) * dy / dx;
    return h + y[i + 1];
  }
}

double calc(int i, int j, double xRight)
{
  double xLeft = xRight - L;
  double curArea = area[j] - area[i + 1];

  double yLeft = calcY(i, xLeft);
  double yRight = calcY(j, xRight);

  curArea += 0.5 * (x[i + 1] - xLeft) * (y[i + 1] + yLeft);
  curArea += 0.5 * (xRight - x[j]) * (y[j] + yRight);
  curArea -= min(minY[j] * 1., min(yLeft, yRight)) * L;
  return curArea;
}

double solve()
{
  double ans = 1e15;
  area[0] = 0;
  for (int i = 1; i < n; i++)
    area[i] = area[i - 1] + 0.5 * (x[i] - x[i - 1]) * (y[i] + y[i - 1]);

  for (int i = 0; i + 1 < n; i++)
  {
    // inside 1 segment
    int dx = x[i + 1] - x[i], dy = abs(y[i + 1] - y[i]), cx = x[i] + L;
    if (cx <= x[i + 1]) 
    {
      if (y[i] < y[i + 1])
      {
        double h = 1. * L * dy / dx;
        ans = min(ans, L * h / 2);
      }
      else
      {
        double h = 1. * (dx - L) * dy / dx;
        ans = min(ans, L * (dy - h) / 2);
      }
    }

    minY[i + 1] = y[i + 1];
    for (int j = i + 2; j < n; j++) minY[j] = min(minY[j - 1], y[j]);

    // >= 2 segments
    for (int j = i + 1; j + 1 < n; j++)
    {
      int lx = max(x[i] + L, x[j]), rx = min(x[i + 1] + L, x[j + 1]);
      if (lx > rx) continue;
      double xLow = lx, xHigh = rx;
      for (int iter = 0; iter < 500; iter++)
      {
        double xMid1 = (xLow * 2 + xHigh) / 3;
        double xMid2 = (xLow + xHigh * 2) / 3;
        double area1 = calc(i, j, xMid1);
        double area2 = calc(i, j, xMid2);

        if (area1 < area2) xHigh = xMid2;
        else xLow = xMid1;
      }

      ans = min(ans, calc(i, j, xLow));
    }
  }

  return ans;
}

int main()
{
  ios::sync_with_stdio(0);
  int test;
  cin >> test;
  while (test--)
  {
    cin >> n >> L;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    double ans = solve();
    for (int i = 0; i < n; i++) x[i] = 10000 - x[i];
    reverse(x, x + n);
    reverse(y, y + n);
    ans = min(ans, solve());

    cout << fixed << setprecision(4) << ans << endl;
  } 
}