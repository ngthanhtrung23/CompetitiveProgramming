#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int GI(int& x) {
    return scanf("%d", &x);
}

struct Node {
    int add, l, r;
} nodes[20111000];
int nNode;

int createNode() {
    ++nNode;
    nodes[nNode].l = nodes[nNode].r = 0;
    nodes[nNode].add = 0;
    return nNode;
}

const int MN = 200111;
int n, a[MN], b[MN];
int ver[MN];

int build(int l, int r) {
    if (l == r) return createNode();

    int mid = (l + r) >> 1;
    int cur = createNode();

    nodes[cur].l = build(l, mid);
    nodes[cur].r = build(mid+1, r);
}

int update(int old, int l, int r, int u, int v) {
    if (v < l || r < u) return old;
    if (u <= l && r <= v) {
        int res = createNode();
        nodes[res] = nodes[old];
        nodes[res].add++;
        return res;
    }
    int mid = (l + r) >> 1;
    int res = createNode();
    nodes[res] = nodes[old];

    nodes[res].l = update(nodes[res].l, l, mid, u, v);
    nodes[res].r = update(nodes[res].r, mid+1, r, u, v);
    return res;
}

int get(int i, int l, int r, int u) {
    if (l == r) return nodes[i].add;

    int mid = (l + r) >> 1;
    int res = nodes[i].add;

    if (u <= mid) res += get(nodes[i].l, l, mid, u);
    else res += get(nodes[i].r, mid+1, r, u);

    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) {
            GI(a[i]);
            GI(b[i]);
        }
        ver[0] = build(1, n);
        FOR(i,1,n) {
            ver[i] = update(ver[i-1], 1, n, a[i], b[i]);
        }

//        cout << "----" << endl;
//        FOR(i,1,n) {
//            FOR(j,1,n) cout << get(ver[i], 1, n, j) << ' ';
//            cout << endl;
//        }

        FOR(i,1,n) {
            if (get(ver[n], 1, n, i) < i) printf("-1 ");
            else {
                int l = 1, r = n, res = n;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (get(ver[mid], 1, n, i) >= i) {
                        res = mid;
                        r = mid - 1;
                    }
                    else l = mid + 1;
                }
                printf("%d ", res);
            }
        }
        puts("");
    }
}
