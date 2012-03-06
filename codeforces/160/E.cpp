#include <iomanip>
#include <sstream>
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
using namespace std;

const double PI = acos(-1.0);

set< pair<int,int> > s[300111];
pair<int,int> res;
int c[100111];
pair< pair<int,int>, pair<int,int> > query[200111];
int result[100111];

#define CT(x) ((x)<<1)
#define CP(x) (CT(x) + 1)

void update(int i, int l, int r, int u, int k, int k2) {
    if (l > r) return ;
    if (u < l || r < u) return ;
    if (l <= u && u <= r) {
//        cout << "insert " << k << ' ' << k2 << " into " << i << endl;
        s[i].insert(MP(k, k2));
    }
    if (l == r) return ;
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, k, k2);
    update(CP(i), mid+1, r, u, k, k2);
}

pair<int,int> now;
set< pair<int,int> > :: iterator it;
void get(int i, int l, int r, int u, int k) {
    if (l > r) return ;
    if (u < c[l]) return ;
    if (c[r] <= u) {
        it = s[i].lower_bound(MP(k,0));
        if (it != s[i].end()) {
//            cout << "got " << it->F << ' ' << it->S << " from " << i << endl;
            if (it->F < res.F) {
                res = *it;
            }
        }
        return ;
    }
    int mid = (l + r) >> 1;
    get(CT(i), l, mid, u, k);
    get(CP(i), mid+1, r, u, k);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        int s, f, t, l, r, b;
        int q = 0, k = 0;
        FOR(i,1,n) {
            scanf("%d%d%d", &s, &f, &t);
            c[++k] = s;
            query[++q] = MP(MP(f,i), MP(s,t));
        }
        sort(c+1, c+k+1);
        k = unique(c+1, c+k+1) - c - 1;
//        cout << k << endl; FOR(i,1,k) cout << c[i] << ' '; puts("");
        FOR(i,1,q) query[i].S.F = lower_bound(c+1, c+k+1, query[i].S.F) - c;
        
        FOR(i,1,m) {
            scanf("%d%d%d", &l, &r, &b);
            query[++q] = MP(MP(r,-i), MP(l,b));
        }
        
        sort(query + 1, query + q + 1);
        FORD(i,q,1) {
//            cout << query[i].F.F << ' ' << query[i].F.S << ' ' << query[i].S.F << ' ' << query[i].S.S <<endl;
            if (query[i].F.S > 0) {
                update(1, 1, k, query[i].S.F, query[i].S.S, query[i].F.S);
            }
            else {
                res.F = 1000111000;
                get(1, 1, k, query[i].S.F, query[i].S.S);
                if (res.F == 1000111000) res.S = -1;
                result[-query[i].F.S] = res.S;
            }
        }
//        cout << "result = ";
        FOR(i,1,m) printf("%d ", result[i]);
        puts("");
    }
    return 0;
}
