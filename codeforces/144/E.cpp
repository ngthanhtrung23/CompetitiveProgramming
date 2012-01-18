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

int n, m;
struct Rec {
    int F, S, ind;
} a[100111];

bool operator < (const Rec &a, const Rec &b) {
    if (a.F != b.F) return a.F < b.F;
    else return a.S < b.S;
}

int cnt[100111];

vector<int> res, res2;

#define _(x) ((x) & (-(x)))

inline int size(int l, int r) {
    return r - l + 1;
}

int get(int x) {
    int res = 0;
    while (x > 0) {
        res += cnt[x];
        x -= _(x);
    }
    return res;
}

void update(int x, int k) {
    while (x <= n) {
        cnt[x] += k;
        x += _(x);
    }
}

int getFirst(int x) {
    int l = x, r = n;
    while (l <= r) {
        if (get(r) - get(l-1) == size(l,r)) return n+1;
        
        if (l == r) return l;
        
        int mid = (l + r) >> 1;
        if (get(mid) - get(l-1) != size(l,mid)) {
            r = mid;
        }
        else l = mid + 1;
    }
    return n+1;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d%d", &n, &m);
    FOR(i,1,m) {
        scanf("%d%d", &a[i].F, &a[i].S);
        a[i].ind = i;
    }
    
    sort(a+1, a+m+1);
    FOR(i,1,m) {
        int l = a[i].F;
        int r = n + 1 - a[i].S;
        if (l > r) swap(l,r);
        
//        cout << a[i].F << ' ' << a[i].S << ' ' << l << ' ' << r << endl;
        
        int x = getFirst(l);
//        cout << "Found: " << x << endl;
        if (x <= r) {
            res.PB(a[i].ind);
            update(x,1);
        }
    }
    printf("%d\n", res.size());
    REP(x,res.size()) printf("%d ", res[x]);
    return 0;
}
