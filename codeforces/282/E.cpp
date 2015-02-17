#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;

struct node
{
	long long low, high, mid;
	int bit, cnt;
	node *L, *R;
	
	node() {}
	node(long long _low, long long _high, int _bit)
	{
		low = _low; high = _high; 
		mid = (low + high) / 2;
		L = NULL; R = NULL;
		bit = _bit; 
		cnt = 0;
	}
	
	void add(long long val)
	{
		cnt++;
		if (low == high) return;
		if (val >> bit & 1)
		{
			if (R == NULL) R = new node(mid + 1, high, bit - 1);
			R -> add(val);
		}
		else
		{
			if (L == NULL) L = new node(low, mid, bit - 1);
			L -> add(val);
		}
	}
	
	void remove(long long val)
	{
		cnt--;
		if (low == high) return;
		if (val >> bit & 1)
		{
			R -> remove(val);
			if (R -> cnt == 0) R = NULL;
		}
		else
		{
			L -> remove(val);
			if (L -> cnt == 0) L = NULL;
		}
	}
	
	long long get(long long val)
	{
		if (low == high) return low;
		if (val >> bit & 1)
		{
			if (L != NULL) return L -> get(val);
			return R -> get(val);
		}
		if (R != NULL) return R -> get(val);
		return L -> get(val);
	}
};

int n;
long long a[100100], xorLeft[100100];

int main()
{
	node root(0LL, (1LL << 40) - 1, 39);
	root.add(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) 
	{
		cin >> a[i];
		xorLeft[i] = xorLeft[i - 1] ^ a[i];
		root.add(xorLeft[i]);
	}
	
	long long ans = root.get(0), xorRight = 0;
	for (int i = n; i; i--)
	{
		root.remove(xorLeft[i]);
		xorRight ^= a[i];
		ans = max(ans, xorRight ^ root.get(xorRight));
	}
	
	cout << ans << endl;
}