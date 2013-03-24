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
#define DB 0
using namespace std;

char s[1000100], t[2000100];
int n, mark[1000100], markDif[1000100], ok[1000100], flag[1000100];
int pre[2000100], match[2000100];

void calcPre(int n)
{
	int i = 0, j = -1;
	pre[0] = -1;
	while (i < n)
	{
		while (j >= 0 && t[i] != t[j]) j = pre[j];
		match[++i] = ++j;
		pre[i] = (j >= n || t[i] != t[j] ? j : pre[j]);
	}
}

int kmp(int from, int dist)
{
	for (int i = 0; i <= dist; i++) t[i] = s[(from + i) % n];
	int len = dist + 1;
	calcPre(len);
	
	int i = 1, j = 0;
	while (i < len)
	{
		while (j >= 0 && t[i] != t[j]) j = pre[j];
		i++; j++;
	}
	
	return j;
}

int kmp2()
{
	for (int i = 0; i < n * 2; i++) t[i] = s[i % n];
	int len = n * 2;
	calcPre(n);
	
	int i = 1, j = 0;
	while (i < len)
	{
		while (j >= 0 && t[i] != t[j]) j = pre[j];
		i++; j++;
		if (j == n) return i - n;
	}
	
	return 0;
}

void solveAll()
{
	int period = kmp2();
	for (int i = 1; i <= n; i++)
		if (i % period == 0 && i < n) printf("0");
		else printf("1");
}

void solveSubstr(int from, int dist)
{
	int period = kmp(from, dist), rest = n - dist - 1;
	
	for (int i = 0; i <= dist + 3; i++) flag[i] = 0;
		
	
	for (int j = period; j; j = match[j])
		for (int i = dist + 1 - j; i < dist; i += dist + 1 - j)
			flag[i] = 1;

	for (int i = 1; i < dist; i++) 
		if (!flag[i]) ok[n - i - 1] = 1;
	if (!dist || s[from] != s[(from + dist) % n]) ok[rest] = 1;
}

int valid(int i, int j)
{
	for (int k = 0; k < j; k++)
		if (s[(i + k) % n] == s[(i + k + 1) % n]) return 0;
	if (s[i] == s[(i + j) %n]) return 0;
	return 1;
}

void brute()
{
	int ok[100] = {0};
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) ok[j + 1] |= valid(i, j);
	ok[1] = 1;
	for (int i = 0; i < n; i++) cout << ok[n - i]; puts("");
}

int main()
{
	//freopen("b.in", "r", stdin);
	int noTest = 0;
	while (scanf("%s", s) == 1)
	{
		n = strlen(s);
		int start = -1;
		for (int i = 0; i < n; i++)
			if (s[i] == s[(i + 1) % n])
			{
				start = (i + 1) % n; break;
			}
			
		for (int i = 0; i <= n; i++) ok[i] = 0;
		ok[n - 1] = 1;
		
		printf("Case %d: ", ++noTest);
		
		if (start < 0) solveAll();
		else
		{
			int from = start;
			
			for (int i = 0; i < n; i++)
			{
				int j = (start + i) % n;
				if (s[j] == s[(j + 1) % n]) 
				{
					solveSubstr(from, (j + n - from) % n);
					from = (j + 1) % n;
					if (from == start) break;
				}
			}
			
			for (int i = 0; i < n; i++) printf("%d", ok[i]);
		}
		
		puts("");
		//brute();
		//break;
	}
}
