#include <bits/stdc++.h>
using namespace std;

string s;
int k, len, flag;

int getSum(int i, int mask)
{
  int res = s[i] - '0';
  if (mask >> i & 1)
    res--;
  if (i && mask >> (i - 1) & 1)
    res += 10;
  if (!i && flag)
    res += 10;
  return res;
}

int solve(int mask)
{
  int d[22];
  memset(d, -1, sizeof d);

  for (int i = 0; i < len; i++)
    if (d[i] < 0)
    {
      int isGood = 0;
      for (d[i] = (i == 0); d[i] <= getSum(i, mask); d[i]++)
      {
        int ok = 1, last = i;
        while (1)
        {
          int cur = (last + k) % len;
          if (cur == i)
          {
            ok = d[cur] + d[last] == getSum(last, mask);
            break;
          }

          d[cur] = getSum(last, mask) - d[last];
          if (d[cur] < 0 || d[cur] > 9)
          {
            ok = 0;
            break;
          }

          last = cur;
        }

        if (ok) 
        {
          isGood = 1;
          break;
        }
      }

      if (!isGood)
        return 0;
    }

  int start = 0;
  for (int i = 0; i < len; i++)
    if (start || d[i])
    {
      cout << d[i];
      start |= d[i] > 0;
    }
  return 1;
}

int main()
{
  freopen("coding.in", "r", stdin);
  freopen("coding.out", "w", stdout);

  cin >> s >> k;
  len = s.size();

  for (int mask = 0; mask < 1 << (len - 1); mask++)
    if (solve(mask))
      return 0;

  if (s[0] == '1')
  {
    flag = 1;
    s = s.substr(1);
    len--;
    for (int mask = 0; mask < 1 << (len - 1); mask++)
    if (solve(mask))
      return 0;
  }
}