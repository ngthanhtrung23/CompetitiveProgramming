#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#define FOR(i,s,e) for (int i=(s); i<(int)(e); i++)
#define FOE(i,s,e) for (int i=(s); i<=(int)(e); i++)
using namespace std;

int n,m,lim,num,val,cnt,a[10005];
map<int,int> dp;

int main(){

	scanf("%d%d%d", &n, &m, &lim);

	for (int i=1; i*i<=m; i++){
		if (m%i==0){
			a[cnt++] = i;
			if (i*i!=m) a[cnt++] = m/i;
		}
	}
	
	sort(a, a+cnt);
	for (int i=0; i<cnt; i++){

		dp[a[i]] = 1;
		if (a[i]<lim) continue;

		dp[a[i]] = 1;
		for (int j=0; j<i; j++){
			if (a[i]%a[j]!=0 || a[j]<lim) continue;
			
			dp[a[i]] = 2;
			num = a[i]/a[j];
			val = dp[a[j]];
			
			if ( (val==1) || (val==2 && num%2==1) || (val==3 && num%2==0)){
				dp[a[i]] = 3;
				break;
			}
		}
	}
	
	
	val = dp[m];
	num = n;
	if ( (val==1) || (val==2 && num%2==1) || (val==3 && num%2==0)) printf("Marsel\n");
	else printf("Timur\n");
	
	return 0;
}