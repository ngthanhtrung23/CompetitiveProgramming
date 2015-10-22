#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  int n, m, x;
  string s, t;
  cin >> n >> x >> s >> m >> t;
  cout << s[--x];
  for (auto c : t)
  {
    if (c == 'L') x--;
    else x++;
    cout << s[x];
  }  
  cout << endl;
}