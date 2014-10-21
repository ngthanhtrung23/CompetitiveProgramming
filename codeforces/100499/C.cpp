#include <bits/stdc++.h>
#define pb push_back
#define sqr(x) (x)*(x)
#define sz(a) int(a.size())
#define reset(a,b) memset(a,b,sizeof(a))
#define oo 1000000007

using namespace std;

typedef pair<int,int> pii;
typedef long long ll;


const int maxn=5007;

int T;
int V,H,VG[maxn],HG[maxn],K;
int lN[maxn],lS[maxn],rN[maxn],rS[maxn],llN[maxn],llS[maxn];
int tW[maxn],tE[maxn],bW[maxn],bE[maxn],bbW[maxn],bbE[maxn];
char VD[maxn],HD[maxn];



struct DijkstraMachine{
    int x1,y1,x2,y2;
    vector<pii> Vline,Hline;
    map<pii,int> id;
    int d[222],N,start,finish;
    vector<pii> e[222];
    bool free1[222];

    void init(int a, int b, int c, int d){
        x1=a; y1=b; x2=c; y2=d;
        Vline.clear(); Hline.clear();
    }

    void addVline(int i){
        if(i==-1) return;
        int dir;
        if(VD[i]=='N') dir=1; else dir=-1;
        Vline.pb(pii(VG[i],dir));

    }

    void addHline(int i){
        if(i==-1) return;
        int dir;
        if(HD[i]=='E') dir=1; else dir=-1;
        Hline.pb(pii(HG[i],dir));
    }

    void addLineWithPoint(int x, int y){
        int xi=lower_bound(VG+1,VG+V+1,x)-VG;
        if(xi>V) xi=V;
        int yi=lower_bound(HG+1,HG+H+1,y)-HG;
        if(yi>H) yi=H;
        addVline(llN[xi]);
        addVline(llS[xi]);
        addVline(lN[xi]);
        addVline(lS[xi]);
        addVline(rN[xi]);
        addVline(rS[xi]);
        addHline(bbE[yi]);
        addHline(bbW[yi]);
        addHline(tE[yi]);
        addHline(tW[yi]);
        addHline(bE[yi]);
        addHline(bW[yi]);
    }

    void normalize(){
        sort(Vline.begin(),Vline.end());
        Vline.resize(unique(Vline.begin(),Vline.end())-Vline.begin());
        sort(Hline.begin(),Hline.end());
        Hline.resize(unique(Hline.begin(),Hline.end())-Hline.begin());
    }

    int getid(int x, int y){
        int v=id[pii(x,y)];
        if(v) return v;
        id[pii(x,y)]=++N;
        e[N].clear();
        return N;
    }

    int calc(){
        //init the graph
        id.clear(); N=0;
        start=getid(x1,y1);
        finish=getid(x2,y2);
        for(int i=0; i<sz(Vline); ++i)
            for(int j=0; j<sz(Hline); ++j){
                int xx=Vline[i].first, yy=Hline[j].first;
                int u=getid(xx,yy);

                for(int i2=0; i2<sz(Vline); ++i2){
                    int xx2=Vline[i2].first;
                    int v=getid(xx2,yy);
                    if(v==u) continue;
                    if( (xx2 - xx) * Hline[j].second > 0 )
                        e[u].pb(pii(v,abs(xx2-xx)));
                }

                for(int j2=0; j2<sz(Hline); ++j2){
                    int yy2=Hline[j2].first;
                    int v=getid(xx,yy2);
                    if(v==u) continue;
                    if( (yy2 - yy) * Vline[i].second > 0 )
                        e[u].pb(pii(v,abs(yy2-yy)));
                }

                if(x1==xx && yy!=y1 && (yy-y1)*Vline[i].second>0)
                    e[start].pb(pii(u,abs(yy-y1)));

                if(x1!=xx && yy==y1 && (xx-x1)*Hline[j].second>0)
                    e[start].pb(pii(u,abs(xx-x1)));

                if(x2==xx && yy!=y2 && (y2-yy)*Vline[i].second>0)
                    e[u].pb(pii(finish,abs(y2-yy)));

                if(x2!=xx && yy==y2 && (x2-xx)*Hline[j].second>0)
                    e[u].pb(pii(finish,abs(x2-xx)));

            }

        for(int i=0; i<sz(Vline); ++i)
            if(x1 == x2 && x1==Vline[i].first && (y2-y1)*Vline[i].second>0)
                e[start].pb(pii(finish,abs(y2-y1)));
        for(int j=0; j<sz(Hline); ++j)
            if(y1 == y2 && y1==Hline[j].first && (x2-x1)*Hline[j].second>0)
                e[start].pb(pii(finish,abs(x2-x1)));

        // do dijktra
        for(int u=1; u<=N; ++u) d[u]=oo, free1[u]=1;
        d[start]=0;
        while(1){
            int u=-1, minv=oo;
            for(int v=1; v<=N; ++v)
                if(free1[v] && minv>d[v]){
                    minv=d[v];
                    u=v;
                }
            if(u==-1 || u==finish) break;
            free1[u]=0;
            for(int i=0; i<sz(e[u]); ++i){
                int v=e[u][i].first, w=e[u][i].second;
                if(free1[v] && d[v]>d[u]+w)
                    d[v]=d[u]+w;
            }
        }
        if(d[finish]==oo) d[finish]=-1;
        return d[finish];
    }

}dijk;

int main(){
    //freopen("input.txt","r",stdin);
    scanf("%d",&T);
    for(int tt=1; tt<=T; ++tt){
        scanf("%d%d%d",&V,&H,&K);
        VG[1]=0;
        int v;
        for(int i=2; i<=V; ++i){
            scanf("%d",&v);
            VG[i]=VG[i-1]+v;
        }
        HG[1]=0;
        for(int i=2; i<=H; ++i){
            scanf("%d",&v);
            HG[i]=HG[i-1]+v;
        }
        scanf("%s",VD+1); scanf("%s",HD+1);

        int pN=-1, pS=-1;
        for(int i=1; i<=V; ++i){
            llN[i]=pN; llS[i]=pS;
            if(VD[i]=='N') pN=i;
            else pS=i;
            lN[i]=pN; lS[i]=pS;
        }
        pN=-1; pS=-1;
        for(int i=V; i>=1; --i){
            rN[i]=pN; rS[i]=pS;
            if(VD[i]=='N') pN=i;
            else pS=i;
        }

        int pE=-1, pW=-1;
        for(int i=1; i<=H; ++i){
            bbW[i]=pW; bbE[i]=pE;
            if(HD[i]=='E') pE=i;
            else pW=i;
            bW[i]=pW; bE[i]=pE;
        }
        pE=-1; pW=-1;
        for(int i=H; i>=1; --i){
            tW[i]=pW; tE[i]=pE;
            if(HD[i]=='E') pE=i;
            else pW=i;
        }

        // solve

        int x1,y1,x2,y2;
        for(int it=0; it<K; ++it){
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            dijk.init(x1,y1,x2,y2);
            dijk.addLineWithPoint(x1,y1);
            dijk.addLineWithPoint(x2,y2);
            dijk.normalize();
            printf("%d\n",dijk.calc());
        }
    }
}