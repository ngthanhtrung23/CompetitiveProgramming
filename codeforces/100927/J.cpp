#include <bits/stdc++.h>
using namespace std;

int main()
{
  freopen("way.in", "r", stdin);
  freopen("way.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  double prob[22][22], probA[22], probB[22];
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> probA[i];
  for (int i = 0; i < m; i++)
    cin >> probB[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> prob[i][j];

  double ans = 1;
  for (int mask = 0; mask < 1 << n; mask++)
  {
    double curProb = 1;
    for (int i = 0; i < n; i++)
      if (mask >> i & 1) curProb *= probA[i];
      else curProb *= 1 - probA[i];

    for (int j = 0; j < m; j++)
    {
      double probLeft = 1;
      for (int i = 0; i < n; i++)
        if (mask >> i & 1)
          probLeft *= 1 - prob[i][j];
      curProb *= 1 - (1 - probLeft) * probB[j];
    }

    ans -= curProb;
  }

  cout << fixed << setprecision(9) << ans << endl;
}