#include <bits/stdc++.h>
using namespace std;

map <int,int> m;
int n, a[4040], M, f[4040], cnt[4040], tr[4040], trV[4040];

int main()
{
  ios::sync_with_stdio(0);
  freopen("rhymes.in", "r", stdin);
  freopen("rhymes.out", "w", stdout);

  cin >> n;
  for (int i = 1; i <= n; i++)
  {
    cin >> a[i];
    m[a[i]] = 0;
  }

  for (auto u : m)
    m[u.first] = ++M;

  for (int i = 1; i <= n; i++)
  {
    f[i] = f[i - 1];
    a[i] = m[a[i]];
    for (int j = 1; j <= M; j++)
      cnt[j] = 0;

    int maxV = 0;
    for (int j = i - 1; j; j--)
    {
      if (a[j] == a[i])
      {
        if (maxV && cnt[maxV] >= 2)
        {
          f[i] = max(f[i], f[j - 1] + 1);
          tr[i] = j;
          trV[i] = maxV;
          break;
        }
      }
      else if (cnt[a[i]] && cnt[a[j]])
      {
        f[i] = max(f[i], f[j - 1] + 1);
        tr[i] = j;
        break;
      }

      cnt[a[j]]++;
      if (!maxV || cnt[a[j]] > cnt[maxV])
        maxV = a[j];
    }
  }

  cout << f[n] << endl;

  vector <int> ans;
  for (int i = n; i;)
    if (f[i] == f[i - 1]) i--;
    else
    {
      int j = tr[i];
      ans.push_back(i);
      if (a[i] == a[j])
      {
        for (int k = i - 1, need = 2; k > j; k--)
          if (a[k] == trV[i])
          {
            ans.push_back(k);
            if (!--need) break;
          }
      }
      else
      {
        for (int k = i - 1; k > j; k--)
          if (a[k] == a[i])
          {
            ans.push_back(k);
            break;
          }

        for (int k = i - 1; k > j; k--)
          if (a[k] == a[j])
          {
            ans.push_back(k);
            break;
          }
      }
      ans.push_back(j);
      i = j - 1;  
    }

  sort(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++)
  {
    cout << ans[i] << ' ';
    if (i % 4 == 3) cout << endl;
  }
}