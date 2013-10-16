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
#define x1 x1_
#define x2 x2_
#define y1 y1_
#define y2 y2_
const int modul = 1000000007;
const int nmax = 1000;
const double e = 1e-8;
const double pi = acos(-1);
typedef long long ll;
typedef pair<int,int> pii;

int n,x1[nmax],x2[nmax],y1[nmax],y2[nmax],stest,w,h;
int main()
{
   // freopen("input.txt","r",stdin);
    ios::sync_with_stdio(false);
    for (cin >> stest;stest;stest--) {
        cin >> w >> h;
        cin >> n;
        For(i,1,n) cin >> x1[i] >> y1[i] >> x2[i] >> y2[i]; 
        bool check=false;
        For(i,1,n) For(j,i+1,n) if ( max(x1[i],x1[j]) < min(x2[i],x2[j]) && max(y1[i],y1[j]) < min(y2[i],y2[j]) ) {
            check=true;
            break;
        }
        if (check) {
            cout << "NONDISJOINT" << endl;
            continue;
        }
        For(i,1,n) if  (x1[i]<0 || x1[i]>w || x2[i]<0 || x2[i]> w || y1[i] < 0 || y1[i] > h|| y2[i]< 0 || y2[i]>h) {
            check=true;
            break;
        }  
        if (check) {
            cout << "NONCONTAINED" << endl;
            continue;
        }
        int res=0;
        For(i,1,n) res+=(x2[i]-x1[i])*(y2[i]-y1[i]);
        if (res!=w*h) cout << "NONCOVERING" << endl;
        else cout << "OK" << endl;
    }
    return 0;
}










