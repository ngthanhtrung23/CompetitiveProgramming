#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <map>
#include <vector>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

struct Node {
    Node *left, *right, *father;
    int val, key, sum;
} *root, *sentinel;

// Must call initTree before using splay tree
void initTree() {
    sentinel = new Node;
    sentinel -> left = sentinel -> right = sentinel -> father = sentinel;
    sentinel -> val = 0;
    sentinel -> key = sentinel -> sum = 0;
}
void setLink(Node *x, Node *y, bool left) {
    if (left) x -> left = y;
    else x -> right = y;
    y -> father = x;
}
void update(Node *x) {
    x -> sum = x->key + x->left->sum + x->right->sum;
}
void upTree(Node *x) {
    Node *y = x -> father;
    Node *z = y -> father;
    Node *tmp;
    if (y->right == x) {
        tmp = x -> left;
        setLink(x, y, true);
        setLink(y, tmp, false);
    }
    else {
        tmp = x -> right;
        setLink(x, y, false);
        setLink(y, tmp, true);
    }
    setLink(z, x, z->left == y);
    update(y); update(x);
}
void splay(Node *x) {
    while (1) {
        Node *y = x -> father;
        if (y == sentinel) return ;
        Node *z = y -> father;
        if (z != sentinel) {
            if ((z->right == y) == (y->right == x)) upTree(y);
            else upTree(x);
        }
        upTree(x);
    }
}
Node *join(Node *t1, Node *t2) {
    if (t1 == sentinel) return t2;
    if (t2 == sentinel) return t1;
    while (1) {
        // refine(t1); // Used for range cover
        if (t1 -> right == sentinel) break;
        t1 = t1 -> right;
    }
    splay(t1);
    setLink(t1, t2, false);
    update(t1);
    return t1;
}

const int MN = 200111;
int n, a[MN], father[MN], sign[MN], cur;
vector< int > ke[MN];
Node *nodes[MN], *first[MN], *last[MN];

Node *createTree(int l, int r) {
    if (l > r) return sentinel;
    int mid = (l + r) >> 1;
    Node *res = new Node;
    res->left = res->right = res->father = sentinel;
    res->val = a[mid];
    res->key = res->sum = sign[mid];

    Node *left = createTree(l, mid - 1);
    Node *right = createTree(mid+1, r);

    if (left != sentinel) setLink(res, left, true);
    if (right != sentinel) setLink(res, right, false);

    update(res);
    return res;
}

Node *access(Node *root, int k) {
    if (root->left->sum >= k) return access(root->left, k);
    k -= root->left->sum;
    if (k == 1 && root->key == 1) return root;
    k -= root->key;

    return access(root->right, k);
}

void init() {
    FOR(i,1,n) {
        ke[i].clear();
        first[i] = last[i] = sentinel;
    }
    cur = 0;
}

void dfs(int u) {
    ++cur; a[cur] = u; sign[cur] = 1;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        father[v] = u;
        dfs(v);
    }
    ++cur; a[cur] = u; sign[cur] = 0;
}

void visitTree(Node *x, string pref = "") {
    if (x == sentinel) return ;
    visitTree(x->left, pref + "  ");
    cout << pref << x->val << ' ' << x->key << ' ' << x->sum << endl;
    visitTree(x->right, pref + "  ");
}

#define printTree(x)  { cout << #x << ":" << endl; visitTree(x); }

void visit(Node *p) {
    if (p == sentinel) return ;

    visit(p->left);
    visit(p->right);

    if (p->key) first[p->val] = p;
    else last[p->val] = p;
}

int main() {
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        initTree();
        init();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
        }
        dfs(1);
        // PR(a, n+n);

        root = createTree(1, n+n);
        // printTree(root);

        visit(root);

        // FOR(i,1,n) cout << first[i]->val << ' '; cout << endl;
        // FOR(i,1,n) cout << last[i]->val << ' '; cout << endl;

        int q; cin >> q;
        while (q--) {
            // cout << "q = " << q << endl;
            // cerr << q << endl;
            int typ; cin >> typ;
            if (typ == 1) {
                int u, v; cin >> u >> v;
                // cout << typ << ' ' << u << ' ' << v << endl;
                // First, split into 3 parts: [leftmost, first(u)) [first(u), last(u)] and (last[u], rightmost]
                Node *t2 = first[u]; splay(t2);
                Node *t1 = t2->left;
                t2->left = t1->father = sentinel;
                update(t2);

                t2 = last[u]; splay(t2);
                Node *t3 = t2->right;
                t2->right = t3->father = sentinel;
                update(t2);

                // printTree(t1);
                // printTree(t2);
                // printTree(t3);

                t1 = join(t1, t3);

                // Split t1 into 2 parts
                Node *t4 = last[v]; splay(t4);
                Node *t5 = t4->left;
                t4->left = t5->father = sentinel;
                update(t4);

                // printTree(t4);
                // printTree(t5);

                root = join(t5, t2);
                root = join(root, t4);

                // printTree(root);
            } else {
                int k; cin >> k;
                // cout << typ << ' ' << k << endl;
                Node *t = access(root, k);
                splay(t);
                root = t;
                // printTree(root);
                cout << t->val << endl;
            }
            // cout << "q = " << q << endl;
        }
    }
    return 0;
}