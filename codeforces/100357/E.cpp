#include <bits/stdc++.h>
using namespace std;
const int BASE = 997;

vector <int> win[55];
vector < pair<long long,int> > a[55];
long long p[55];

int isLose(int len, long long h)
{
  int id = lower_bound(a[len].begin(), a[len].end(), make_pair(h, 0)) - a[len].begin();
  return id < a[len].size() && a[len][id].first == h && !win[len][id];
}

int main()
{
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  int m;
  string s;
  cin >> m;
  while (m--)
  {
    cin >> s;
    for (int j = 0; j < s.size(); j++)
    {
      long long h = 0;
      for (int k = j; k < s.size(); k++)
      {
        h = h * BASE + s[k];
        a[k - j + 1].push_back({h, k - j + 1 == s.size()});
      }
    }
  }

  for (int i = 0; i <= 50; i++)
    p[i] = i ? p[i - 1] * BASE : 1;

  a[0].push_back({0, 0});
  for (int len = 50; len >= 0; len--)
  {
    sort(a[len].begin(), a[len].end());
    int n = 1;
    for (int i = 1; i < a[len].size(); i++)
      if (a[len][i].first == a[len][n - 1].first) a[len][n - 1] = a[len][i]; 
      else a[len][n++] = a[len][i];
    a[len].resize(n);

    for (int i = 0; i < n; i++)
      if (a[len][i].second) win[len].push_back(1);
      else
      {
        win[len].push_back(0);
        for (char c = 33; c <= 126; c++)
        {
          long long hLeft = c * p[len] + a[len][i].first;
          long long hRight = a[len][i].first * BASE + c;
          if (isLose(len + 1, hLeft) || isLose(len + 1, hRight))
          {
            win[len][i] = 1;
            break;
          }
        }
      }
  }

  if (win[0][0])
  {
    cout << "First" << endl;
    for (int i = 0; i < a[1].size(); i++)
      if (!win[1][i])
        cout << char(a[1][i].first);
  }
  else cout << "Second" << endl;
}