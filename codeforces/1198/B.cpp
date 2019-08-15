/**
 *    author:  tourist
 *    created: 30.07.2019 17:49:26       
**/
#include "bits/stdc++.h"
 
using namespace std;
 
int main() {
  int n; scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
  }
  int tt; scanf("%d", &tt);
  vector<int> op(tt);
  vector<int> who(tt);
  vector<int> val(tt);
  for (int i = 0; i < tt; i++) {
      scanf("%d", &op[i]);
    if (op[i] == 1) {
        scanf("%d", &who[i]);
        scanf("%d", &val[i]);
      --who[i];
    } else {
        scanf("%d", &val[i]);
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
