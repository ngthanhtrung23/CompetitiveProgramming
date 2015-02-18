#include <algorithm>
#include <iostream>
#include <iomanip>
#include <complex>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <map>
#include <set>
using namespace std;
//#pragma comment(linker,"/STACK:102400000,102400000")

int n;
vector <int> xs;
vector <int> nex_xs;
int A, B;

map <int, int> occur;

int MAIN()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int t;
		cin >> t;
		if(!occur.count(t))
			xs.push_back(t);
		occur[t] = 1;
	}
	cin >> A >> B;
	int ans = 0;
	while(A != B)
	{
		nex_xs.clear();
		int bestA = A - 1;
		for(int i = 0; i < xs.size(); i++)
		{
			int t = xs[i];
			int v = (A / t) * t;
			if(v >= B)
			{
				nex_xs.push_back(t);
				bestA = min(bestA, v);
			}
		}
		A = bestA;
		xs = nex_xs;
		ans ++;
	}
	cout << ans << endl;
	return 0;
}

int main()
{
	#ifdef LOCAL_TEST
		freopen("in.txt", "r", stdin);
		freopen("out.txt", "w", stdout);
	#endif
	ios :: sync_with_stdio(false);
	cout << fixed << setprecision(16);
	return MAIN();
}