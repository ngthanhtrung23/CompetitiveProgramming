#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define sqr(a) ((a)*(a))
#define FR(i,n) for (int i = 0; i < (n); i++)
#define DN(i,a) for(int i = (a)-1; i >= 0; i--)
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define DOWN(i,a,b) for(int i = (a); i >= (b); i--)
#define FORV(i,a) for(typeof(a.begin()) i = a.begin(); i != a.end(); i++)
#define Set(a,c) memset(a, c, sizeof(a))
#define oo 1000000000
#define MAXN 100005

typedef pair<int, int> PII;
typedef vector<int> VI;

struct querry {
    int l,r,i;    
} q[MAXN];

int a[MAXN], m, n, T[MAXN];
VI list[MAXN];
int res[MAXN];

void update(int i, int k) {
    while (i <= n) {
        T[i] += k;
        i += i & (-i);   
    }    
}

int get(int i) {
    int s = 0;
    while (i) {
        s += T[i];
        i -= i & (-i);   
    }    
    return s;
}

void process() {
    int cur = 0;
    FOR(i, 1, m) {
        FOR(j, cur + 1, q[i].r) {
            if (a[j] > n) continue;
            int k = a[j];
            list[k].pb(j);
            int z = list[k].size();
            if (z >= k) {
                update(list[k][z - k], 1);   
            }
            if (z >= k + 1) {
                update(list[k][z - k - 1], -2);   
            }
            if (z >= k + 2) {
                update(list[k][z - k - 2], 1);   
            }
        }
        res[q[i].i] = get(q[i].r) - get(q[i].l - 1);
        cur = q[i].r;
    }    
    FOR(i, 1, m) printf("%d\n", res[i]);
}

bool cmp(querry a, querry b) {
    return a.r < b.r;    
}

int main () {
    cin >> n >> m;
    FOR(i, 1, n) scanf("%d", &a[i]);
    FOR(i, 1, m) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].i = i;
    }
    sort(q + 1, q + 1 + m, cmp);
    process();
    return 0;
}