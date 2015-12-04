#include <bits/stdc++.h>
using namespace std;
const int oo = 27081993;

int solve(vector <int> a, vector <int> b, int n)
{
  int res = 0;
  for (int i = 0; i < n; i++)
    if (a[i] != b[i])
      for (int j = i + 1; j < n; j++)
        if (a[j] == b[i])
        {
          for (int k = j; k > i; k--)
          {
            swap(a[k], a[k - 1]);
            res++;
          }
          break;
        }

  for (int i = 0; i < n; i++)
    if (a[i] != b[i])
      return oo;

  return res;
}

int main()
{
  ios::sync_with_stdio(0);
  int n, m, s[22];
  vector <int> a(22), b(22);
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> a[i];

  for (int i = 0; i < m; i++)
    cin >> s[i];

  for (int i = 0, j = 0, v = 0; j < m; j++, v ^= 1)
    for (int k = 0; k < s[j]; k++)
      b[i++] = v;

  int ans = solve(a, b, n);

  for (int i = 0, j = 0, v = 1; j < m; j++, v ^= 1)
    for (int k = 0; k < s[j]; k++)
      b[i++] = v;  

  ans = min(ans, solve(a, b, n));

  cout << ans << endl;
}