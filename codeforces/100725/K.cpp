
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
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
    printf("%d ", x->key);
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
void __cut(Node *x, Node * &t1, Node * &t2) {
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
        __cut(x, t1, t2);
    }
}

void insertAtPosition(Node * &root, int x, int pos) {
    Node *t1, *t2;
    cut(root, t1, t2, pos);

    Node *p = createNode(x);

    root = join(t1, p);
    root = join(root, t2);
}

#define MP map< pair<int,int>, Node* >
bool previousSegmentContains(MP::iterator it, int pos) {
    --it;
    return it->first.first <= pos && pos <= it->first.second;
}

int main() {
    freopen("key.in", "r", stdin);
    freopen("key.out", "w", stdout);

    int n, k;
    while (scanf("%d%d", &n, &k) == 2) {
        MP all;

        FOR(i,1,n) {
//            cout << "--------------------" << endl;
            int pos; scanf("%d", &pos);

            auto it = all.upper_bound(make_pair(pos+1, -1));

            if (it != all.begin() && previousSegmentContains(it, pos)) {
                --it;
                int l = it->first.first, r = it->first.second;
                int k = pos - l;
                Node* root = it->second;

//                cout << "INSERT TO TREE: "; print(root); cout << endl;

                insertAtPosition(root, i, k);

                all.erase(it);
                all[make_pair(l, r+1)] = root;

                auto it = all.lower_bound(make_pair(l, r+1));
                // try to merge with next segment
                if (it != all.end()) {
                    auto it_next = it; ++it_next;

                    if (it->first.second + 1 == it_next->first.first) {
                        Node *t1 = it->second, *t2 = it_next->second;
                        int l = it->first.first, r = it_next->first.second;
                        t1 = join(t1, t2);

                        all.erase(it);
                        all.erase(it_next);

                        all[make_pair(l, r)] = t1;
                    }
                }

//                cout << "AFTER INSERT: "; print(root); cout << endl;
            }
            else {
//                cout << "CREATE NEW SEGMENT" << endl;

                Node *p = createNode(i);
                all[make_pair(pos, pos)] = p;

                auto it = all.lower_bound(make_pair(pos, pos));
                // try to merge with next segment
                if (it != all.end()) {
                    auto it_next = it; ++it_next;

                    if (it->first.second + 1 == it_next->first.first) {
                        Node *t1 = it->second, *t2 = it_next->second;
                        int l = it->first.first, r = it_next->first.second;
                        t1 = join(t1, t2);

                        all.erase(it);
                        all.erase(it_next);

                        all[make_pair(l, r)] = t1;
                    }
                }
                
                it = all.lower_bound(make_pair(pos, pos));
                // try to merge with previous segment
                if (it != all.begin()) {
                    auto it_prev = it; --it_prev;

                    if (it_prev->first.second + 1 == it->first.first) {
                        Node *t1 = it_prev->second, *t2 = it->second;
                        int l = it_prev->first.first, r = it->first.second;
                        t1 = join(t1, t2);

                        all.erase(it_prev);
                        all.erase(it);

                        all[make_pair(l, r)] = t1;
                    }
                }
            }

//            DEBUG(pos);
//            DEBUG(i);
//            for(auto p : all) {
//                cout << p.first.first << " --> " << p.first.second << endl;
//                print(p.second);
//                cout << endl;
//            }
        }
        auto it = all.rbegin();
        cout << it->first.second << endl;
        int last = 0;
        for(auto p : all) {
            int l = p.first.first, r = p.first.second;

            FOR(i,last+1,l-1) printf("0 ");
            print(p.second);

            last = r;
        }
        puts("");
    }

    return 0;
}
