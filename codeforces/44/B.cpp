#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;
#define FOR(i,a,b) for(int i=a,_s=b; i<_s; ++i)
int n,a,b,c;
int main(){
    //freopen("test.in","r",stdin);
//    freopen("test.out","w",stdout);
    cin>> n >> a >> b >> c;
    n<<=1;
    int res=0;
    FOR(i,0,b+1)
        FOR(j,0,c+1){
            int t = n - i*2 - j*4;
            if(t>=0 && t<=a) res++;
        }
    cout << res<<endl;
    return 0;
}
