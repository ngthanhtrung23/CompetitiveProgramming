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
int n;
double t[5001];
double x[5001],y[5001],z[5001];
int main(){
//    freopen("test.in","r",stdin);
//    freopen("test.out","w",stdout);
    cin>>n;
    cin>> x[0] >> y[0] >> z[0];
    double res=1e9;
    FOR(i,1,n){
        cin>>x[i]>>y[i] >> z[i];
        t[i] = sqrt ( (x[i]-x[0])*(x[i]-x[0]) + (y[i]-y[0])*(y[i]-y[0]) + (z[i]-z[0])*(z[i]-z[0]) );
        FOR(j,1,i){
            double d= sqrt ( (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) + (z[i]-z[j])*(z[i]-z[j])  );                
            double c = max(t[j],t[i]) + ( d- fabs( t[i]-t[j] ) )/2.0;
            res=min(res,c);
        }
    }
    printf("%.10lf\n",res);
    return 0;
}
