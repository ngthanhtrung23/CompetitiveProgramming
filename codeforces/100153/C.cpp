#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#define plli pair < pair<long long,long long>, int >
using namespace std;

int n;
long long w[33], v[33], L, R;

vector < plli > get(int n, vector <long long> w, vector <long long> v)
{
	vector < plli > res;
	for (int mask = 0; mask < 1 << n; mask++)
	{
		long long V = 0, W = 0;
		for (int i = 0; i < n; i++)
			if (mask >> i & 1)
			{
				V += v[i];
				W += w[i];
			}
		res.push_back(make_pair(make_pair(W, V), mask));
	}
	sort(res.begin(), res.end());
	return res;
}

int main()
{
	freopen("dowry.in", "r", stdin);
	freopen("dowry.out", "w", stdout);
	cin >> n >> L >> R;
	for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
	
	int n1 = n / 2, n2 = n - n1;
	vector <long long> w1, w2, v1, v2;
	for (int i = 0; i < n; i++)
		if (i < n1) w1.push_back(w[i]), v1.push_back(v[i]);
		else w2.push_back(w[i]), v2.push_back(v[i]);
	
	vector < plli > a = get(n1, w1, v1);
	vector < plli > b = get(n2, w2, v2);
	
	priority_queue < plli > q;
	long long ans = 0, maskRes = 0;
	for (int i = int(a.size()) - 1, j = 0; i >= 0; i--)
	{
		long long low = L - a[i].first.first, high = R - a[i].first.first;
		while (j < int(b.size()) && b[j].first.first <= high) 
			q.push(make_pair(make_pair(b[j].first.second, b[j].first.first), b[j].second)), j++;
		
		while (!q.empty())
		{
			plli u = q.top();
			if (u.first.second < low) q.pop();
			else
			{
				if (ans < u.first.first + a[i].first.second)
				{
					ans = u.first.first + a[i].first.second;
					maskRes = (1LL * u.second << n1) | a[i].second;
				}
				break;
			}
		}
	}
	
	int cnt = 0;
	for (int i = 0; i < n; i++)
		if (maskRes >> i & 1) cnt++;
	cout << cnt << endl;
	for (int i = 0; i < n; i++)
		if (maskRes >> i & 1) cout << i + 1 << endl;
}
