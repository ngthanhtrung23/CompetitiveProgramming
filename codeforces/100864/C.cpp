
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

struct Node {
    Node *child[2], *father;
    int size, key;
} *root, *nil;

int initTree() { // Must be called at the start of program
    nil = new Node;
    nil->child[0] = nil->child[1] = nil->father = nil;
    nil->size = nil->key = 0;
    return 0;
}
int ensureInit = initTree();

// For updating node's value based on children (sum, min, max...)
void update(Node *x) {
    if (x == nil) return ;
    x->size = x->child[0]->size + x->child[1]->size + 1;
}

// For pushing down lazy update values
void refine(Node *x) {
    if (x == nil) return ;
}

void print(Node *x) {
    if (x == nil) return;
    refine(x);
    print(x->child[0]);
    cout << x->key << ' ';
    print(x->child[1]);
}

Node *createNode(int key) {
    Node * tmp = new Node();
    tmp->child[0] = tmp->child[1] = tmp->father = nil;
    tmp->key = key;
    tmp->size = 1;
    return tmp;
}

void setChild(Node *x, Node *y, int d) {
    x->child[d] = y;
    y->father = x;
}

Node *build(int l, int r) {
    if (l > r) return nil;
    if (l == r) return createNode(l);

    int mid = (l + r) >> 1;
    Node* res = createNode(mid);
    Node* left = build(l, mid - 1);
    Node* right = build(mid+1, r);

    setChild(res, left, 0);
    setChild(res, right, 1);
    update(res);
    return res;
}

int getDirection(Node *x, Node *y) {
    return x->child[0] == y ? 0 : 1;
}

void rotate(Node *x, int d) {
    Node *y = x->father;
    Node *z = x->child[d];
    setChild(x, z->child[d ^ 1], d);
    setChild(y, z, getDirection(y, x));
    setChild(z, x, d ^ 1);
    update(x);
    update(z);
}

Node *splay(Node *x) {
    if (x == nil) return nil;
    while (x->father != nil) {
        Node *y = x->father;
        Node *z = y->father;
        int dy = getDirection(y, x);
        int dz = getDirection(z, y);
        if (z == nil) {
            rotate(y, dy);
        } else if (dy == dz) {
            rotate(z, dz);
            rotate(y, dy);
        } else {
            rotate(y, dy);
            rotate(z, dz);
        }
    }
    return x;
}

Node *access2(Node *p, int k) {
    refine(p);
    if (k <= p->child[0]->size) return access2(p->child[0], k);
    k -= p->child[0]->size + 1;
    if (!k) return p;
    return access2(p->child[1], k);
}

Node *access(Node * &root, int k) {
    Node *res = access2(root, k);
    splay(res);
    root = res;
    return root;
}

Node *join(Node *x, Node *y) {
    if (x == nil) return y;
    while (1) {
        refine(x);
        if (x->child[1] == nil) break;
        x = x->child[1];
    }
    splay(x);
    setChild(x, y, 1);
    update(x);
    return x;
}

// Note: If cut by position, really careful to return nil if empty
void cut(Node *x, Node * &t1, Node * &t2) {
    t1 = splay(x);
    t2 = t1->child[1];
    t2->father = t1->child[1] = nil;
    update(t1);
}

// t1 = (1 --> k); t2 = (k+1 --> size)
void cut(Node * &root, Node * &t1, Node * &t2, int k) {
    if (k == 0) {
        t1 = nil;
        t2 = root;
    } else if (k == root->size) {
        t1 = root;
        t2 = nil;
    } else {
        Node *x = access(root, k);
        cut(x, t1, t2);
    }
}

Node *create(int from, int to) {
    if (from > to) return nil;

    int mid = (from + to) >> 1;
    Node *p = createNode(mid);
    Node *left = create(from, mid - 1);
    Node *right = create(mid + 1, to);

    if (left != nil) setChild(p, left, 0);
    if (right != nil) setChild(p, right, 1);
    update(p);
    return p;
}

string s;
pair< pair<int,int>, int > queries[50111];
int q;

void go(Node* root) {
    if (root == nil) return ;
    go(root->child[0]);
    cout << s[root->key - 1];
    go(root->child[1]);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("coding.in", "r", stdin);
    freopen("coding.out", "w", stdout);
    while (cin >> s) {
        cin >> q;
        FOR(i,1,q) cin >> queries[i].first.first >> queries[i].first.second >> queries[i].second;

        int n = SZ(s);
        Node* root = build(1, n);
//        cout << "root = ";
//        print(root);
//        cout << endl;

        FORD(turn,q,1) {
            int i = queries[turn].first.first;
            int j = queries[turn].first.second;
            int k = queries[turn].second;

            Node*tmp, *tmp2, *tmp3, *t1, *t2, *t3, *t4;
            cut(root, tmp, t4, j);
            cut(tmp, tmp2, t3, i+k-1);
            cut(tmp2, t1, t2, i-1);

//            cout << "t1 = "; print(t1); cout << endl;
//            cout << "t2 = "; print(t2); cout << endl;
//            cout << "t3 = "; print(t3); cout << endl;
//            cout << "t4 = "; print(t4); cout << endl;

            root = join(t1, t3);
            root = join(root, t2);
            root = join(root, t4);

//            cout << "root = "; print(root); cout << endl;
        }
        go(root);
        cout << endl;
    }
}
