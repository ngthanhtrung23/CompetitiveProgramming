#include <bits/stdc++.h>
using namespace std;

char a[10100], b[10100];

int main()
{
  scanf("%s%s", a, b);
  int n = strlen(a);
  vector < pair<int,int> > ans;
  for (int i = 0; i < n; i++)
    if (a[i] != b[i])
    {
      int sum = 0, j;
      for (j = i; j < n; j++)
      {
        sum += a[j] - '0';
        if (a[j] == b[i] && sum % 2 == 0)
          break;
      }

      if (j == n)
      {
        cout << "NO" << endl;
        return 0;
      }

      ans.push_back({i, j});
      reverse(a + i, a +  j + 1);
    }

  cout << "YES" << endl << ans.size() << endl;
  for (auto u : ans)
    printf("%d %d\n", u.first + 1, u.second + 1);
}