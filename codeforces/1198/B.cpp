/**
 *    author:  tourist
 *    created: 30.07.2019 17:49:26       
**/
#include "bits/stdc++.h"
 
using namespace std;
 
inline int ReadInt()
{
    char c;
    while (c = getchar(), c < '0' || c > '9');
    int x = c - '0';
    while (c = getchar(), c >= '0' && c <= '9')
        x = x * 10 + c - '0';
    return x;
}
 
inline void WriteInt(int x)
{
    int p = 1;
    for (int temp = x / 10; temp > 0; temp /= 10)
        p *= 10;
    for (; p > 0; x %= p, p /= 10)
        putchar(x / p + '0');
}
 
int main() {
  int n = ReadInt();
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
      a[i] = ReadInt();
  }
  int tt = ReadInt();
  vector<int> op(tt);
  vector<int> who(tt);
  vector<int> val(tt);
  for (int i = 0; i < tt; i++) {
      op[i] = ReadInt();
    if (op[i] == 1) {
        who[i] = ReadInt();
        val[i] = ReadInt();
      --who[i];
    } else {
        val[i] = ReadInt();
    }
  }
  vector<int> res(n, -1);
  int mx = -1;
  for (int i = tt - 1; i >= 0; i--) {
    if (op[i] == 1) {
      if (res[who[i]] == -1) {
        res[who[i]] = max(val[i], mx);
      }
    } else {
      mx = max(mx, val[i]);
    }
  }
  for (int i = 0; i < n; i++) {
    if (res[i] == -1) {
      res[i] = max(a[i], mx);
    }
  }
  for (int i = 0; i < n; i++) {
    if (i > 0) {
        cout << ' ';
    }
    cout << res[i];
  }
  cout << '\n';
  return 0;
}
