#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, a[1111];
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];

  sort(a, a + n);
  int ans = 0;
  long long sum = 0; 
  for (int i = 0; i < n; i++)
    if (a[i] > sum)
    {
      ans++;
      sum += a[i];
    }

  cout << ans << endl;
}