#define _GLIBCXX_DEBUG
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
    Node *left, *right;
} *root;

#define TWO(x) (1LL<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;
const int MN = 100111;

int n;
long long a[MN];

Node *createNode() {
    Node *t = new Node;
    t->left = t->right = NULL;
    return t;
}

void insert(Node *root, long long value, long long bit) {
    if (bit == -1) return ;

    if (CONTAIN(value, bit)) {
        if (root->right == NULL)
            root->right = createNode();
        insert(root->right, value, bit - 1);
    }
    else {
        if (root->left == NULL)
            root->left = createNode();
        insert(root->left, value, bit - 1);
    }
}

long long get(Node *root, long long value, int bit) {
    if (bit == -1) return 0;

    Node *good, *bad;
    if (CONTAIN(value, bit)) {
        good = root->left;
        bad = root->right;
    }
    else {
        good = root->right;
        bad = root->left;
    }

    if (good) {
        return TWO(bit) + get(good, value, bit - 1);
    }
    else {
        return get(bad, value, bit - 1);
    }
}

void print(Node *root, string pref = "") {
    if (root->left) print(root->left, pref + "  ");
    cout << pref << "X\n";
    if (root->right) print(root->right, pref + "  ");
}

int main() {
    while (scanf("%d", &n) == 1) {
        root = createNode();
        long long sum = 0;
        FOR(i,1,n) {
            scanf("%I64d", &a[i]);
            sum ^= a[i];
        }

        long long res = sum, right = 0;
        insert(root, 0, 50);

        FORD(i,n-1,0) {
            sum ^= a[i+1];
            right ^= a[i+1];

            insert(root, right, 50);

            res = max(res, get(root, sum, 50));

            // DEBUG(sum);
            // DEBUG(right);
            // DEBUG(res);
            // print(root);
        }
        cout << res << endl;
    }
    return 0;
}
