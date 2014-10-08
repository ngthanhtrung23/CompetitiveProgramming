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
    int i,j,k,r,g,b;
    cin>>r>>g>>b;
    int an=r/3+g/3+b/3;
    if(r>=1&&g>=1&&b>=1)an=max(an,(r-1)/3+(g-1)/3+(b-1)/3+1);
    if(r>=2&&g>=2&&b>=2)an=max(an,(r-2)/3+(g-2)/3+(b-2)/3+2);
    cout<<an<<endl;
    return 0;
}