#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  int m, n, x;
  vector < pair<int,int> > a;
  cin >> m >> n;
  for (int i = 1; i <= m; i++)
  {
    cin >> x;
    a.push_back({x, i});
  }
  for (int i = 1; i <= n; i++)
  {
    cin >> x;
    a.push_back({x, -i});
  }

  sort(a.begin(), a.end());
  long long ans = 0;
  long long sumIndexA = 0, sumIndexB = 0;
  long long sumValueA = 0, sumValueB = 0;
  long long sumProductA = 0, sumProductB = 0;
  long long cntA = 0, cntB = 0;
  for (auto u : a)
    if (u.second > 0)
    {
      int value = u.first, index = u.second;
      ans += value * (1LL * index * cntB - sumIndexB);
      ans += sumProductB - sumValueB * index;
      cntA++;
      sumProductA += 1LL * value * index;
      sumIndexA += index;
      sumValueA += value;
    } 
    else
    {
      int value = u.first, index = -u.second;
      ans -= value * (1LL * index * cntA - sumIndexA);
      ans -= sumProductA - sumValueA * index;
      cntB++;
      sumProductB += 1LL * value * index;
      sumIndexB += index;
      sumValueB += value;
    }

  cout << ans << endl;
}