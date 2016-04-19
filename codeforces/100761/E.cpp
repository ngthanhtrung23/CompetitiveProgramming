#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int a, b = 0, g, n, x;
  cin >> a >> g >> n;
  vector < pair<int,int> > ans;
  while (n--)
  {
    cin >> x;
    if (x == b + g) ans.push_back({0, 0});
    else if (x < b + g)
    {
      if (x < b) 
      {
        cout << "ERROR\n";
        return 0;
      }
      ans.push_back({0, b + g - x});
      g = x - b;
    }
    else
    {
      if (x > a + g)
      {
        cout << "ERROR\n";
        return 0;
      }
      ans.push_back({x - b - g, 0});
      b = x - g;
    }
  }

  for (auto u : ans)
    cout << u.first << ' ' << u.second << '\n';
}