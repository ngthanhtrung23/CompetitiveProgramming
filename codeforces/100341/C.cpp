
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
#define double long double
using namespace std;
#define int long long

const int MN = 200111;
const int MOD = 786433;
const double PI = acos((double) -1.0);


ll buf[10000000],*ptr=buf;
void mul( int n, ll *a, ll *b, ll *c ) {
    if ( n<=32 ) {
        REP(i,2*n) c[i]=0;
        REP(i,n) REP(j,n) c[i+j]+=a[i]*b[j];
        REP(i,2*n) c[i]%=MOD;
        return;
    }
    int m=n/2;
    ll *s1=ptr; ptr+=n;
    ll *s2=ptr; ptr+=n;
    ll *s3=ptr; ptr+=n;
    ll *aa=ptr; ptr+=m;
    ll *bb=ptr; ptr+=m;
    REP(i,m) {
        aa[i]=a[i]+a[i+m];
        bb[i]=b[i]+b[i+m];
        if ( aa[i]>=MOD ) aa[i]-=MOD;
        if ( bb[i]>=MOD ) bb[i]-=MOD;
    }
    mul(m,a,b,s1);
    mul(m,a+m,b+m,s2);
    mul(m,aa,bb,s3);
    memcpy(c,s1,n*sizeof(ll));
    memcpy(c+n,s2,n*sizeof(ll));
    REP(i,n) c[i+m]+=s3[i]-s1[i]-s2[i];
    REP(i,2*n) c[i]%=MOD;
    ptr-=4*n;
}

ll u[MN], v[MN], f[22][MN];
int sz[22];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("avl.in", "r", stdin);
    freopen("avl.out", "w", stdout);

    // initialize
    sz[0] = 1;
    FOR(i,1,16) sz[i] = sz[i-1] * 2;

    f[0][0] = 1;
    f[1][1] = 1;

    FOR(i,2,15) {
        // f[i-1] * f[i-1]
        int n;
        mul(sz[i-1], f[i-1], f[i-1], u);
        mul(sz[i-1], f[i-2], f[i-1], v);

        REP(t,sz[i]) if (t) {
            f[i][t] = (u[t-1] + v[t-1] * 2) % MOD;
        }
    }
    int n, h;
    while (cin >> n >> h) {
        if (h < 15) {
            cout << (f[h + 1][n] % MOD + MOD) % MOD << endl;
        }
        else {
            ll res = 0;
            --n;
            REP(i,n+1) {
                res += f[h][i] * f[h][n-i] % MOD;
                res += (2 * f[h-1][i] * f[h][n-i]) % MOD;
            }
            cout << (res % MOD + MOD) % MOD << endl;
        }
    }
}
