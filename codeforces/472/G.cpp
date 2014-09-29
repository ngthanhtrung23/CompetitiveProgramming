#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)
#define PR(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 200111;
#define Int unsigned int
#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))

char a[MN], b[MN];
Int maska[32][MN], maskb[32][MN];
int cnt[TWO(16)], la, lb;

const int allOne = (1<<16) - 1;
inline int count(Int x) { return (cnt[(x)>>16] + cnt[x & allOne]); } 

int main() {
    REP(i,TWO(16)) cnt[i] = __builtin_popcount(i);

    while (gets(a) && gets(b)) {
        la = strlen(a), lb = strlen(b);
        memset(maska, 0, sizeof maska);
        memset(maskb, 0, sizeof maskb);
        REP(start,32) {
            REP(i,la) if (a[i+start] == '1') maska[start][i >> 5] |= 1 << (i & 31);
            REP(i,lb) if (b[i+start] == '1') maskb[start][i >> 5] |= 1 << (i & 31);
        }
        int q; scanf("%d\n", &q);
        while (q--) {
            int u, v, len; scanf("%d%d%d\n", &u, &v, &len);
            int atA = u >> 5, atB = v >> 5;
            int masku = u & 31, maskv = v & 31;
            int i = 0, res = 0;
            while (i + 32 <= len) {
                res += count(maska[masku][atA++] ^ maskb[maskv][atB++]);
                i += 32;
            }
            while (i < len) {
                res += (a[u+i] != b[v+i]);
                ++i;
            }
            cout << res << endl;
        }
    }
    return 0;
}
