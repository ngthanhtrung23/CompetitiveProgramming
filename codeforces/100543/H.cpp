#include <bits/stdc++.h>
using namespace std;
const int BUTTONS[4][3] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9},
  {-1, 0, -1}
};

int visited[1010];

void go(int lastX, int lastY, int number)
{
  if (number > 1000) return;
  if (visited[number]) return;
  visited[number] = 1;
  
  for (int x = lastX; x < 4; x++)
    for (int y = lastY; y < 3; y++)
      if (BUTTONS[x][y] >= 0)
        go(x, y, number * 10 + BUTTONS[x][y]);
}

int main()
{
  ios::sync_with_stdio(0);
  go(0, 0, 0);
  
  int test;
  cin >> test;
  while (test--)
  {
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i <= 1000; i++)
      if (visited[i] && abs(i - n) < abs(ans - n))
        ans = i;
    cout << ans << endl;
  }
}