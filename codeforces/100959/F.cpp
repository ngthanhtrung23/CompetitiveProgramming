#include <bits/stdc++.h>
using namespace std;
const int MAX = int(1e9), LIM = int(1e5);

int n, a[22], c[22];
map <int,int> flag;

int isGood(int m)
{
  for (int i = 0; i < n;)
  {
    int j = i;
    while (j < n && c[j] == c[i])
    {
      if (a[j] / m != a[i] / m)
        return 0;
      j++;
    }
    i = j;
    if (i < n && a[i] / m == a[i - 1] / m)
      return 0;
  }

  return 1;
}

void checkSame(int u, int v)
{
  if (u == v) return;
  for (int i = 0; i <= MAX / LIM; i++)
  {
    int low = u / (i + 1);
    if (low * (i + 1) <= u) low++;
    int high = v / (i + 1);
    if (i) high = min(high, u / i);
    if (low <= high && high > LIM)
    {
      flag[max(low, LIM + 1)]++;
      flag[high + 1]--;
    }
  }
}

void checkDif(int u, int v)
{
  for (int i = 0; i <= MAX / LIM; i++)
  {
    int low = v / (i + 1);
    if (low * (i + 1) <= v) low++;
    int high = i ? u / i : MAX;
    if (low <= high && high > LIM)
    {
      flag[max(low, LIM + 1)]++;
      flag[high + 1]--;
    }
  }
}

int main()
{
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i] >> c[i];
    a[i]--;
    for (int j = 0; j < i; j++)
      if (c[j] == c[i])
        for (int k = j + 1; k < i; k++)
          if (c[k] != c[i])
          {
            cout << 0 << endl;
            return 0;
          }
  }

  if (c[0] == c[n - 1])
  {
    cout << -1 << endl;
    return 0;
  }

  int ans = 0;
  for (int m = 1; m <= LIM; m++)
    ans += isGood(m);

  flag[LIM + 1] = 0;
  for (int i = 0; i < n;)
  {
    int j = i;
    while (j < n && c[j] == c[i])
      j++;
    checkSame(a[i], a[j - 1]);
    if (j < n)
      checkDif(a[j - 1], a[j]);
    i = j;
  }

  int last = LIM + 1, cur = 0;
  for (auto u : flag)
  {
    if (!cur)
      ans += u.first - last;
    cur += u.second;
    last = u.first;
  }

  cout << ans << endl;
}