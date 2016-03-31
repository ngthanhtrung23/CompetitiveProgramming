#include <bits/stdc++.h>
using namespace std;
const int oo = 27081993;

struct Edge
{
  int x, y, cap, flow, cost;
};

int n, dist[33], tr[33];
vector <int> a[33];
vector <Edge> edges;

void addEdge(int x, int y, int cap, int cost)
{
  a[x].push_back(edges.size()); 
  edges.push_back({x, y, cap, 0, cost});
  a[y].push_back(edges.size()); 
  edges.push_back({y, x, 0, 0, -cost});
}

int negativeCycle()
{
  int lastUpdated = 0;
  memset(dist, 0, sizeof dist);
  memset(tr, -1, sizeof tr);

  for (int turn = 0; turn < n + 3; turn++)
  {
    int found = 0;
    for (int i = 0; i < edges.size(); i++)
    {
      Edge e = edges[i];
      if (e.flow < e.cap && dist[e.y] > dist[e.x] + e.cost)
      {
        found = 1;
        lastUpdated = e.y;
        dist[e.y] = dist[e.x] + e.cost;
        tr[e.y] = i;
      }
    }

    if (!found)
      return 0;
  }

  return lastUpdated;
}

int modify(int x)
{
  int minCap = oo;
  vector <int> edgeList, flag(edges.size(), 0);
  while (1)
  {
    int i = tr[x];
    if (i < 0) break;
  
    Edge e = edges[i];
    if (flag[i]) 
    {
      while (edgeList[0] != i)
        edgeList.erase(edgeList.begin());
      break;
    }

    minCap = min(minCap, e.cap - e.flow);
    edgeList.push_back(i);
    flag[i] = 1;
    x = e.x;
  }

  int res = 0;
  for (auto i : edgeList)
  {
    edges[i].flow += minCap;
    res += minCap * edges[i].cost;
    edges[i ^ 1].flow -= minCap;
  }
  return res;
}

int main()
{
  freopen("arbitrage.in", "r", stdin);
  freopen("arbitrage.out", "w", stdout);

  int m, x, y, cost, cap;
  cin >> n >> m;
  while (m--)
  {
    cin >> x >> y >> cost >> cap;
    addEdge(x, y, cap, -cost);
  }

  int ans = 0;
  while (1)
  {
    int x = negativeCycle();
    if (!x) break;
    ans += modify(x);
  }
  cout << -ans << endl;
}