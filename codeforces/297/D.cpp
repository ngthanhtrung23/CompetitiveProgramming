#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int m, n, k, color[1010][1010], swapped;
string row[1010], col[1010];

void swapRowCol()
{
	string tmpRow[1010], tmpCol[1010];
	for (int j = 0; j < n; j++)
	{
		tmpRow[j] = string(m + 2, ' ');
		for (int i = 0; i < m - 1; i++) tmpRow[j][i] = col[i][j];
	}
	for (int j = 0; j < n - 1; j++)
	{
		tmpCol[j] = string(m + 2, ' ');
		for (int i = 0; i < m; i++) tmpCol[j][i] = row[i][j];
	}
	for (int i = 0; i < n; i++) row[i] = tmpRow[i];
	for (int i = 0; i < n - 1; i++) col[i] = tmpCol[i];
	swap(m, n);
	swapped = 1;
}

int main()
{
	cin >> m >> n >> k;
	for (int i = 0; i < m * 2 - 1; i++)
		if (i % 2) cin >> col[i / 2];
		else cin >> row[i / 2];
		
	if (m * (n - 1) < n * (m - 1)) swapRowCol();
	
	if (k == 1)
	{
		int cntE = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n - 1; j++)
				cntE += row[i][j] == 'E';
		for (int i = 0; i < m - 1; i++)
			for (int j = 0; j < n; j++)
				cntE += col[i][j] == 'E';
		if (cntE * 4 < (m * (n - 1) + n * (m - 1)) * 3) 
		{
			puts("NO");
			return 0;
		}
	}
	else
	{
		for (int j = 1; j < n; j++) color[0][j] = color[0][j - 1] ^ (row[0][j - 1] == 'N');
	
		for (int i = 1; i < m; i++)
		{
			int cntFalse = (color[i - 1][0] ^ color[i][0] ^ (col[i - 1][0] == 'N'));
			for (int j = 1; j < n; j++) 
			{
				color[i][j] = color[i][j - 1] ^ (row[i][j - 1] == 'N');
				cntFalse += (color[i][j] ^ color[i - 1][j] ^ (col[i - 1][j] == 'N'));
			}
		
			if (cntFalse > n - cntFalse)
				for (int j = 0; j < n; j++) color[i][j] ^= 1;
		}
	}
	
	puts("YES");
	if (!swapped)
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				printf("%d%c", color[i][j] + 1, (j == n - 1 ? '\n' : ' '));
	else
		for (int j = 0; j < n; j++)
			for (int i = 0; i < m; i++)
				printf("%d%c", color[i][j] + 1, (i == m - 1 ? '\n' : ' '));
}