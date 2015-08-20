#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, M, Y, x[1010], roundUp = 0;
  pair <int,int> a[1010];
  cin >> n >> M >> Y;
  for (int i = 0; i < n; i++)
  {
    cin >> x[i];
    a[i] = {x[i] * M % Y, i};
    roundUp += a[i].first;
    x[i] = x[i] * M / Y;
  }

  assert(roundUp % Y == 0);
  roundUp /= Y;

  sort(a, a + n);
  for (int i = 1; i <= roundUp; i++)
    x[a[n - i].second]++;

  for (int i = 0; i < n; i++) 
    cout << x[i] << (i == n - 1 ? '\n' : ' ');
}