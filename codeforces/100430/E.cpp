#include <bits/stdc++.h>
using namespace std;
const int D = 840, oo = 27081993, MAX_S = 1111;

int m, n, dest[111][10], days[111], S[111], T[111], start[111], finish[111], at[111];
vector < pair<int,int> > paths[111];

int main()
{
	ios::sync_with_stdio(0);
	freopen("hot.in", "r", stdin);
	freopen("hot.out", "w", stdout);
	
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> days[i];
		for (int j = 0; j < days[i]; j++) cin >> dest[i][j];
	}
	
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> S[i] >> T[i] >> start[i];
		finish[i] = oo;
		
		int x = S[i];
		for (int day = start[i]; day <= start[i] + D * m; day++)
		{
			if (x == T[i]) 
			{
				finish[i] = day;
				break;
			}
			x = dest[x][day % days[x]];
		}
	}
	
	vector <int> ans;
	
	for (int day = 0; day <= D * m + MAX_S; day++)
	{
		for (int i = 1; i <= n; i++)
			if (start[i] == day)
				if (!at[S[i]] || finish[at[S[i]]] > finish[i])
					at[S[i]] = i;
		
		for (int i = 1; i <= n; i++)
			if (finish[i] == day && at[T[i]] == i)
			{
				ans.push_back(i);
				at[T[i]] = 0;
			}
			
		int save[111];
		for (int i = 1; i <= m; i++) save[i] = at[i], at[i] = 0;
		for (int i = 1; i <= m; i++) 
		{
			if (!save[i]) continue;
			int next = dest[i][day % days[i]];
			if (!at[next] || finish[at[next]] > finish[save[i]]) 
				at[next] = save[i];
		}	
	}
	
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for (int i = 0; i < int(ans.size()); i++) cout << ans[i] << ' ';
}