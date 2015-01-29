#include <bits/stdc++.h>
using namespace std;

int visited[1111], n, k, deg[1111];
vector <int> lines, cycles, a[1111];

int calc(int d)
{
  // put at root
  int ans = 1;
  
  for (auto x : lines) 
    if (x > d)
      ans += (x - d + 2 * d) / (2 * d + 1);
  
  for (auto x : cycles)
    if (x > d * 2)
      ans += x / (2 * d + 1);
  
  // put at others
  for (int range = 1; range <= d; range++)
  {
    int sumLine = 0, sumCycle = 0;
    for (auto x : lines)
      if (x > d - range) 
        sumLine += (x - (d - range) + 2 * d) / (2 * d + 1);
    
    for (auto x : cycles)
      if (x > (d - range) * 2)
        sumCycle += (x - (d - range) * 2 + 2 * d) / (2 * d + 1);
        
    // put on line
    for (auto x : lines)
      if (x >= range)
      {
        int res = sumLine + sumCycle + 1;
        if (x > d - range) res -= (x - (d - range) + 2 * d) / (2 * d + 1);
        if (x > range + d) res += (x - range - d + 2 * d) / (2 * d + 1);
        ans = min(ans, res);
      }
      
    // put on cycle
    for (auto x : cycles)
      if (x >= range)
      {
        int res = sumLine + sumCycle + 1;
        if (x > (d - range) * 2) res -= (x - (d - range) * 2 + 2 * d) / (2 * d + 1);
        if (x > d * 2) res += x / (2 * d + 1);
        ans = min(ans, res);
      }
  }
  
  return ans;
}

int main()
{
  ios::sync_with_stdio(0);
  int m, x, y;
  
  cin >> n >> m >> k;
  while (m--)
  {
    cin >> x >> y;
    deg[x]++;
    deg[y]++;
    a[x].push_back(y);
    a[y].push_back(x);
  }
  
  if (n == 1)
  {
    cout << 0 << endl;
    return 0;
  }
  
  int maxDeg = 0, root = 0;
  for (int i = 1; i <= n; i++)
    if (deg[i] > maxDeg)
    {
      root = i;
      maxDeg = deg[i];
    }
    
  visited[root] = 1;
  for (auto u : a[root])
    if (!visited[u])
    {
      int cnt = 0;
      while (1)
      {
        cnt++;
        visited[u] = 1;
        int found = 0;
        for (auto v : a[u])
          if (!visited[v])
          {
            u = v;
            found = 1;
            break;
          }
        if (!found) break;
      }
      
      if (a[u].size() == 1) lines.push_back(cnt);
      else cycles.push_back(cnt);
    }
    
  int low = 0, high = n, ans = n + 1;
  while (low <= high)
  {
    int mid = (low + high) / 2;
    if (calc(mid) <= k) ans = mid, high = mid - 1;
    else low = mid + 1;
  }
  
  cout << ans << endl;
}
