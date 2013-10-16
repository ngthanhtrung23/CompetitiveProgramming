#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <complex>
using namespace std;
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Ford(i,a,b) for(int i=a;i>=b;i--)
#define fi first
#define se second
#define sr(x) (int)x.size()
#define BUG(x) {cout << #x << " = " << x << endl;}
#define PR(x,a,b) {cout << #x << " = "; For(_,a,b) cout << x[_] << ' '; cout << endl;}
#define Bit(s,i) ((s&(1<<i))>0)
#define Two(x) (1<<x)
const int modul = 1000000007;
const int nmax = 1000;
const double e = 1e-8;
const double pi = acos(-1);
typedef long long ll;
typedef pair<int,int> pii;

int n,stest;
struct node {
    double a,b,c;
};
node s[3];
int a[4],b[4],c[4];
void get1(double &u,double &v,int c) {
    c=90-c;
    u=cos((c*pi)/180);
    v=sin((c*pi)/180);
}
void get2(double &u,double &v,int c) {
    c=180-c;
    u=sin((c*pi)/180);
    v=-cos((c*pi)/180);
}
void Cal(int i,int a,int b,int c) {
    double u,v;
    if (c<=90) get1(u,v,c);
    else if (c<180) get2(u,v,c); else 
    if (c<=270) {
        get1(u,v,c-180);
        u=-u;v=-v;
    } else {
        get2(u,v,c-180);
        u=-u;v=-v;
    }
  //  cout << u <<  " " << v << endl;
    swap(u,v);u=-u;
    s[i].a=u;s[i].b=v;s[i].c=u*a+v*b;
}
int main()
{
 //   freopen("input.txt","r",stdin);
    ios::sync_with_stdio(false);
    for (cin >> stest;stest;stest--) {
        For(i,1,2) cin >> a[i] >> b[i] >> c[i];
        For(i,1,2) Cal(i,a[i],b[i],c[i]);
        double d=(s[1].a*s[2].b - s[2].a*s[1].b);
        double dx = (s[1].c*s[2].b - s[2].c*s[1].b);
        double dy = (s[1].a*s[2].c - s[2].a*s[1].c);
        printf("%.4lf %.4lf\n",dx/d,dy/d);
    }
    return 0;
}










