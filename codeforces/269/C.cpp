#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define V vector<int>
#define MAXN 200111
#define MAXM 400111
using namespace std;

int n,m,eu[MAXM],ev[MAXM],ec[MAXM],ef[MAXM],head[MAXN],current[MAXN],next_[MAXM],savem;
ll excess[MAXN];
int h[MAXN];
int queue[2][MAXM],first[2],last[2];
int q[MAXM];

void addEdge(int u,int v,int c) {
    eu[m]=u; ev[m]=v; ec[m]=c; ef[m]=0; next_[m]=head[u]; head[u]=m; m++;
    eu[m]=v; ev[m]=u; ec[m]=c; ef[m]=0; next_[m]=head[v]; head[v]=m; m++;
}

void input() {
    scanf("%d", &n);
    FOR(i,1,n) head[i]=-1;
    int x; scanf("%d", &x); savem = x;
    while (x--) {
        int u,v,c;
        scanf("%d%d%d", &u, &v, &c);
        addEdge(u,v,c);
    }
    
    FOR(i,1,n) current[i]=head[i];
}

void init() {
    int p=head[1];
    while (p>=0) {
        ef[p]=ec[p]; ef[p^1]=-ec[p];
        excess[ev[p]]+=ec[p];
        excess[1]-=ec[p];
        p=next_[p];
    }
    FOR(v,2,n-1) h[v]=1;
    h[1]=n; h[n]=0;
}

void push(int i) {
    ll delta=min(excess[eu[i]],(ll)ec[i]-ef[i]);
    ef[i]+=delta; ef[i^1]-=delta;
    excess[eu[i]]-=delta;
    excess[ev[i]]+=delta;
}

void lift(int u) {
    int minH=2*MAXN;
    int p=head[u];
    while (p>=0) {
        if (ec[p]>ef[p])
            minH = min(minH, h[ev[p]]);
        p=next_[p];
    }
    h[u]=minH+1;
}

bool avail[MAXN];

void globalLabeling() {
    memset(avail,true,sizeof avail);
    memset(h,0,sizeof h);
    h[1]=n; h[n]=0;
    int first=1, last=1; q[1]=n;
    avail[n]=false;
    while (first<=last) {
        int x=q[first++];
        int p=head[x];
        while (p>=0) {
            int pp=p^1;
            if (avail[eu[pp]] && ef[pp]<ec[pp]) {
                h[eu[pp]]=h[x]+1;
                avail[eu[pp]]=false;
                q[++last]=eu[pp];
            }
            p=next_[p];
        }
        if (first>last && avail[1]) {
            avail[1]=false;
            q[++last]=1;
        }
    }
    FOR(x,1,n) current[x]=head[x];
}

void solve() {
    int now=0;
    first[0]=1; last[0]=0;
    FOR(x,1,n)
        if (x!=1 && x!=n && excess[x]>0)
            queue[now][++last[now]]=x;
    
    globalLabeling();
    int cnt=0;
    int ok=0;
    while (first[now]<=last[now]) {
        first[1-now]=1; last[1-now]=0;
        while (first[now]<=last[now]) {
            int x=queue[now][first[now]++];
            while (current[x]>=0) {
                int p=current[x];
                if (ec[p]>ef[p] && h[eu[p]]>h[ev[p]]) {
                    bool need = (ev[p]!=1 && ev[p]!=n && !excess[ev[p]]);
                    push(current[x]);
                    if (need) queue[1-now][++last[1-now]]=ev[p];
                    if (!excess[x]) break;
                }
                current[x]=next_[current[x]];
            }
            
            if (excess[x]>0) {
                lift(x);
                current[x]=head[x];
                queue[1-now][++last[1-now]]=x;
                cnt++;
                if (cnt==n) {
                    globalLabeling();
                    cnt=0;
                }
            }
        }
        now=1-now;
    }
    REP(i,savem) if (ef[i<<1] >= 0) {
        puts("0");
    }
    else {
        puts("1");
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    input();
    init();
    solve();
    return 0;
}
