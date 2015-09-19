#include <bits/stdc++.h>
using namespace std;

int n, a[3333];
short f[3333][3333], tr[3333][3333];
unordered_map <int,int> id;

int main()
{
  ios::sync_with_stdio(0);
  freopen("fibsubseq.in", "r", stdin);
  freopen("fibsubseq.out", "w", stdout);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  if (n == 1)
  {
    cout << 1 << endl << a[1] << endl;
    return 0;
  }

  int ans = 0, ri, rj;
  for (int i = 1; i < n; i++)
  {
    for (int j = i + 1; j <= n; j++)
    {
      f[i][j] = 2;
      if (id.count(a[j] - a[i])) 
      {
        int k = id[a[j] - a[i]];
        if (f[k][i] + 1 > f[i][j])
        {
          f[i][j] = f[k][i] + 1;
          tr[i][j] = k;
        }
      }

      if (f[i][j] > ans)
      {
        ans = f[i][j];
        ri = i;
        rj = j;
      }
    }
    id[a[i]] = i;
  }

  vector <int> seq(1, a[rj]);
  while (ri)
  {
    seq.push_back(a[ri]);
    int tmp = ri;
    ri = tr[ri][rj];
    rj = tmp;
  }

  cout << ans << endl;
  for (int i = ans - 1; i >= 0; i--)
    cout << seq[i] << ' ';
}