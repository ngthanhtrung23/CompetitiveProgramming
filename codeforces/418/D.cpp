#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <cmath>
//#include <conio.h>
using namespace std;
#define FOR(i, a, b) for(int i=a; i<=b; i++)
#define DOW(i, a, b) for(int i=a; i>=b; i--)
#define FOREACH(it, c) for(typeof(c.begin()) it=c.begin(); it!=c.end(); it++)
#define RESET(c, val) memset(c, val, sizeof(c))
#define maxn 100005
#define oo 10000000

int test, n, CC, u, v, q, res;
int head[maxn], lik[maxn*2], adj[maxn*2];
int chil[maxn], num[maxn], g[maxn], fmax1[maxn], fmax2[maxn], fmax3[maxn], high[maxn];
int p[maxn][20], f[maxn][20];
int it[maxn*4], VV[maxn];

void dfs(int u) {
    CC++, num[u]=CC, chil[u]=1;
    FOR(i, 1, 18) p[u][i]=p[p[u][i-1]][i-1];
    int i=head[u], v;
    while (i!=0) {
        v=adj[i];
        if (num[v]==0) {
            p[v][0]=u;
            high[v]=high[u]+1;
            dfs(v);
            if (fmax1[u]<fmax1[v]+1) {
                fmax3[u]=fmax2[u];
                fmax2[u]=fmax1[u];
                fmax1[u]=fmax1[v]+1;
            } else if (fmax2[u]<fmax1[v]+1) {
                fmax3[u]=fmax2[u];
                fmax2[u]=fmax1[v]+1;
            } else if (fmax3[u]<fmax1[v]+1)
                  fmax3[u]=fmax1[v]+1;
            chil[u]+=chil[v];
        }
        i=lik[i];
    }
}
void getG(int u, int val) {
    g[u]=val;
    int i=head[u], v;
    while (i!=0) {
        v=adj[i];
        if (p[v][0]==u) {
            if (fmax1[u]==fmax1[v]+1) getG(v, max(val+1, fmax2[u]+1));
                else getG(v, max(val+1, fmax1[u]+1));
        }
        i=lik[i];
    }
}
void getF(int u) {
    FOR(i, 1, 18)
        f[u][i] = max(f[u][i-1], f[p[u][i-1]][i-1] + (1<<(i-1)));
    int i=head[u], v;
    while (i!=0) {
        v=adj[i];
        if (p[v][0]==u) {
            if (fmax1[u]==fmax1[v]+1) f[v][0]=fmax2[u]+1;
                else f[v][0]=fmax1[u]+1;
            getF(v);
        }
        i=lik[i];
    }
}
void build(int node, int l, int h) {
    if (l==h) {it[node]=VV[l]; return;}
    int m=(l+h)>>1;
    build(node<<1, l, m);
    build((node<<1)+1, m+1, h);
    it[node]=max(it[node<<1], it[(node<<1)+1]);
}
int get(int node, int l, int h, int u, int v) {
    if (l>v || h<u || u>v) return 0;
    if (u<=l && h<=v) return it[node];
    int m=(l+h)>>1;
    return max(get(node*2, l, m, u, v), get(node*2+1, m+1, h, u, v));
}
int find(int u, int dis) {
    DOW(i, 18, 0)
        if ((1<<i) <= dis) dis-= 1<<i, u=p[u][i];
    return u;
}
int getval1(int u, int v) {
    int res=0, dd=0;
    DOW(i, 18, 0)
        if (high[p[u][i]]>=high[v]) {
            res=max(f[u][i]+dd, res);
            dd+=1<<i;
            u=p[u][i];
        }
    return res;
}
int getval2(int u, int v) {
    int l1=num[u], h1=num[u]+chil[u]-1;
    int l2=num[v], h2=num[v]+chil[v]-1;
    return max(get(1, 1, n, l1, l2-1), get(1, 1, n, h2+1, h1));
}
int main() {
    //freopen("test.inp", "r", stdin);
    //freopen("test.out", "w", stdout);
    test = 1;
    FOR(t, 1, test) {
        RESET(head, 0);
        scanf("%d", &n);
        FOR(i, 1, n-1) {
            scanf("%d%d", &u, &v);
            adj[i]=v, lik[i]=head[u], head[u]=i;
            adj[i+n]=u, lik[i+n]=head[v], head[v]=i+n;
        }
        scanf("%d", &q);
        RESET(fmax1, 0); RESET(fmax2, 0); RESET(fmax3, 0); RESET(p, 0);
        RESET(chil, 0);
        RESET(num, 0); CC=0;
        high[1]=1;
        dfs(1);
        getG(1, 0);
        high[0]=0; FOR(i, 0, 18) f[0][i]=-oo;
        getF(1);

        FOR(i, 1, n) VV[num[i]]=high[i];
        build(1, 1, n);

        FOR(kaka, 1, q) {
            scanf("%d%d", &u, &v);
            if (high[u]<high[v]) swap(u, v);
            int uu=u, vv=v;
            DOW(i, 18, 0) if (high[p[uu][i]]>=high[vv]) uu=p[uu][i];
            if (uu==vv) {
                int dis=high[u]-high[v];
                int z = find(u, dis/2);
                int r = u;
                DOW(i, 18, 0) if (high[p[r][i]]>=high[v]+1) r=p[r][i];
                if (fmax1[v]==fmax1[r]+1) res=fmax2[v]; else res=fmax1[v];
                res = max(res, max(fmax1[u], g[v]));
                res = max(res, max(getval1(u, z), getval2(v, z)-high[v]));
            } else {
                DOW(i, 18, 0) if (p[uu][i]!=p[vv][i]) uu=p[uu][i], vv=p[vv][i];
                int lca=p[vv][0];
                int z;
                if ((high[u]+high[v])%2==1) z=find(u, (high[u]+high[v]-high[lca]*2)/2);
                    else z=find(u, (high[u]+high[v]-high[lca]*2)/2-1);

                int r1=fmax1[uu]+1, r2=fmax1[vv]+1, rr=-1;
                if (fmax1[lca]==r1) r1=-1;
                    else if (fmax1[lca]==r2) r2=-1;
                    else if (rr==-1) rr=fmax1[lca];
                if (fmax2[lca]==r1) r1=-1;
                    else if (fmax2[lca]==r2) r2=-1;
                    else if (rr==-1) rr=fmax2[lca];
                if (fmax3[lca]==r1) r1=-1;
                    else if (fmax3[lca]==r2) r2=-1;
                    else if (rr==-1) rr=fmax3[lca];
                res=rr+high[v]-high[lca];
                res=max(res, max(fmax1[u], getval1(u, z)));
                res=max(res, fmax1[v]);
                res=max(res, g[lca]+high[v]-high[lca]);
                res=max(res, getval2(uu, z)-high[lca]+high[v]-high[lca]);
                res=max(res, getval1(v, vv));
            }
            printf("%d\n", res);
        }
    }
    //getch();
    return 0;
}
