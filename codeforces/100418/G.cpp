#include <bits/stdc++.h>
using namespace std;

int n, a[1000100];
vector <int> ans;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", a + i);
  sort(a, a + n);
  int bad = -1;
  for (int i = 0; i < n; i++)
    if (i && a[i] == a[i - 1])
    {
      if (a[n - 1] == a[i])
      {
        bad = i;
        break;
      }

      int j = upper_bound(a + i, a + n, a[i]) - a;
      swap(a[i], a[j]);
    }

  if (bad < 0)
    for (int i = 0; i < n; i++)
      ans.push_back(a[i]);
  else
  {
    int cnt = 0, low, high = 0, value = a[bad];
    for (int i = 0; i < n; i++)
      if (a[i] == value) cnt++;
      else a[high++] = a[i];
    low = high - cnt + 1;

    if (low < 0)
    {
      cout << -1 << endl;
      return 0;
    }

    sort(a + low, a + high);

    for (int i = 0; i < high; i++)
    {
      if (low <= i && i <= high) 
        ans.push_back(a[bad]);
      ans.push_back(a[i]);
    }
	ans.push_back(value);
  }

  for (int x : ans)
    printf("%d ", x);
}
