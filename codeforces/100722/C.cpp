#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);

int main()
{
  ios::sync_with_stdio(0);
  int test;
  cin >> test;
  while (test--)
  {
    int r[10100], n, f;
    cin >> n >> f;
    for (int i = 0; i < n; i++) cin >> r[i];
    f++;
    double low = 0, high = 1e8;
    for (int it = 0; it < 100; it++)
    {
      double mid = (low + high) / 2;
      int cnt = 0;
      for (int i = 0; i < n; i++)
        cnt += int(1.0 * r[i] * r[i] / mid);
      if (cnt >= f) low = mid;
      else high = mid;
    }
    cout << fixed << setprecision(4) << low * PI << endl;
  }  
}