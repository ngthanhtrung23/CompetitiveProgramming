#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, cnt[10100] = {0}, x, ans = 0;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> x;
    ans = max(ans, ++cnt[x]);
  }
  cout << ans << endl;
}