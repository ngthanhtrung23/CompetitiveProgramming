#include <bits/stdc++.h>
using namespace std;
const long long oo = 1LL << 50;

int m, n, s[111], r[111];

int ok(long long day)
{
  multiset < pair<long long,int> > projects;
  for (int i = 0; i < n; i++)
    projects.insert({-day, s[i]});

  int done = 0, flag[111] = {0};
  while (done < m)
  {
    if (projects.empty())
      return 0;

    auto u = projects.begin();
    projects.erase(u);
    long long newTime = - u->first - u->second;
    for (int i = 0; i < m; i++)
      if (!flag[i] && r[i] - 1 <= newTime)
      {
        projects.insert({-newTime, u->second});
        flag[i] = 1;
        done++;
        break;
      }
  }

  return 1;
}

int main()
{
  freopen("budget.in", "r", stdin);
  freopen("budget.out", "w", stdout);
  int P;
  cin >> n >> m >> P;
  for (int i = 0; i < n; i++)
  {
    cin >> s[i];
    s[i] = (P + s[i] - 1) / s[i];
  }
  for (int i = 0; i < m; i++)
    cin >> r[i];

  sort(s, s + n);
  sort(r, r + m, greater<int>());

  long long low = 1, high = oo - 1, ans = oo;
  while (low <= high)
  {
    long long mid = (low + high) / 2;
    if (ok(mid))
    {
      ans = mid;
      high = mid - 1;
    }
    else low = mid + 1;
  }

  cout << ans << endl;
}