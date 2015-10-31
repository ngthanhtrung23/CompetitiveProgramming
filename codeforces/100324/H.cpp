#include <bits/stdc++.h>
using namespace std;

long long eval(vector <string> a, char firstMove)
{
  long long res = 0;
  for (auto s : a)
    for (int i = 0, start = 1, value = 1 << 19; i < s.size(); i++)
    {
      if (i && s[i] != s[i - 1])
        start = 0;
      if (!start) 
        value >>= 1;
      if (s[i] == firstMove) res += value;
      else res -= value;
    }
  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("pebbles.in", "r", stdin);
  freopen("pebbles.out", "w", stdout);

  int n;
  cin >> n;
  vector <string> a;
  string s;
  for (int i = 0; i < n; i++)
  {
    cin >> s;
    a.push_back(s);
  }

  long long ans = eval(a, 'B');
  if (ans <= 0) cout << "Mike" << endl;
  else
  {
    cout << "Andrew" << endl;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < a[i].size(); j++)
        if (a[i][j] == 'B')
        {
          string tmp = a[i];
          a[i] = a[i].substr(0, j);
          if (eval(a, 'R') <= 0)
          {
            cout << i + 1 << ' ' << j + 1 << endl;
            return 0;
          }
          a[i] = tmp;
        }
    assert(0);
  }
}