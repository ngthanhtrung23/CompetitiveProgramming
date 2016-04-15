#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, X, t, x;
  set <int> s[2];
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> X;
  for (int i = 0; i < n; i++)
  {
    cin >> x >> t;
    s[t].insert(x);
  }

  x = X;
  t = 0;
  int ans = 0;
  while (1)
  {
    if (!t)
    {
      auto it = s[0].upper_bound(x);
      if (it == s[0].begin()) 
      {
        ans++;
        x = 0;
      }
      else 
      {
        x = *--it;
        s[0].erase(x);
      }
      t = 1;
    }
    else
    {
      auto it = s[1].lower_bound(x);
      if (it == s[1].end())
        break;
      x = *it;
      s[1].erase(x);
      t = 0;
    }
  }

  if (s[0].empty() && s[1].empty()) cout << ans << endl;
  else cout << -1 << endl;
}