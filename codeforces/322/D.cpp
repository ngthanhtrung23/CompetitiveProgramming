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
int d[2][155],ty[155],need[155],nn,used[155];
int main(){
    int i,j,k,n,m,res=0;
    char s[155];
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++){
        scanf("%s%d",s,&d[0][i]);
        if(s[0]=='A'){
            ty[i]=1;
            need[nn++]=d[0][i];
        }
        else{
            ty[i]=0;
            need[nn++]=d[0][i]+1;
        }
    }
    for(i=0;i<m;i++){
        scanf("%d",&d[1][i]);
    }
    sort(d[1],d[1]+m);
    sort(need,need+n);
    for(i=j=0;i<n&&j<m;i++){
        while(j<m&&d[1][j]<need[i])j++;
        if(j==m)break;
        else j++;
    }
    int an;
    if(i==n){
        an=0;
        for(i=0;i<m;i++)an+=d[1][i];
        for(i=0;i<n;i++)an-=d[0][i];
        for(i=0;i<n;i++){
            if(ty[i]==0){
                for(j=0;j<m;j++){
                    if(used[j])continue;
                    if(d[1][j]>d[0][i]){
                        used[j]=1;
                        an-=d[1][j]-d[0][i];
                        break;
                    }
                }
            }
        }
        res=an;
    }
    an=0;
    nn=0;
    for(i=0;i<n;i++){
        if(ty[i]==1){
            need[nn++]=d[0][i];
        }
    }
    sort(need,need+nn);
    reverse(need,need+nn);
    reverse(d[1],d[1]+m);
    for(i=1;i<=nn;i++){
        int tmp=0;
        for(j=0;j<i;j++){
            if(d[1][j]>=need[nn-i+j])tmp+=d[1][j]-need[nn-i+j];
        }
        if(j==i)an=max(an,tmp);
    }
    res=max(res,an);
    printf("%d\n",res);
    return 0;
}