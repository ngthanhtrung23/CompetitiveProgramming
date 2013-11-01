#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
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

struct Node {
    Node *left, *right;
} *root;

int r, n;
long long x[111];

void insert(Node* &p, int level, long long val) {
    if (p == NULL) {
        p = new Node();
        p->left = p->right = NULL;
    }
    if (level < n) {
        if (x[level+1] == val * 2)
            insert(p->left, level+1, val*2);
        else
            insert(p->right, level+1, val*2+1);
    }
}

vector<long long> res;

void visit(Node* &p, int level, long long val) {
    if (p == NULL) {
        res.push_back(val);
        return ;
    }
    if (level < n) {
        visit(p->left, level+1, val*2);
        visit(p->right, level+1, val*2+1);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> r) {
        ++n;
        root = NULL;
        while (r--) {
            long long u; cin >> u;
            FORD(i,n,1) {
                x[i] = u;
                u >>= 1;
            }
            insert(root, 1, 1);
        }
        res.clear();
        visit(root, 1, 1);
        sort(res.begin(), res.end());
        REP(i,res.size())
            cout << res[i] << ' ';
        cout << "\n";
    }
    return 0;
}
