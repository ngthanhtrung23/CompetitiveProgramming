#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#include<cmath>
#include<deque>
#include<map>
#include<set>
#define oo 1000000000
#define ooll 1ll<<50
#define base 1000000007ll
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
                            /*                           END OF TEMPLATE                            */


string S;
int freda()
{
    int sz=S.size()-1;
    if(S[sz]!='.') return 0;
    if(S[sz-1]!='a') return 0;
    if(S[sz-2]!='l') return 0;
    if(S[sz-3]!='a') return 0;
    if(S[sz-4]!='l') return 0;
    return 1;
}
int rainbow()
{
    if(S[0]!='m') return 0;
    if(S[1]!='i') return 0;
    if(S[2]!='a') return 0;
    if(S[3]!='o') return 0;
    if(S[4]!='.') return 0;
    return 1;
}
void execute()
{
    getline(cin,S);
    if(S.size()<5) printf("OMG>.< I don't know!\n");
    else
    {
        if(freda() && rainbow()) printf("OMG>.< I don't know!\n");
        else if(freda()) printf("Freda's\n");
        else if(rainbow()) printf("Rainbow's\n");
        else printf("OMG>.< I don't know!\n");
    }
}
int main()
{
    int test;
    scanf("%d",&test);
    while(getchar()!='\n') {}
    while(test--) execute();
    return 0;
}