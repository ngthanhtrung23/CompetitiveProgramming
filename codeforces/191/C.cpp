#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstring>
#define maxn 100005
#define prev __prev
using namespace std;

vector<int> adj[maxn];
map< pair<int,int>,int > mp;
int n;
int parIdx[maxn],sum[maxn],ret[maxn];
int prev[maxn][20];
int enter[maxn],quit[maxn],cnt = 0;

void DFS(int u,int pre) {
  enter[u] = cnt++;
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v == pre) continue;
    parIdx[v] = mp[make_pair(v,u)];
    prev[v][0] = u;
    DFS(v,u);
  }
  quit[u] = cnt++;
}

bool parent(int u,int v) {
  return (enter[u] <= enter[v] && quit[v] <= quit[u]);
}

int LCA(int u,int v) {
  if (parent(u,v)) return u;
  for (int i = 19; i >= 0; i--) {
    int z = prev[u][i];
    if (z >= 0 && !parent(z,v)) u = z;
  }
  return prev[u][0];
}

void go(int u,int pre) {
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v == pre) continue;
    go(v,u);
    sum[u] += sum[v];
  } 
  if (u > 1) ret[parIdx[u]] = sum[u];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u,v;
    scanf("%d %d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
    mp[make_pair(u,v)] = mp[make_pair(v,u)] = i;
  }
  memset(prev,-1,sizeof(prev));  
  DFS(1,-1);
  for (int j = 1; j < 20; j++)
    for (int i = 1; i <= n; i++) {
      int u = prev[i][j - 1];
      if (u >= 0 && prev[u][j - 1] >= 0) prev[i][j] = prev[u][j - 1];
    }
  int m;
  scanf("%d", &m);
  while (m--) {
    int u,v;
    scanf("%d %d", &u, &v);
    int z = LCA(u,v);
    sum[u]++;
    sum[v]++;
    sum[z] -= 2;
  }
  go(1,-1);
  for (int i = 1; i < n; i++) printf("%d ", ret[i]);
}