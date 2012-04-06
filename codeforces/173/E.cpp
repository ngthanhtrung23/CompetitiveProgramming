//#pragma comment(linker, "/STACK:66777216")
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);
const int MN = 200111;

struct Person {
    int age, resp;
} a[MN], savea[MN];

struct Query {
    int type, resp, u, v, x, index;
} q[MN];

bool operator < (const Query &a, const Query &b) {
    if (a.resp != b.resp) return a.resp > b.resp;
    return a.type < b.type;
}

bool cmp1(const Person &a, const Person &b) {
    return a.resp < b.resp;
}

#define _(u) ((u) & (-(u)))

int n, k, c[MN], sAge, first[MN], res[MN], nQuery, bit[MN], it[6*MN];

void update(int u, int k) {
    while (u <= 200000) {
        bit[u]++;
        u += _(u);
    }
}

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

#define CT(i) ((i) << 1)
#define CP(i) (CT(i) + 1)

void update2(int i, int l, int r, int u, int x) {
    if (l > r) return ;
    if (u < l || r < u) return ;
    if (l == r) {
        it[i] = max(it[i], x);
        return ;
    }
    int mid = (l + r) >> 1;
    update2(CT(i), l, mid, u, x);
    update2(CP(i), mid+1, r, u, x);
    it[i] = max(it[CT(i)], it[CP(i)]);
}

int get2(int i, int l, int r, int u, int v) {
    if (l > r) return -1;
    if (v < l || r < u) return -1;
    if (u <= l && r <= v) {
        return it[i];
    }
    int mid = (l + r) >> 1;
    return max(get2(CT(i), l, mid, u, v), get2(CP(i), mid+1, r, u, v));
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) scanf("%d", &a[i].resp);
        FOR(i,1,n) {
            scanf("%d", &a[i].age);
            c[i] = a[i].age;
        }
        c[n+1] = -2000111000;
        c[n+2] = 2000111000;
        sort(c+1, c+n+3);
        sAge = unique(c+1, c+n+3) - c - 1;
        FOR(i,1,n) {
            a[i].age = lower_bound(c+1, c+sAge+1, a[i].age) - c;
        }
//        PR(c, sAge);
//        FOR(i,1,n) cout << a[i].age << ' '; puts("");
        
        FOR(i,1,n) savea[i] = a[i];
        sort(a+1, a+n+1, cmp1);
//        cout << "resp = "; FOR(i,1,n) cout << a[i].resp << ' '; puts("");
        
        // Create update queries
        nQuery = 0;
        FOR(i,1,n) {
            if (i == 1) first[i] = i;
            else if (a[i].resp == a[i-1].resp) first[i] = first[i-1];
            else first[i] = i;
        }
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            update(a[i].age, 1);
            if (i == n || a[i+1].resp != a[i].resp) {
                FOR(x,first[i],i) {
                    ++nQuery;
                    q[nQuery].type = 1;
                    q[nQuery].resp = a[x].resp;
                    int age2 = upper_bound(c+1, c+sAge+1, c[a[x].age]+k) - c - 1;
                    int age1 = lower_bound(c+1, c+sAge+1, c[a[x].age]-k) - c - 1;
                    q[nQuery].u = a[x].age;
                    q[nQuery].x = get(age2) - get(age1);
                    
//                    cout << a[x].resp << ' ' << a[x].age << ' ' << age1 << ' ' << age2 << ' ' << q[nQuery].x << endl;
                }
            }
        }
        
        // Create get queries
        int nQ; scanf("%d", &nQ);
        FOR(Q,1,nQ) {
            int u, v; scanf("%d%d", &u, &v);
            int age1 = min(c[savea[u].age], c[savea[v].age]);
            int age2 = max(c[savea[u].age], c[savea[v].age]);
            
            if (age1 + k < age2 - k) {
                res[Q] = -1;
                continue;
            }
            ++nQuery;
            q[nQuery].type = 2;
            q[nQuery].index = Q;
            q[nQuery].resp = max(savea[u].resp, savea[v].resp);
            q[nQuery].u = lower_bound(c+1, c+sAge+1, age2-k) - c;
            q[nQuery].v = upper_bound(c+1, c+sAge+1, age1+k) - c - 1;
        }
        
        sort(q+1, q+nQuery+1);
//        cout << "Query: \n"; FOR(i,1,nQuery) cout << q[i].type << ' ' << q[i].resp << ' ' << q[i].u << ' ' << q[i].v << ' ' << q[i].x + q[i].index << endl;
        
        memset(it, -1, sizeof it);
        FOR(i,1,nQuery) {
            if (q[i].type == 1) {
                update2(1,1,sAge,q[i].u,q[i].x);
            }
            else {
                res[q[i].index] = get2(1,1,sAge,q[i].u,q[i].v);
            }
        }
        FOR(i,1,nQ) printf("%d\n", res[i]);
        break;
    }
    return 0;
}
