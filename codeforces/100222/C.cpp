#include <bits/stdc++.h>
using namespace std;

int n, m, len, t, nex[222][26], tr[1010][222];
string words[222];
long double f[1010][222], p[1010][26];

int ok(int i, char c, int k)
{
  for (int j = 1; j < len; j++)
    if (words[k][j - 1] != words[i][j])
      return 0;
  return words[k][len - 1] == c;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("decoding.in", "r", stdin);
  freopen("decoding.out", "w", stdout);  
  cin >> m >> len >> t;
  for (int i = 0; i < m; i++)
    cin >> words[i];

  cin >> n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < t; j++)
      cin >> p[i][j];

  for (int i = 0; i < m; i++)
    for (int j = 0; j < t; j++)
    {
      nex[i][j] = -1;
      for (int k = 0; k < m; k++)
        if (ok(i, char('a' + j), k))
          nex[i][j] = k;
    }

  for (int i = 0; i < m; i++)
  {
    f[len - 1][i] = 1;
    for (int j = 0; j < len; j++)
      f[len - 1][i] *= p[j][words[i][j] - 'a'];
  }

  for (int i = len; i < n; i++)
    for (int j = 0; j < m; j++)
      for (int c = 0; c < t; c++)
        if (nex[j][c] >= 0 && f[i][nex[j][c]] < f[i - 1][j] * p[i][c])
        {
          f[i][nex[j][c]] = f[i - 1][j] * p[i][c];
          tr[i][nex[j][c]] = j;
        }

  long double best = 0;
  int bestJ = -1;
  for (int j = 0; j < m; j++)
    if (f[n - 1][j] > best)
    {
      bestJ = j;
      best = f[n - 1][j];
    }

  if (bestJ < 0) cout << "---\n";
  else
  {
    string ans = "";
    for (int i = n - 1; i >= len; i--)
    {
      int j = tr[i][bestJ];
      for (int c = 0; c < t; c++)
        if (nex[j][c] == bestJ)
        {
          ans += char('a' + c);
          break;
        }
      bestJ = j;
    }
    cout << words[bestJ];
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
  }
}