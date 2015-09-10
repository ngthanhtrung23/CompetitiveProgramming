#include<bits/stdc++.h>
#define MAX   1000100
#define FOR(i,a,b) for (int i=(a),_b=(b);i<=_b;i=i+1)
#define REP(i,n) for (int i=0,_n=(n);i<_n;i=i+1)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define ALL(v) (v).begin(),(v).end()
#define fi   first
#define se   second
using namespace std;
const int d=1000;
pair<int,int> a[MAX];
vector<int> block[MAX];
int n;
bool compLeft(const int &x,const int &y) {
    return (a[x].se<a[y].se);
}
bool compRight(const int &x,const int &y) {
    return (a[x].se>a[y].se);
}
void init(void) {
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&a[i].fi,&a[i].se);
    FOR(i,1,n) block[a[i].fi/d].push_back(i);
}
void process(void) {
    bool mode=true;
    REP(i,MAX) if (!block[i].empty()) {
        sort(ALL(block[i]),mode?compLeft:compRight);
        mode^=1;
    }
    REP(i,MAX) if (!block[i].empty()) FORE(it,block[i]) printf("%d ",*it);
    printf("\n");
}
int main(void) {
    init();
    process();
    return 0;
}