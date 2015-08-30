#include <bits/stdc++.h>
using namespace std;

int n, a[200200], s[400400], st[400400], tail, head = 1;

int main()
{
  ios::sync_with_stdio(0);
  freopen("positive.in", "r", stdin);
  freopen("positive.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  for (int i = 1; i <= n * 2; i++)
    s[i] = s[i - 1] + (i > n ? a[i - n] : a[i]);

  int ans = 0;
  for (int i = n * 2 - 1; i >= 0; i--)
  {
    while (tail >= head && s[i] < s[st[tail]])
      tail--;
    while (head <= tail && st[head] - i > n) 
      head++;
    if (i < n && head > tail)
      ans++;
    st[++tail] = i;
  }

  cout << ans << endl;
}