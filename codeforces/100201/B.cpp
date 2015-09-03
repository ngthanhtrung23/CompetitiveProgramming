#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);

int n, x[111], y[111];

int main()
{
  ios::sync_with_stdio(0);
  freopen("angle.in", "r", stdin);
  freopen("angle.out", "w", stdout);

  bool first = true;
  while (cin >> n, n) {
    if (first) first = false; else cout << endl;
    for (int i = 0; i < n; i++)
      cin >> x[i] >> y[i]; 

    long double total = 0;
    for (int i = 0; i + 1 < n; i++)
      total += atan2(y[i + 1] - y[i], x[i + 1] - x[i]) + PI * 2;

    int k = int(total / PI / 2);
    if (fabs(k * PI * 2 - total) > 1e-8) k++;
    long double ans = 0;
    if (n > 1) ans = (k * PI * 2 - total) / (n - 1);
    cout << fixed << setprecision(20) << 0.0 << endl;
    cout << fixed << setprecision(20) << ans << endl;

    for (int i = 0; i < n; i++)
    {
      long double xx = cos(ans) * x[i] - sin(ans) * y[i];
      long double yy = sin(ans) * x[i] + cos(ans) * y[i];
      cout << fixed << setprecision(20) << xx << ' ' << yy << endl;
    }
  }
}