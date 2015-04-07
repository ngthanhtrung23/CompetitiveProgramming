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
using namespace std;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int main()
{
	int fx, fy, x = 0, y = 0, d = 1, z = 0, step;
	cin >> fx >> fy;
	
	for (step = 0; ; step++)
	{
		int xx = x + dx[z] * d, yy = y + dy[z] * d;
		if ((fx - x) * (fx - xx) <= 0 && (fy - y) * (fy - yy) <= 0) break;
		x = xx; y = yy;
		z = (z + 1) & 3;
		if (step & 1) d++;
	}
	
	cout << step << endl;
}