#include<bits/stdc++.h>
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
long long cnt[111],allow[111],best;
int n;
bool valid(void) {
    REP(i,MASK(n)) if (cnt[i]<0) return (false);
    REP(i,MASK(n)) if (__builtin_popcount(i)>1 && cnt[i]>1) return (false);
    REP(i,MASK(n)) REP(j,MASK(n)) if (i!=j)
        if (__builtin_popcount(i&j)>1 && cnt[i]>0 && cnt[j]>0) return (false);
    return (true);
}
bool checkSum(void) {
    long long sum[10];
    memset(sum,0,sizeof sum);
    REP(i,MASK(n)) REP(j,n) if (BIT(i,j)) sum[j]+=cnt[i];
    REP(i,n) if (sum[i]!=allow[i]) return (false);
    return (true);
}
void backtrack(int step) {
//    printf("backtrack %d: ",step);
//    REP(i,MASK(n)) printf("%lld ",cnt[i]); printf("\n");
    if (!valid()) return;
    if (step>=n) {
        if (!checkSum()) return;
        long long tmp=0;
        REP(i,MASK(n)) tmp+=cnt[i];
        minimize(best,tmp);
        return;
    }
    REP(i,MASK(MASK(step))) if (__builtin_popcount(i)<=allow[step]) {
        bool ok=true;
        REP(j,MASK(step)) if (BIT(i,j) && cnt[j]<1) ok=false;
        if (!ok) continue;
        REP(j,MASK(step)) if (BIT(i,j)) {
            cnt[j]--;
            cnt[j|MASK(step)]++;
        }
        cnt[MASK(step)]=allow[step]-__builtin_popcount(i);
        backtrack(step+1);
        REP(j,MASK(step)) if (BIT(i,j)) {
            cnt[j]++;
            cnt[j|MASK(step)]--;
        }
        cnt[MASK(step)]=0;
    }
}
void process(void) {
    cin>>n;
    REP(i,n) cin>>allow[i];
    REP(i,n) best+=allow[i];
    backtrack(0);
    cout<<best<<endl;
}
int main(void) {
    process();
    return 0;
}
