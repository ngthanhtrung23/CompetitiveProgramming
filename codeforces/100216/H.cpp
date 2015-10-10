#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  freopen("sand.in", "r", stdin);
  freopen("sand.out", "w", stdout);
  double h, r, s;
  int m;
  cin >> h >> r >> s >> m;
  for (int i = 0; i < m; i++)
    cout << fixed << setprecision(9) << sqrt(r * r + h * h) * s / h * pow(1. * (m - i) / m, 1. / 3) << endl;
}