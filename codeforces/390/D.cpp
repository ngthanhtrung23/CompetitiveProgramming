#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <ctime>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#define FOR(a,b,c) for (int a=b,_c=c;a<=_c;a++)
#define FORD(a,b,c) for (int a=b;a>=c;a--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define REPD(i,a) for(int i=(a)-1; i>=0; --i)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sz(a) int(a.size())
#define reset(a,b) memset(a,b,sizeof(a))
#define oo 1000000007

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<pii> r[55*55];

vector<pii> gen(int x, int y){
    vector<pii> res;
    FOR(xt,2,x) res.pb(pii(xt,1));
    FOR(yt,2,y) res.pb(pii(x,yt));
    return res;
}

int main(){
    //freopen("input.txt","r",stdin);
    int m,n,k,K;
    cin>>m>>n>>k;
    K=k;
    int res=0;
    FOR(l,1,m+n-1){
        int x=1, y=l;
        while(y>n){
            ++x;
            --y;
        }
        while(y>=1 && x<=m && k>0 ){
            r[k]=gen(x,y);
            res+=sz(r[k])+1;
            --k;
            ++x;
            --y;
        }
        if(k==0) break;
    }
    printf("%d\n",res);
    FOR(i,1,K){
        printf("(1,1)");
        REP(j,sz(r[i])) printf(" (%d,%d)",r[i][j].fi,r[i][j].se);
        puts("");
    }
    return 0;

}