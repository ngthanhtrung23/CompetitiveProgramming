#include <bits/stdc++.h>
using namespace std;
const long long oo = 1LL << 60;

int n;
pair <long long,long long> a[100100];

int main()
{
  freopen("pulp.in", "r", stdin);
  freopen("pulp.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i].first >> a[i].second;

  sort(a, a + n);
  long long ans = 0, t = 0;
  set < pair<long long,long long> > s;

  for (int i = 0; i < n || !s.empty();)
  {
    long long dif = i < n ? a[i].first - t : oo;
    if (!s.empty() && s.begin() -> first <= dif)
    {
      t += s.begin() -> first;
      ans += t;
      s.erase(s.begin());
    }
    else
    {
      if (!s.empty())
      {
        auto u = s.begin();
        s.erase(u);
        s.insert({u -> first - dif, u -> second});
      }
      s.insert({a[i].second, i});
      t = a[i++].first;
    }
  }

  cout << ans << endl;
}