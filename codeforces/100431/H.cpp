#include <bits/stdc++.h>
using namespace std;
const long long oo = 1LL << 60;

int n, m, c;
int craneSpeed[100100], craneNoType[100100], craneType[100100][11];
int shipType[100100], shipSpeed[100100], ans[100100];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("seaport.in", "r", stdin);
  freopen("seaport.out", "w", stdout);
  int d;

  cin >> n >> m >> c;
  set < pair<long long,int> > idleCrane[11], event, idleShip[11];

  for (int i = 1; i <= n; i++)
  {
    cin >> d >> shipType[i] >> shipSpeed[i];
    event.insert({d, i});
  }
  
  for (int i = 1; i <= m; i++)
  {
    cin >> craneSpeed[i] >> craneNoType[i];
    for (int j = 1; j <= craneNoType[i]; j++)
    {
      cin >> craneType[i][j];
      idleCrane[craneType[i][j]].insert({0, i});
    }
  }

  int cnt = 0;
  while (!event.empty() && cnt < n)
  {
    auto u = *event.begin();
    event.erase(u);
    // crane
    if (u.second <= 0)
    {
      int crane = m + u.second, ship = 0;
      long long earliest = oo;
      for (int i = 1; i <= craneNoType[crane]; i++)
      {
        int type = craneType[crane][i];
        if (idleShip[type].empty()) continue;
        auto curShip = *idleShip[type].begin();
        if (curShip.first < earliest || (curShip.first == earliest && curShip.second < ship))
        {
          earliest = curShip.first;
          ship = curShip.second;
        }
      }

      if (ship) 
      {
        ans[ship] = crane;
        cnt++;
        idleShip[shipType[ship]].erase(idleShip[shipType[ship]].begin());
        long long avaiTime = u.first + (shipSpeed[ship] + craneSpeed[crane] - 1) / craneSpeed[crane];
        event.insert({avaiTime, crane - m});
      }
      else
        for (int i = 1; i <= craneNoType[crane]; i++)
          idleCrane[craneType[crane][i]].insert({u.first, crane});
      
    }
    // ship
    else
    {
      int ship = u.second;
      if (idleCrane[shipType[ship]].empty())
        idleShip[shipType[ship]].insert(u);
      else
      {
        int crane = idleCrane[shipType[ship]].begin()->second;
        long long avaiTime = idleCrane[shipType[ship]].begin()->first;
        ans[ship] = crane;
        cnt++;
        long long newAvaiTime = u.first + (shipSpeed[ship] + craneSpeed[crane] - 1) / craneSpeed[crane];
        for (int i = 1; i <= craneNoType[crane]; i++)
        {
          int type = craneType[crane][i];
          idleCrane[type].erase({avaiTime, crane});
        }
        event.insert({newAvaiTime, crane - m});
      }
    }
  }

  for (int i = 1; i <= n; i++)
    cout << ans[i] << '\n';
}