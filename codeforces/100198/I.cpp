#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
const int INTERVAL = int(1e6);

double r1, r2;

double f(double x)
{
  return cos(x) * cos(x) * sqrt(r1 * r1 - r2 * r2 + r2 * r2 * cos(x) * cos(x));
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("twocyl.in", "r", stdin);
  freopen("twocyl.out", "w", stdout);
  cin >> r1 >> r2;
  if (r2 > r1) swap(r1, r2);

  double ans = 0;
  for (int i = 0; i < INTERVAL; i++)
  {
    double a = 1. * i / INTERVAL * PI / 2;
    double b = 1. * (i + 1) / INTERVAL * PI / 2;
    ans += (b - a) / 3 * (f(a) + 1 * f((a + b) / 2) + f(b));
  }

  cout << fixed << setprecision(6) << ans * 8 * r2 * r2 << endl;
}