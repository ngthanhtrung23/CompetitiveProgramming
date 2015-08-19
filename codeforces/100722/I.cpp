#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  int test;
  cin >> test;
  while (test--)
  {
    int d[256] = {0}, a[26], cnt[30] = {0};
    string s;
    cin >> s;
    for (int i = 0; i < 26; i++) a[i] = s[i] - 'A';
    for (int i = 0; i < 26; i++) 
      if (!d[i])
      {
        int length = 0, id = i;
        while (!d[id])
        {
          d[id] = 1;
          length++;
          id = a[id];
        }
        cnt[length]++;
      }

    string ans = "Yes";
    for (int i = 2; i <= 26; i += 2)
      if (cnt[i] % 2)
        ans = "No";

    cout << ans << endl;
  }
}