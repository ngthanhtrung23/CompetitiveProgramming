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
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

const long double PI = acos((long double) -1.0);
const int MN = 200111;
const long long MOD1 = 1000000007;
const long long MOD2 = 1000000009;
const long long BASE = 1000003;

long long power(long long x, long long k, long long MOD) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1, MOD);
    mid = (mid * mid) % MOD;
    if (k & 1) return (mid * x) % MOD;
    else return mid;
}

struct Hash {
    long long u;

    Hash() { u = 0; }
    Hash(long long u) : u(u) {};

    Hash operator + (Hash a) { return Hash((u+a.u) % MOD1); }
    Hash operator - (Hash a) { return Hash((u-a.u+MOD1) % MOD1); }
    Hash operator * (long long k) { return Hash((u*k) % MOD1); }
    Hash operator * (Hash a) { return Hash((u*a.u) % MOD1); }
};

bool operator == (const Hash &a, const Hash &b) {
    return a.u == b.u;
}

struct Node {
    Hash sum, mul;
    int sz;
} it[MN * 3];

int n, m, a[MN], b[MN], ina[MN], inb[MN];
long long RBASE1, RBASE2;
Hash p[MN];


#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void cal(int i) {
    it[i].sum = it[CT(i)].sum + it[CP(i)].sum;
    it[i].sz = it[CT(i)].sz + it[CP(i)].sz;
}

void down(int i) {
    it[CT(i)].mul = it[CT(i)].mul * it[i].mul;
    it[CT(i)].sum = it[CT(i)].sum * it[i].mul;

    it[CP(i)].mul = it[CP(i)].mul * it[i].mul;
    it[CP(i)].sum = it[CP(i)].sum * it[i].mul;

    it[i].mul = Hash(1);
}

int count(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sz;
    int mid = (l + r) >> 1;
    return count(CT(i), l, mid, u, v) + count(CP(i), mid+1, r, u, v);
}

void add(int i, int l, int r, int u, Hash k) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].mul = Hash(1);
        it[i].sum = k;
        it[i].sz = 1;
        return ;
    }
    down(i);
    int mid = (l + r) >> 1;
    add(CT(i), l, mid, u, k);
    add(CP(i), mid+1, r, u, k);

    cal(i);
}

void remove(int i, int l, int r, int u) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].mul = Hash(1);
        it[i].sum = Hash(0);
        it[i].sz = 0;
        return ;
    }
    down(i);
    int mid = (l + r) >> 1;
    remove(CT(i), l, mid, u);
    remove(CP(i), mid+1, r, u);

    cal(i);
}

void mul(int i, int l, int r, int u, int v, Hash k) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].mul = it[i].mul * k;
        it[i].sum = it[i].sum * k;
        return ;
    }
    down(i);
    int mid = (l + r) >> 1;
    mul(CT(i), l, mid, u, v, k);
    mul(CP(i), mid+1, r, u, v, k);

    cal(i);
}

int cnt;

void init(int i, int l, int r) {
    if (l == r) {
        if (b[l] <= n) {
            it[i].sum = Hash(b[l]) * p[cnt++];
            it[i].mul = Hash(1);
            it[i].sz = 1;
        }
        else {
            it[i].sum = Hash(0);
            it[i].mul = Hash(1);
            it[i].sz = 0;
        }
        return ;
    }

    int mid = (l + r) >> 1;
    init(CT(i), l, mid);
    init(CP(i), mid+1, r);

    cal(i);
    it[i].mul = Hash(1);
}

void print(int i, int l, int r) {
    cout << i << ' ' << l << ' ' << r << ":   " << it[i].sum.u << "   " << it[i].mul.u << "   " << it[i].sz << endl;
    if (l == r) return ;
    int mid = (l + r) >> 1;
    print(CT(i), l, mid);
    print(CP(i), mid+1, r);
}

int main() {
    RBASE1 = power(BASE, MOD1 - 2, MOD1);
    RBASE2 = power(BASE, MOD2 - 2, MOD2);
    p[0] = Hash(1);
    FOR(i,1,200000) {
        p[i] = p[i-1] * BASE;
    }

    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]), ina[a[i]] = i;
        FOR(i,1,m) scanf("%d", &b[i]), inb[b[i]] = i;

        cnt = 0;
        init(1, 1, m);

        Hash increase = Hash(0);
        REP(i,n) increase = increase + p[i];

        Hash cur = Hash(0);
        FOR(i,1,n) cur = cur + p[i-1] * a[i];

        int res = 0;

        FOR(i,1,m-n+1) {
            // cout << "cur = "; cur.print();
            // cout << "root = "; it[1].sum.print();
            if (cur == it[1].sum) ++res;

            // Remove i
            int u = inb[i];
            remove(1, 1, m, u);
            mul(1, 1, m, u+1, m, Hash(RBASE1));

            // Add i+n
            if (i+n > m) break;
            u = inb[i+n];
            int cnt = count(1, 1, m, 1, u);
            add(1, 1, m, u, p[cnt] * (i+n));
            mul(1, 1, m, u+1, m, Hash(BASE));

            // puts("IT:");
            // print(1, 1, m);

            cur = cur + increase;
        }
        cout << res << endl;
    }
    return 0;
}
