#include <bits/stdc++.h>
using namespace std;
const long long oo = 1LL << 50;

pair <int, string> addictions[1010];
int n, k;
long long f[1010], best[10100];

void write(int n)
{
  vector <string> names;
  long long ans = 0;
  for (int i = 0; i < n; i++)
  {
    ans += f[i];
    names.push_back(addictions[i].second);
  }
  cout << n << ' ' << ans << endl;
  sort(names.begin(), names.end());
  for (auto x : names)
    cout << x << endl;
}

int main()
{
  ios::sync_with_stdio(0);
  freopen("addict.in", "r", stdin);
  freopen("addict.out", "w", stdout);

  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> addictions[i].second >> addictions[i].first;

  sort(addictions, addictions + n);  
  for (int i = 1; i <= 10000; i++)
    best[i] = oo;

  for (int i = 0; i < n; i++)
  {
    int str = addictions[i].first;
    if (str <= k) f[i] = 1;
    else
    {
      f[i] = oo;
      for (int j = max(0, str - k); j <= str; j++)
        f[i] = min(f[i], best[j] + 1);

      if (f[i] == oo)
      {
        write(i);
        return 0;
      }
    }

    
    for (int j = 10000; j >= str; j--)
      if (best[j - str] < oo)
        best[j] = min(best[j], best[j - str] + f[i]);
  }

  write(n);
}