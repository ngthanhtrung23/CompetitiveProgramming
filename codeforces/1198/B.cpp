/**
 *    author:  tourist
 *    created: 30.07.2019 17:49:26       
**/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int tt;
  cin >> tt;
  vector<int> op(tt);
  vector<int> who(tt);
  vector<int> val(tt);
  for (int i = 0; i < tt; i++) {
    cin >> op[i];
    if (op[i] == 1) {
      cin >> who[i] >> val[i];
      --who[i];
    } else {
      cin >> val[i];
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
      cout << " ";
    }
    cout << res[i];
  }
  cout << '\n';
  return 0;
}