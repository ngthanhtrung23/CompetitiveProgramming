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
string s;

int MAIN()
{
	cin >> n >> s;
	int cntSmall = 0, cntBig = 0;
	for(int i = 0; i < n; i++)
		if(s[i] == 'x')
			cntSmall ++;
		else
			cntBig ++;
	int ans = 0;
	for(int i = 0; i < n; i++)
	{
		if(cntSmall < cntBig && s[i] == 'X')
		{
			s[i] = 'x';
			cntSmall ++;
			cntBig --;
			ans ++;
		}
		if(cntBig < cntSmall && s[i] == 'x')
		{
			s[i] = 'X';
			cntSmall --;
			cntBig ++;
			ans ++;
		}
	}
	cout << ans << endl;
	cout << s << endl;
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