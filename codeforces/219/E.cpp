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

const long double PI = acos((long double) -1.0);
const int MN = 200111;

struct Node {
    int dist, p;
    int l, r;
};

bool operator < (const Node &a, const Node &b) {
    if (a.dist == b.dist) return a.p > b.p;
    return a.dist < b.dist;
}

int lpos[MN], rpos[MN], hsize;
struct Heap {
    Node a[MN];

    void downHeap(int i) {
        int j = i << 1;
        while (j <= hsize) {
            if (j < hsize && a[j] < a[j+1]) ++j;
            if (a[i] < a[j]) {
                swap(lpos[a[i].l], lpos[a[j].l]);
                swap(rpos[a[i].r], rpos[a[j].r]);
                swap(a[i], a[j]);
            }
            i = j; j = i << 1;
        }
    }

    void upHeap(int i) {
        int j = i >> 1;
        while (i > 1 && a[j] < a[i]) {
            swap(lpos[a[i].l], lpos[a[j].l]);
            swap(rpos[a[i].r], rpos[a[j].r]);
            swap(a[i], a[j]);
            i = j; j = i >> 1;
        }
    }

    void insert(Node &t) {
        if (t.l > t.r) return ;
        ++hsize; a[hsize] = t;
        lpos[t.l] = hsize;
        rpos[t.r] = hsize;
        upHeap(hsize);
    }

    Node remove() {
        Node res = a[1];
        lpos[res.l] = 0; rpos[res.r] = 0;
        if (hsize == 1) {
            hsize = 0;
            return res;
        }

        swap(a[1], a[hsize]);
        lpos[a[1].l] = 1;
        rpos[a[1].r] = 1;
        --hsize;
        downHeap(1);
        return res;
    }

    void print() {
        cout << "Heap:\n";
        FOR(i,1,hsize) {
            cout << a[i].l << ' ' << a[i].r << ' ' << a[i].p << ' ' << a[i].dist << endl;
        }
    }
} h;

int n, m;
int allocated[1000111];

void refine(Node &x) {
    if (x.l == 1 && x.r == n) {
        x.p = 1;
        x.dist = n + 1;
    }
    else if (x.l == 1) {
        x.p = 1;
        x.dist = x.r;
    }
    else if (x.r == n) {
        x.p = n;
        x.dist = n - x.l + 1;
    }
    else {
        x.p = (x.l + x.r) >> 1;
        x.dist = min(x.p - x.l + 1, x.r + 1 - x.p);
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        Node cur;
        cur.l = 1; cur.r = n;
        refine(cur);
        h.insert(cur);

        int type, id;
        Node x, y;
        while (m--) {
            scanf("%d%d", &type, &id);
            if (type == 1) {
                cur = h.remove();
                allocated[id] = cur.p;

                // split cur
                x.l = cur.l; x.r = cur.p - 1;
                if (x.l <= x.r) {
                    refine(x);
                    h.insert(x);
                }
                x.l = cur.p + 1; x.r = cur.r;
                if (x.l <= x.r) {
                    refine(x);
                    h.insert(x);
                }

                printf("%d\n", allocated[id]);

                // cout << "Insert " << id << " at " << allocated[id] << endl;
            }
            else {
                int p = allocated[id];
                // cout << "Remove " << id << " at " << allocated[id] << endl;
                if (rpos[p-1] && lpos[p+1]) {
                    h.a[rpos[p-1]].dist = 1000111000;
                    h.upHeap(rpos[p-1]);
                    x = h.remove();
                    h.a[lpos[p+1]].dist = 1000111000;
                    h.upHeap(lpos[p+1]);
                    y = h.remove();

                    cur.l = x.l; cur.r = y.r;
                    refine(cur);
                    h.insert(cur);
                }
                else if (rpos[p-1]) {
                    h.a[rpos[p-1]].dist = 1000111000;
                    h.upHeap(rpos[p-1]);
                    x = h.remove();

                    cur.l = x.l; cur.r = p;
                    refine(cur);
                    h.insert(cur);
                }
                else if (lpos[p+1]) {
                    h.a[lpos[p+1]].dist = 1000111000;
                    h.upHeap(lpos[p+1]);
                    x = h.remove();
                    cur.l = p; cur.r = x.r;
                    refine(cur);
                    h.insert(cur);
                }
                else {
                    cur.l = cur.r = p;
                    refine(cur);
                    h.insert(cur);
                }
            }

            // h.print();
        }
    }
    return 0;
}
