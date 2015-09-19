#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  freopen("assign.in", "r", stdin);
  freopen("assign.out", "w", stdout);

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; j++)
      if (i <= j) cout << 1 << ' ';
      else cout << 0 << ' ';
    cout << endl;
  }
}
