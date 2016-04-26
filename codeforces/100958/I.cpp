#include<bits/stdc++.h>
#define MAXB   222
#define MAXS   55
#define FOR(i,a,b) for (int i=(a),_b=(b);i<=_b;i=i+1)
#define FORD(i,b,a) for (int i=(b),_a=(a);i>=_a;i=i-1)
#define REP(i,n) for (int i=0,_n=(n);i<_n;i=i+1)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define ALL(v) (v).begin(),(v).end()
#define fi   first
#define se   second
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X,class Y>
    void minimize(X &x,const Y &y) {
        if (x>y) x=y;
    }
template<class X,class Y>
    void maximize(X &x,const Y &y) {
        if (x<y) x=y;
    }
const int mod=(int)1e9+7;
class DisjointSet {
    private:
    int nComp;
    vector<int> lab;
    public:
    DisjointSet() {
        nComp=0;
    }
    DisjointSet(int n) {
        nComp=n;
        lab.assign(n+1,-1);
    }
    int find(int x) {
        return (lab[x]<0?x:find(lab[x]));
    }
    bool join(int a,int b) {
        int x=find(a);
        int y=find(b);
        if (x==y) return (false);
        if (lab[x]>lab[y]) swap(x,y);
        lab[x]+=lab[y];
        lab[y]=x;
        nComp--;
        return (true);
    }
    int numComp(void) const {
        return (nComp);
    }
};
int bigLen,smallLen,numChar;
vector<pair<long long,int> > maskKMP;
vector<int> cntSmall;
int f[MAXB],g[MAXB];
int pw[MAXB];
int z[MAXS],str[MAXS];
long long imply(DisjointSet &dsu) {
    FOR(i,1,smallLen) str[i-1]=dsu.find(i);
    int L=0,R=0;
	FOR(i,1,smallLen-1) {
        if (i>R) {
            L=R=i;
            while (R<smallLen && str[R-L]==str[R]) R++;
            z[i]=R-L;
            R--;
        }
        else {
            int k=i-L;
            if (z[k]<R-i+1) z[i]=z[k];
            else {
                L=i;
                while (R<smallLen && str[R-L]==str[R]) R++;
                z[i]=R-L;
                R--;
            }
        }
    }
    z[0]=smallLen;
    long long res=0;
    FOR(i,1,smallLen) if (z[smallLen-i]==i) res|=MASK(i);
    return (res);
}
void backtrack(DisjointSet dsu,long long cur,int step) {
    //printf("BACK %lld %d %d\n",cur,step,dsu.numComp());
    if (dsu.numComp()==1) return;
    if (step<1) {
        maskKMP.push_back(make_pair(cur,dsu.numComp()));
        if (maskKMP.size()%10000==0) cerr<<maskKMP.size()<<endl;
        return;
    }
    backtrack(dsu,cur,step-1);
    if (BIT(cur,step)) return;
    FOR(i,1,step) if (dsu.join(i,smallLen-step+i) && dsu.numComp()==1) return;
    cur=imply(dsu);
    while (step>0 && BIT(cur,step)) step--;
    backtrack(dsu,cur,step);
}
void init(void) {
    scanf("%d%d%d",&bigLen,&smallLen,&numChar);
}
void calcSmall(void) {
    pw[0]=1;
    FOR(i,1,MAXB-1) pw[i]=1LL*pw[i-1]*numChar%mod;
    backtrack(DisjointSet(smallLen),0,smallLen-1);
    maskKMP.push_back(make_pair(MASK(smallLen+1)-2,1));
    sort(ALL(maskKMP));
    FORE(it,maskKMP) cntSmall.push_back(pw[it->se]);
    FORD(i,(int)maskKMP.size()-1,0) FOR(j,i+1,(int)maskKMP.size()-1)
        if ((maskKMP[i].fi&maskKMP[j].fi)==maskKMP[i].fi)
            cntSmall[i]=(cntSmall[i]-cntSmall[j]+mod)%mod;
}
int calcBig(long long mask) {
    REP(i,smallLen) f[i]=g[i]=0;
    FOR(i,smallLen,bigLen) {
        g[i]=(pw[i-smallLen]-f[i-smallLen]+mod)%mod;
        FOR(j,1,smallLen-1) if (BIT(mask,smallLen-j)) g[i]=(g[i]-g[i-j]+mod)%mod;
        f[i]=0;
        FOR(j,smallLen,i) f[i]=(f[i]+1LL*g[j]*pw[i-j])%mod;
    }
    return (f[bigLen]);
}
void process(void) {
    int res=0;
    REP(i,maskKMP.size()) res=(res+1LL*calcBig(maskKMP[i].fi)*cntSmall[i])%mod;
    printf("%d\n",res);
}
int main(void) {
    init();
    calcSmall();
    process();
    return 0;
}
