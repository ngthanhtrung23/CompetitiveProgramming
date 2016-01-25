#include <bits/stdc++.h>
using namespace std;
const int BASE = 97;

int main()
{
  freopen("pattern.in", "r", stdin);
  freopen("pattern.out", "w", stdout);
  string s;
  cin >> s;
  int n = s.size();
  vector < pair<long long,int> > a;

  for (int i = 0; i < n; i++)
  {
    int has[26] = {0}, cur = 0;
    long long h = 0;
    for (int j = i; j < n; j++)
    {
      int ch = s[j] - 'a';
      if (!has[ch])
        has[ch] = ++cur;
      h = h * BASE + has[ch];
      a.push_back({h, i * n + j});
    }
  }

  sort(a.begin(), a.end());
  int ans = 0, res = -1;
  for (int i = 0; i < a.size();)
  {
    int len = a[i].second % n - a[i].second / n + 1;
    int j = i + 1;
    while (j < a.size() && a[j].first == a[i].first)
      j++;
    if ((j - i) * len > ans)
    {
      ans = (j - i) * len;
      res = a[i].second;
    }
    i = j;
  }

  cout << s.substr(res / n, res % n - res / n + 1) << endl;
}