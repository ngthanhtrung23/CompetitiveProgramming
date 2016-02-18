#include <bits/stdc++.h>
using namespace std;
const int STEP = 80000000;

string a[10][10];
char trees[STEP * 2 + 10];

int main()
{
  freopen("beavers.in", "r", stdin);
  freopen("beavers.out", "w", stdout);
  ios::sync_with_stdio(0);

  for (int j = 0; j < 5; j++)
    for (int i = 0; i < 2; i++)
      cin >> a[i][j];

  int x = STEP, mood = 0;
  for (int step = 0; step < STEP; step++)
  {
    string cur = a[trees[x]][mood];
    trees[x] = cur[0] - '0';
    if (cur[1] == 'L') x--;
    else x++;
    mood = cur[2] - 'A';
    if (mood >= 5)
    {
      cout << "happy beaver" << endl;
      return 0;
    }
  }  

  cout << "unhappy beaver" << endl;
}