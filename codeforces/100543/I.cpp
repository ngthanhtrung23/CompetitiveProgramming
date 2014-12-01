#include <bits/stdc++.h>
using namespace std;

int n, b[100100], a[100100], sum[2], curSum[2];

int main()
{
  ios::sync_with_stdio(0);
  //freopen("i.in", "r", stdin);
  
  int test;
  char ch;
  cin >> test;
  while (test--)
  {
    cin >> n;
    sum[0] = sum[1] = 0;
    for (int i = 0; i < n; i++)
    {
      cin >> a[i] >> ch;
      b[i] = ch == 'B';
      sum[b[i]] += a[i];
    }
    
    int nn = 1;
    for (int i = 1; i < n; i++)
      if (b[i] == b[nn - 1]) a[nn - 1] += a[i];
      else
      {
        a[nn] = a[i];
        b[nn++] = b[i];
      }
    
    n = nn;
    if (n == 1)
    {
      cout << sum[b[0]] << endl;
      continue;
    }
    
    curSum[0] = curSum[1] = 0;
    curSum[b[0]] = a[0];
    int ans = 0;
    for (int i = 1; i < n; i++)
    {
      curSum[b[i]] += a[i];
      if (!curSum[0] || !curSum[1]) continue;
      if (1LL * curSum[b[i] ^ 1] * sum[b[i]] % sum[b[i] ^ 1] == 0)
      {
        long long need = 1LL * curSum[b[i] ^ 1] * sum[b[i]] / sum[b[i] ^ 1];
        if (need <= curSum[b[i]] && curSum[b[i]] - need <= a[i])
        {
          curSum[b[i]] -= need;
          curSum[b[i] ^ 1] = 0;
          ans++;
        }
      }
    }
    
    cout << ans << endl;
  }
}
