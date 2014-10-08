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
long long a,b;
int n;
long long xx=0,yy=0;
char s[1024];
char cc[7]="RULD";
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int get(char c){
    for(int i=0;i<4;i++){
        if(cc[i]==c)return i;
    }
}
void check(long long mul){
    int i;
    long long x=xx*mul;
    long long y=yy*mul;
    if(x==a&&y==b){
        puts("Yes");
        exit(0);
    }
    for(i=0;i<n;i++){
        int id=get(s[i]);
        x+=dx[id];
        y+=dy[id];
        if(x==a&&y==b){
            puts("Yes");
            exit(0);
        }
    }
}
int main(){
    int i,j,k;
    cin>>a>>b;
    scanf("%s",s);
    n=strlen(s);
    for(i=0;i<n;i++){
        int id=get(s[i]);
        xx+=dx[id];
        yy+=dy[id];
    }
    if(xx==0&&yy==0){
        check(0);
    }
    else{
        long long tmp;
        if(xx){
            tmp=a/xx;
            for(long long ha=max(0ll,tmp-5000);ha<=tmp+5000;ha++)check(ha);
        }
        if(yy){
            tmp=b/yy;
            for(long long ha=max(0ll,tmp-5000);ha<=tmp+5000;ha++)check(ha);
        }
    }
    puts("No");
    return 0;
}