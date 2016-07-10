#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cassert>
using namespace std;
typedef long long ll;
typedef double R;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define FOR(i, s, t) for(i = (s); i < (t); i++)
#define RFOR(i, s, t) for(i = (s)-1; i >= (t); i--)

const R PI = acos(-1);
const int MAXN = 105;
const int P = 1e9+7;

char s[MAXN];

int main(){
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif
	int r, c;
	int i, j;
	int cnt = 0;
	scanf("%d%d", &r, &c);
	for(i = 0; i < r; i++)
		scanf("%s", s);
	for(i = 0; i < c; i++){
		if(s[i] == 'B'){
			if(i == 0 || s[i-1] == '.')
				cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}
