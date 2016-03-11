#include <bits/stdc++.h>
using namespace std;

int m, n, a[200200], b[200200];

int ok(int target)
{
  int i = 0, j = target - 1, level = 0, socket = 1;
  while (socket <= j)
  {
    while (j >= 0 && b[j] == level)
      if (!socket) return 0;
      else
      {
        socket--;
        j--;
      }

    int plugUse = min(socket, m - i);
    j -= socket - plugUse;

    socket = 0;
    while (plugUse--)
      socket = min(n, socket + a[i++]);
    level++;
  }

  return 1;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> m >> n;
  for (int i = 0; i < m; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];

  sort(a, a + m, greater<int>());
  sort(b, b + n, greater<int>());

  int low = 1, high = n, ans = 0;
  while (low <= high)
  {
    int mid = (low + high) / 2;
    if (ok(mid))
    {
      ans = mid;
      low = mid + 1;
    }
    else high = mid - 1;
  }

  cout << ans << endl;
}