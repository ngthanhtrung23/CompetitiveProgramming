#include <bits/stdc++.h>
using namespace std;

int n, f[1000100];
char tr[101][1000100];
vector <int> ans;

int solve(int p, int a[], int q, int b[])
{
  memset(f, 0, sizeof f);
  memset(tr, 0, sizeof tr);
  for (int i = 1; i <= n; i++)
    for (int j = p; j >= a[i]; j--)
      if (f[j] < f[j - a[i]] + b[i])
      {
        f[j] = f[j - a[i]] + b[i];
        tr[i][j] = 1;
      }

  if (f[p - 1] >= q)
  {
    ans.clear();
    for (int i = n, j = p - 1; i; i--)
      if (tr[i][j])
      {
        ans.push_back(1);
        j -= a[i];
      }
      else ans.push_back(0);
    reverse(ans.begin(), ans.end());
    return 1;
  }

  return 0;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int p, q, a[111], b[111];
  cin >> n >> p;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  cin >> q;
  for (int i = 1; i <= n; i++)
    cin >> b[i];

  if (solve(p, a, q, b) || solve(q, b, p, a))
  {
    cout << "NO" << endl;
    for (auto u : ans)
      cout << u;
  }
  else cout << "YES" << endl;
}