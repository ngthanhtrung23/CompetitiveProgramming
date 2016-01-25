#include <bits/stdc++.h>
using namespace std;

double f[111], g[111];
int n, m, s, p[111], w[111];

int main()
{
  freopen("casino.in", "r", stdin);
  freopen("casino.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m >> s;
  for (int i = 0; i < m; i++)
    cin >> p[i] >> w[i];

  for (int i = 1; i <= 100; i++)
    f[i] = (i <= n ? 0.5 : 1);

  for (int turn = 0; turn <= 10000; turn++)
  {
    for (int i = 1; i <= n; i++)
    {
      g[i] = 0;
      for (int j = 0; j < m; j++)
        g[i] = max(g[i], f[i - 1] * (s - p[j]) / s + f[i + w[j]] * p[j] / s);
    }

    for (int i = 1; i <= n; i++)
      f[i] = g[i];
  }
  cout << fixed << setprecision(9) << f[n] << endl;
}