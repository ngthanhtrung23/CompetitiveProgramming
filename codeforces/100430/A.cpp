#include <bits/stdc++.h>
using namespace std;

int n, wires[50500], sockets[100100], ans[50500];
vector <int> g[200200], gt[200200], pos[50500];
vector<bool> used;
vector<int> order, comp;

void dfs1 (int v) 
{
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) 
	{
		int to = g[v][i];
		if (!used[to]) dfs1(to);
	}
	order.push_back (v);
}
void dfs2 (int v, int cl) 
{
	comp[v] = cl;
	for (size_t i=0; i<gt[v].size(); ++i) 
	{
		int to = gt[v][i];
		if (comp[to] == -1) dfs2(to, cl);
	}
}

int readInput()
{
	int n;  
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> wires[i];
	for (int i = 1; i <= n * 2; i++)
	{
		cin >> sockets[i];
		pos[sockets[i]].push_back(i);
	}
	
	for (int i = 1; i <= n; i++)
	{
		int x = pos[i][0], y = pos[i][1];
		g[x].push_back(y + n * 2);
		gt[y + n * 2].push_back(x);
		
		g[y + n * 2].push_back(x);
		gt[x].push_back(y + n * 2);
		
		g[y].push_back(x + n * 2);
		gt[x + n * 2].push_back(y);
		
		g[x + n * 2].push_back(y);
		gt[y].push_back(x + n * 2);
	}
	
	for (int i = 1; i <= n * 2; i++)
	{
		int next = i + 1;
		if (next > n * 2) next = 1;
		if (wires[sockets[i]] != wires[sockets[next]]) continue;
		
		g[i].push_back(next + n * 2);
		g[next].push_back(i + n * 2);
		
		gt[next + n * 2].push_back(i);
		gt[i + n * 2].push_back(next);
	}
	
	return n;
}

int main() {
	
	freopen("chip.in", "r", stdin);
	freopen("chip.out", "w", stdout);
	n = readInput() * 4;
	used.assign (n + 1, false);
	for (int i = 1; i <= n; i++)
		if (!used[i])   dfs1 (i);
	comp.assign (n + 1, -1);
	for (int i=0, j=0; i<n; ++i) {
		int v = order[n-i-1];
		if (comp[v] == -1) dfs2 (v, j++);
	}

	for (int i = 1; i <= n / 2; i++)
		if (comp[i] == comp[i + n / 2]) 
		{
			 cout << "NO\n";
			 return 0;
		}
	
	for (int i=1; i<=n/2; i++)
		if (comp[i] > comp[i + n / 2])
			ans[sockets[i]] = i;
		
	cout << "YES\n";
	for (int i = 1; i <= n / 4; i++) cout << ans[i] << ' ';
}
