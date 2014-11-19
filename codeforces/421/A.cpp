#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int ans[101];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, a, b;
  scanf("%d %d %d", &n, &a, &b);
  for (int i = 1; i <= a; ++i) {
    int t;
    scanf("%d", &t);
    ans[t] = 1;
  }
  for (int i = 1; i <= b; ++i) {
    int t;
    scanf("%d", &t);
    ans[t] = 2;
  }
  for (int i = 1; i <= n; ++i)
    printf("%d ", ans[i]);
}