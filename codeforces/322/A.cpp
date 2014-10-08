#include<stdio.h>
#include<string>
#include<math.h>
#include<stdlib.h>
#include<set>
#include<bitset>
#include<map>
#include<vector>
#include<string.h>
#include<algorithm>
#include<iostream>
#define pb push_back
using namespace std;
int main(){
    int i,j,k,n,m;
    cin>>n>>m;
    printf("%d\n",n+m-1);
    for(i=1;i<=m;i++)printf("%d %d\n",1,i);
    for(i=2;i<=n;i++)printf("%d %d\n",i,m);
    return 0;
}