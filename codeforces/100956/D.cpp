#include <bits/stdc++.h>
using namespace std;

int n;
pair <int,int> a[100100];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i].first;
  for (int i = 0; i < n; i++)
    cin >> a[i].second;
  sort(a, a + n, greater< pair<int,int> >());

  multiset <int> s;
  for (int i = 1; i < n; i += 2)
  {
    s.insert(a[i].second);
    if (i + 1 < n)
    {
      s.insert(a[i + 1].second);
      s.erase(s.begin());
    }
  }

  long long ans = 0;
  for (auto x : s)
    ans += x;
  cout << ans << endl;
}