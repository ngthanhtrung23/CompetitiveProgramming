#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <vector>
#include <map>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <string>
#include <queue>
#include <fstream>

#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define FR(i,a) for(int i = 0; i < (a); i++)
#define DR(i,a) for(int i = (a)-1; i >=0; i--)
#define DOWN(i,a,b) for(int i = (a); i >= (b); i--)
#define FORD(i,a,b) for(int i = (a), _b = (b); i >= _b; i--)
#define REPD(i,n) for(int i = (n) - 1; i >= 0; i--)
#define PB push_back
#define MP make_pair

#define F first
#define S second
#define RESET(c,x) memset(c,x,sizeof(c))
#define SIZE(c) (c).size()
#define ALL(c) (c).begin(), (c).end()

#define REP(i,a) for(int i = 0; i < (a); i++)

#define sqr(x) ((x)*(x))
#define oo 1000000009
using namespace std;
/*************************TEMPLATE**********************************/
long long convertToNum(string s)
{
    long long val = 0; FR(i,s.size()) val = val * 10 + s[i] - '0';
    return val;
}
char bu[50];
string convertToString(int a) {
    sprintf(bu,"%d",a);
    return string(bu);
}
long long GCD(long long x,long long y)  {
    if (!x) return y; if (!y) return x;
    if (x == y) return x; if (x < y) return GCD(x,y%x); else return GCD(x%y,y);
}
long long POW(long long x,long long y,long long Base){
    if (!y) return 1; long long u = POW(x,y/2,Base);
    u = (u * u) % Base;
    if (y & 1) return (u * x) % Base; else return u;
}
void extended_euclid(long long A, long long B, long long &x,long long &y) {
    if (A == 1 && B == 0) {
        x = 1;
        y = 0;
        return;
    }
    if (A < B) extended_euclid(B,A,y,x);
    else {
        long long xx,yy;
        extended_euclid(A%B,B,xx,yy);
        x = xx;
        y = yy - (A/B)*xx;
        
    }
}
//newstate = (newstate-1) & oldstate
/**************************CODE HERE*****************************/

void OPEN() {
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
}
#define maxn 100100
long long Base = 1000000007;
int n;
long long Tree[maxn], a[maxn];

void update(int node) {
    for(;node <= 100000; node += node & (-node))
        Tree[node]++;
}
long long visit(int node) {
    long long s = 0;
    for(; node > 0; node -= node & (-node))
        s += Tree[node];
    return s;
}
long long get_greater(int val) {
    return visit(100000) - visit(val-1);
}
vector<int> ds1, ds2;
long long solve(long long X) {
    
    long long val = get_greater(X);
    if (!val) return 0;
    ds1.clear();
    ds2.clear();
    for(long long i = 1; i * i <= X; i++) 
    if (X % i == 0) {
        ds1.push_back(i);
        if (i != X / i) ds2.push_back(X/i);
    }
    DR(i,ds1.size()) ds2.push_back(ds1[i]);
//    FR(i,ds2.size()) cout << ds2[i] << " ";
//    cout << endl;
//    FR(i,ds2.size()) cout << get_greater(ds2[i]) << " ";
//    cout << endl; 
    long long souoc = ds2.size();
    long long prev = val;
    long long res = (POW(souoc, val, Base) - POW(souoc-1, val, Base)) % Base;
    if (res < 0) res += Base;
    for(int i = 1; i < ds2.size(); i++) {
        val = get_greater(ds2[i]);
        long long save_val = val;
        val -= prev;
        prev = save_val;
        res = (res * POW(souoc-i, val, Base)) % Base;
    }
//    cout << res << endl;
    return res;
}
int main() {     
//    OPEN();
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]);
    FOR(i,1,n) update(a[i]);
    long long res = 0;
    FOR(i,1,100000) {
        res = (res + solve(i)) % Base;
    }
    cout
     << res << endl;
    return 0;
}