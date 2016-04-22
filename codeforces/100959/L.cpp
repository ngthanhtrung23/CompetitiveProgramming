#include <bits/stdc++.h>
using namespace std;

char f[5050][5050], isGood[5050];

int main()
{
  string s, t;
  cin >> s >> t;
  int m = s.size(), n = t.size();

  if (s[0] != t[0])
  {
    cout << "No" << endl;
    return 0;
  }

  f[0][0] = 1;
  for (int i = 0; i < m; i++)
    for (int j = i; j < n; j++)
    {
      if (f[i][j] && s[i] == t[j])
      {
        f[i + 1][j + 1] = 1;
        if (j + 1 < n && t[j + 1] != t[j])
          isGood[i + 1] = 1;
      }
      else f[i + 1][j + 1] = isGood[i + 1];
    }

  cout << (f[m][n] ? "Yes" : "No") << endl;
}