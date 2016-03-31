#include <bits/stdc++.h>
using namespace std;

int n, a[22];
deque<char> supply[22], discard[22];

void grab(int x, int y, int move)
{
  if (a[y] < a[x])
    swap(x, y);

  while (!discard[y].empty())
  {
    supply[y].push_back(discard[y].back());
    discard[y].pop_back();
  }
  while (!discard[x].empty())
  {
    supply[y].push_back(discard[x].back());
    discard[x].pop_back();
  }

  if (supply[x].empty())
  {
    cout << "Player " << x + 1 << " wins after " << move << " moves." << endl;
    exit(0);
  }
}

int main()
{
  freopen("jungle.in", "r", stdin);
  freopen("jungle.out", "w", stdout);
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
  {
    string s;
    cin >> s;
    for (char c : s)
      supply[i].push_back(c);
  }

  for (int move = 1, player = 0; move <= 1000000; move++)
  {
    char card = supply[player].front();
    supply[player].pop_front();
    discard[player].push_back(card);

    for (int i = 0; i < n; i++)
      if (i != player && !discard[i].empty() && discard[i].back() == card)
      {
        grab(i, player, move);
        break;
      }

    int found = 0;
    for (int i = 1; i <= n; i++)
      if (!supply[(player + i) % n].empty())
      {
        found = 1;
        player = (player + i) % n;
        break;
      }

    if (!found) 
    {
      cout << "Draw after " << move << " moves." << endl;
      return 0;
    }
  }

  cout << "Abandoned after 1000000 moves." << endl;
}