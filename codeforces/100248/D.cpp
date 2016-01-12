#pragma comment(linker, "/STACK:16777216")
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <memory.h> 
#include <sstream>
#include <complex>
 
#define REP(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define REPD(i,n) for(int i = (n) - 1; i >= 0; i--)
#define FOR(i,a,b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i,a,b) for (int i = (a), _b = (b); i >= _b; i--)
#define FORN(i,a,b) for(int i=a;i<b;i++)
#define FOREACH(it,c) for (__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
#define RESET(c,x) memset (c, x, sizeof (c))
 
#define sqr(x) ((x) * (x))
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define Aint(c) (c).begin(), (c).end()
#define SIZE(c) (c).size()
 
#define DEBUG(x) { cerr << #x << " = " << x << endl; }
#define PR(a,n) {cerr<<#a<<" = "; FOR(_,1,n) cerr << a[_] << ' '; cerr <<endl;}
#define PR0(a,n) {cerr<<#a<<" = ";REP(_,n) cerr << a[_] << ' '; cerr << endl;}
#define ll long long
#define SZ(a) ((int)a.size())
using namespace std;
 
const double PI = 2.0 * acos (0.0);
 
typedef pair <int, int> PII;
 
template <class T> inline T MAX (T a, T b) { if (a > b) return a; return b; }
template <class T> inline T MIN (T a, T b) { if (a < b) return a; return b; }

#define maxn 111
#define oo 1000111000

struct rec {
    int x0,y0,x,y;
} a[maxn];

int n,w,h;

int att(vector<int> & v) {
    if(v.empty()) return 0;
    if(v.size()==1) {
        rec r = a[v[0]];
        return (r.x-r.x0)*(r.y-r.y0);
    }
    vector<int> lx,ly;
    REP(i,v.size()) {
        lx.PB(a[v[i]].x);
        lx.PB(a[v[i]].x0);
        ly.PB(a[v[i]].y);
        ly.PB(a[v[i]].y0);
    }
    sort(lx.begin(),lx.end());
    sort(ly.begin(),ly.end());


    int x0=oo,y0=oo,x=-oo,y=-oo;
    REP(i,v.size()) {
        x0=min(x0,a[v[i]].x0);
        x=max(x,a[v[i]].x);
        y0=min(y0,a[v[i]].y0);
        y=max(y,a[v[i]].y);
    }


    REP(i,lx.size()) if(i==0 || lx[i]!=lx[i-1]) if(lx[i]!=x && lx[i]!=x0) {
        int x=lx[i];
        bool ok=true;
        REP(j,v.size()) {
            if(a[v[j]].x0<x && x<a[v[j]].x) {
                ok=false;
                break;
            }
        }
        if(ok) {
            vector<int> v1,v2;
            REP(j,v.size()) {
                if(a[v[j]].x0<x)  v1.PB(v[j]);
                else v2.PB(v[j]);
            }
            return max(att(v1),att(v2));
        }
    }

    REP(i,ly.size()) if(i==0 || ly[i]!=ly[i-1]) if(ly[i]!=y && ly[i]!=y0) {
        int y=ly[i];
        bool ok=true;
        REP(j,v.size()) {
            if(a[v[j]].y0<y && y<a[v[j]].y) {
                ok=false;
                break;
            }
        }
        if(ok) {
            vector<int> v1,v2;
            REP(j,v.size()) {
                if(a[v[j]].y0<y)  v1.PB(v[j]);
                else v2.PB(v[j]);
            }
            return max(att(v1),att(v2));
        }
    }

    
    return (x-x0) * (y-y0);
}

int main() {
    ios::sync_with_stdio(false);
    int _;
    cin >> _;
    while(_--) {
        int w,h;
        cin >> w >> h;
        cin >> n;
        FOR(i,1,n) cin >> a[i].x0 >> a[i].y0 >> a[i].x >> a[i].y;

        vector<int> v;
        FOR(i,1,n) v.PB(i);
        cout << att(v) << endl;
    }
    return 0;
}