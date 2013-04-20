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
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

const long double PI = acos((long double) -1.0);

struct Node {
    Node *left, *right, *father;
    int size;
    char key;
} *root, *sentinel;

void print(Node *root) {
    if (root == sentinel) return ;

    print(root->left);
    cout << root->key;
    print(root->right);
}

// Must call initTree before using splay tree
void initTree() {
    sentinel = new Node;
    sentinel -> left = sentinel -> right = sentinel -> father = sentinel;
    sentinel -> size = 0;
    sentinel -> key = 0;
}
void setLink(Node *x, Node *y, bool left) {
    if (left) x -> left = y;
    else x -> right = y;
    y -> father = x;
}
void update(Node *x) {
    x -> size = x -> left -> size + x -> right -> size + 1;
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
        if (z != sentinel)
            if ((z->right == y) == (y->right == x)) upTree(y);
            else upTree(x);
        upTree(x);
    }
}
Node *access2(Node *p, int k) {
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
        if (t1 -> right == sentinel) break;
        t1 = t1 -> right;
    }
    splay(t1);
    setLink(t1, t2, false);
    update(t1);
    return t1;
}
void insert(Node * &r, int k, char x) { // insert x at kth position
    Node *p = new Node;
    p->size = 1;
    p->key = x;
    p->left = p->right = p->father = sentinel;
    Node *t1, *t2;
    split(r, t1, t2, k);
    r = join(t1, p);
    r = join(r, t2);
}
void del(Node * &r, int k) { // delete kth position
    r = access(r, k);
    Node *t1 = r->left, *t2 = r->right;
    delete r;
    t1->father = sentinel;
    t2->father = sentinel;
    r = join(t1, t2);
}

char a[1000111];

Node * buildTree(int l, int r) {
    if (l > r) return sentinel;

    int mid = (l + r) >> 1;
    Node *cur = new Node();
    cur->left = cur->right = cur->father = sentinel;
    cur->key = a[mid];
    cur->size = r - l + 1;

    Node *left = buildTree(l, mid-1);
    if (left != sentinel) setLink(cur, left, true);
    Node *right = buildTree(mid+1, r);
    if (right != sentinel) setLink(cur, right, false);

    return cur;
}

int main() {
    freopen("collider.in", "r", stdin);
    freopen("collider.out", "w", stdout);
    int n, q;
    while (scanf("%d%d\n", &n, &q) == 2) {
        initTree();
        scanf("%s\n", &a[1]);
        root = buildTree(1, n);
        // print(root); cout << endl;

        while (q--) {
            char c;
            scanf("%c\n", &c);
            if (c == 'a') {
                int u, v; scanf("%d %d\n", &u, &v);
                char c = access(root, u)->key;
                del(root, u);
                insert(root, v, c);
                // print(root); cout << endl;
            }
            else {
                int x; scanf("%d\n", &x);
                printf("%c\n", access(root, x)->key);
            }
        }
    }
    return 0;
}
