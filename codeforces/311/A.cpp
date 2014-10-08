#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#define fi "CF185_1_1.INP"
#define fo "CF185_1_1.OUT"
#define nmax
#define INF
using namespace std;

//VARIABLES
int n,m;
//FUNCTION PROTOTYPES
void Process();

//MAIN
int main()
{
	//freopen(fi,"r",stdin);
	//freopen(fo,"w",stdout);
	Process();
	return 0;
}

//FUNCTIONS AND PROCEDURES
void Process()
{
	scanf("%d%d",&n,&m);
	if ((n*(n-1))/2<=m)
	{
		printf("no solution\n");
		return;
	}
	for (int i=1;i<=n;++i) printf("0 %d\n",i);
}