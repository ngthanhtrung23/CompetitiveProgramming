
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 200111;

struct Node {
    int left, right;
    int add;
} nodes[11000111];
int nNode, versions[MN];

int n, q, root;
int getIn[MN], getOut[MN], id, h[MN], father[20][MN];
vector<int> ke[MN];

void dfs1(int u) {
    getIn[u] = ++id;
    for(int v : ke[u]) {
        h[v] = h[u] + 1;
        father[0][v] = u;
        dfs1(v);
    }
    getOut[u] = ++id;
}

void initLCA() {
    FOR(t,1,17) {
        FOR(u,1,n)
            father[t][u] = father[t-1][ father[t-1][u] ];
    }
}

int lca(int u, int v) {
    if (h[u] != h[v]) {
        if (h[u] > h[v]) swap(u, v);
        FORD(t,17,0)
            if (h[ father[t][v] ] >= h[u]) {
                v = father[t][v];
            }
    }
    if (u == v) return u;

    FORD(t,17,0)
        if (father[t][u] != father[t][v]) {
            u = father[t][u];
            v = father[t][v];
        }
    return father[0][u];
}

int build(int l, int r) {
    if (l == r) {
        ++nNode;
        nodes[nNode].left = nodes[nNode].right = 0;
        nodes[nNode].add = 0;
        return nNode;
    }
    int mid = (l + r) >> 1;
    int left = build(l, mid);
    int right = build(mid+1, r);

    ++nNode;
    nodes[nNode].left = left;
    nodes[nNode].right = right;
    nodes[nNode].add = 0;
    return nNode;
}

int update(int id, int l, int r, int u, int v, int val = 1) {
    if (v < l || r < u) return id;
    if (u <= l && r <= v) {
        ++nNode;
        nodes[nNode] = nodes[id];
        nodes[nNode].add += val;
        return nNode;
    }
    int mid = (l + r) >> 1;
    int left = update(nodes[id].left, l, mid, u, v, val);
    int right = update(nodes[id].right, mid+1, r, u, v, val);

    ++nNode;
    nodes[nNode].left = left;
    nodes[nNode].right = right;
    nodes[nNode].add = nodes[id].add;
    return nNode;
}

int get(int id, int l, int r, int u) {
    if (l == r) return nodes[id].add;

    int mid = (l + r) >> 1;
    if (u <= mid) return nodes[id].add + get(nodes[id].left, l, mid, u);
    else return nodes[id].add + get(nodes[id].right, mid+1, r, u);
}

// precondition: u is ancestor of v, versions: (from, to]
int countBad(int fromVersion, int toVersion, int u, int v, bool countu) {
    int x = get(versions[toVersion], 1, n+n, getIn[v])
            - get(versions[fromVersion], 1, n+n, getIn[v]);

    if (countu) u = father[0][u];
    int y = (u == 0)
            ? 0
            : (get(versions[toVersion], 1, n+n, getIn[u])
            - get(versions[fromVersion], 1, n+n, getIn[u]));

    return x - y;
}

// precondition: u is ancestor of v
int countGood(int fromVersion, int toVersion, int u, int v, bool countu) {
    int bad = countBad(fromVersion, toVersion, u, v, countu);

    if (countu) u = father[0][u];
    return h[v] - h[u] - bad;
}

int getFather(int u, int jump) {
    FORD(i,16,0)
        if (jump >= (1<<i)) {
            u = father[i][u];
            jump -= 1<<i;
        }
    return u;
}

int getKth(int u, int jump, int fromVersion, int toVersion, int k) {
//    cout << u << ' ' << jump << ' ' << k << endl;
    int left = 0, right = jump, res = getFather(u, jump);
    while (left <= right) {
        int mid = (left + right) >> 1;

        int fat = getFather(u, mid);
        if (countGood(fromVersion, toVersion, fat, u, true) >= k) {
            res = fat;
            right = mid - 1;
        }
        else left = mid + 1;
    }
    return res;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();

        FOR(i,1,n) {
            int u; scanf("%d", &u);
            if (u == 0) root = i;
            else ke[u].push_back(i);
        }
        id = 0;
        h[root] = 1;
        dfs1(root);
        initLCA();

//        PR(getIn, n);
//        PR(getOut, n);

        nNode = 0;
        versions[0] = build(1, n+n);
        int q; scanf("%d", &q);
        FOR(i,1,q) {
            int typ; scanf("%d", &typ);
//            DEBUG(i);
            if (typ == 1) {
                int u; scanf("%d", &u);
                versions[i] = update(versions[i-1], 1, n+n, getIn[u], getOut[u]);

//                cout << "Paint: " << u << endl;
            }
            else {
                versions[i] = versions[i-1];
                int a, b, k, y; scanf("%d%d%d%d", &a, &b, &k, &y);
                int l = lca(a, b);

//                cout << a << " --> " << b << endl;
//                DEBUG(l);
                if (countGood(y, i, a, a, true)) ++k;

                int firstHalf = countGood(y, i, l, a, true);
                int secondHalf = countGood(y, i, l, b, false);
                int nGood = firstHalf + secondHalf;
                if (nGood < k) {
                    puts("-1");
                    continue;
                }
                if (countGood(y, i, b, b, true) && k == nGood) {
                    puts("-1");
                    continue;
                }

//                DEBUG(countGood(y, i, l, a, true));
//                DEBUG(countGood(y, i, l, b, false));

                if (firstHalf >= k) {
//                    cout << "1st half" << endl;
                    int jump = h[a] - h[l];

                    printf("%d\n", getKth(a, jump, y, i, k));
                }
                else {
//                    cout << "2nd half" << endl;
                    k -= firstHalf;
                    k = secondHalf - k + 1;
                    int jump = h[b] - h[l] - 1;

                    printf("%d\n", getKth(b, jump, y, i, k));
                }
            }
        }
    }
    return 0;
}

