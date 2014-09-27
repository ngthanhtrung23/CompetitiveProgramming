#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

struct Node {
    Node *left, *right, *father;
    int size;
    char key;
    bool rev;
} *root, *sentinel;

void initTree() {
    sentinel = new Node;
    sentinel->left = sentinel->right = sentinel->father = sentinel;
    sentinel->key = ' ';
    sentinel->rev = false;
    sentinel->size = 0;
}

void setLink(Node *x, Node *y, bool left) {
    if (left) x->left = y; else x->right = y;
    y->father = x;
}

void update(Node *x) {
    x->size = x->left->size + 1 + x->right->size;
}

void refine(Node *x) {
    if (x->rev) {
        x->rev = false;
        swap(x->left, x->right);

        x->left->rev = !x->left->rev;
        x->right->rev = !x->right->rev;
    }
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
Node *access2(Node *p, int k) {
    refine(p); // Need for cover range
    if (k <= p->left->size) return access2(p->left, k);
    k -= p->left->size + 1;
    if (!k) return p;
    return access2(p->right, k);
}
Node *access(Node * &root, int k) {
    Node *res = access2(root, k);
    splay(res);
    root = res;
    return res;
}
// Split Node 1..k-1 to tree t1 and Node k..size to tree t2
void split(Node *r, Node * &t1, Node * &t2, int k) {
    if (k == 1) {
        t1 = sentinel;
        t2 = r;
        return ;
    } else if (k == r->size + 1) {
        t1 = r;
        t2 = sentinel;
        return ;
    }
    Node *p = access(r, k);
    t1 = p->left;
    t2 = p;
    t1 -> father = t2 -> left = sentinel;
    update(t2);
}
Node *join(Node *t1, Node *t2) {
    if (t1 == sentinel) return t2;
    if (t2 == sentinel) return t1;
    while (1) {
        refine(t1); // Used for range cover
        if (t1 -> right == sentinel) break;
        t1 = t1 -> right;
    }
    splay(t1);
    setLink(t1, t2, false);
    update(t1);
    return t1;
}

int n, l, r;
string s;

Node *createTree(int l, int r) {
    if (l > r) return sentinel;
    int mid = (l + r) >> 1;

    Node *res = new Node;
    res->father = res->left = res->right = sentinel;
    res->size = 1;
    res->rev = false;
    res->key = s[mid];

    Node *left = createTree(l, mid - 1);
    Node *right = createTree(mid+1, r);

    setLink(res, left, true);
    setLink(res, right, false);
    update(res);

    return res;
}

void print(Node *root, bool rev = false) {
    if (root == sentinel) return;
    if (root->rev) rev = !rev;

    if (!rev) {
        print(root->left, rev);
        cout << root->key;
        print(root->right, rev);
    } else {
        print(root->right, rev);
        cout << root->key;
        print(root->left, rev);
    }
}

#define PRINT(x) { cout << #x << " = "; print(x); cout << endl; }

int main() {
    while (cin >> n >> l >> r) {
        cin >> s;
        initTree();
        root = createTree(0, n-1);
        int q; cin >> q;

        while (q--) {
            char typ; cin >> typ;
            if (typ == 'S') {
                char x, y; cin >> x >> y;
                if (x == 'L') {
                    if (y == 'L') --l;
                    else ++l;
                } else {
                    if (y == 'L') --r;
                    else ++r;
                }
            } else if (typ == 'Q') {
                char c; cin >> c;
                int k = (c == 'L') ? l : r;
                Node *cur = access(root, k);
                // DEBUG(cur->key);
                cout << cur->key;
            } else {
                Node *t1, *tmp, *t2, *t3;

                split(root, tmp, t3, r+1);
                split(tmp, t1, t2, l);
                t2->rev = !t2->rev;

                // PRINT(t1);
                // PRINT(t2);
                // PRINT(t3);

                root = join(t1, t2);
                root = join(root, t3);

                // cout << "Reverse: " << l << ' ' << r << endl;
                // PRINT(root);
            }
        }
        cout << endl;
    }
}

