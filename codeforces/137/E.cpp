#include <stdio.h>
#include <algorithm>
#include <string.h>
#define N 200001
using namespace std;
char s[N];
int d[N],dp[N],sn;
pair<int,int>stack[N];
int isvowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}
int main() {
    int i, n, an1=0,an2=0;
    scanf("%s", s);
    n = strlen(s);
    for(i = 0; i < n; i++) {
        if(isvowel(s[i]))d[i+1]=-1;
        else d[i+1]=2;
    }
    stack[sn++]=make_pair(0,0);
    for(i=1;i<=n;i++){
        dp[i]=d[i]+dp[i-1];
        int pos=lower_bound(stack,stack+sn,make_pair(-dp[i],-10000))-stack;
        if(pos!=sn){
            an1=max(an1,i-stack[pos].second);
        }
        if(-dp[i]>stack[sn-1].first)
            stack[sn++]=make_pair(-dp[i],i);
    }
    for(i=an1;i<=n;i++)
        if(dp[i]-dp[i-an1]>=0)an2++;
    if(an1)printf("%d %d\n",an1,an2);
    else puts("No solution");
    return 0;
}