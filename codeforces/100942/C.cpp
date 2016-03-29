#include <bits/stdc++.h>
using namespace std;
const int OPPOSITE[] = {5, 3, 4, 1, 2, 0};

double calc(string cube, char from, char to)
{
  int cnt = 0;
  double res = 0;
  for (int i = 0; i < cube.size(); i++)
    if (cube[i] == from)
    {
      cnt++;
      int prev = -1, done = 0;
      for (int j = 0; j < cube.size(); j++)
        if (j != i && cube[j] == to)
        {
          if (j == OPPOSITE[i])
          {
            res += 1;
            done = 1;
            break;
          }

          if (prev < 0) prev = j;
          else if (prev != OPPOSITE[j])
          {
            res += 1;
            done = 1;
            break;
          }
        }

      if (prev >= 0 && !done)
        res += 0.5;
    }
  return cnt ? res / cnt : 0;
}

int main()
{
  string initial, target, cube;
  cin >> initial >> target;
  int n = initial.size();
  double ans = 1;
  for (int i = 0; i < n; i++)
  {
    cin >> cube;
    if (initial[i] != target[i])
      ans *= calc(cube, initial[i], target[i]);
  }
  cout << fixed << setprecision(9) << ans << endl;
}