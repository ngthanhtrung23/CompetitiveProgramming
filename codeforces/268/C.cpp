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

int main()
{
	int m, n;
	cin >> m >> n;
	cout << min(m, n) + 1 << endl;
	for (int i = 0; i <= min(m, n); i++) cout << i << ' ' << min(m, n) - i << endl;
}