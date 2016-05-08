
#include <bits/stdc++.h>
#define int long long
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

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

struct Node {
    int cost;
    Node* child[11];
    int f, tr;
} *root, *nil;

int a[111];
int n, m, k;

Node* createNode() {
    Node* root = new Node();
    root->cost = 0;
    root->f = root->tr = 0;
    REP(i,k) root->child[i] = nil;
    return root;
}

void initTree() {
    nil = new Node();
    nil->cost = 0;
    REP(i,k) nil->child[i] = nil;
    nil->f = nil->tr = 0;

    root = createNode();
}

char tmp[111];

void dfs(Node* p) {
    if (p == nil) return ;

    REP(i,k) dfs(p->child[i]);

    p->f = p->cost + p->child[0]->f;
    p->tr = 0;

    REP(i,k) {
        int cur = p->child[i]->f + p->cost;
        if (cur < p->f) {
            p->f = cur;
            p->tr = i;
        }
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1 && GI(m) == 1 && GI(k) == 1) {
        initTree();
        FOR(i,1,m) {
            GI(a[i]);
        }
        FORD(i,m,1) a[i] -= a[i-1];

        FOR(i,1,n) {
            scanf("%s\n", &tmp[0]);
            string s = " " + string(tmp) + " ";

            Node* p = root;
            FOR(j,1,m) {
                int c = s[j] - '0';
                if (p->child[c] == nil) {
                    p->child[c] = createNode();
                }
                p = p->child[c];
                p->cost += a[j];
            }
        }
        dfs(root);

        Node *p = root;
        FOR(i,1,m) {
            cout << p->tr;
            p = p->child[p->tr];
        }
        cout << endl;
        cout << root->f << endl;
        break;
    }
}
