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
    Node *to[30];
    bool has;
} *root;
int nWord;

struct Hash {
    long long x, y;
    Hash(long long x = 0, long long y = 0) : x(x), y(y) {}

    Hash operator + (Hash a) { return Hash(x+a.x, y+a.y); }
    Hash operator * (Hash a) { return Hash(x*a.x, y*a.y); }
};
bool operator < (const Hash &a, const Hash &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
Hash p(31, 1000003);

set< Hash > all;

void insert(Node* &p, string &s, int pos) {
    if (p == NULL) {
        p = new Node;
        REP(i,30) p->to[i] = NULL;
        p->has = false;
    }
    if (pos < s.length())
        insert(p->to[s[pos]-'a'], s, pos+1);
    else p->has = true;
}

Hash visit(Node *root) {
    if (root == NULL) return Hash(0, 0);

    Hash cur = Hash(1, 1);
    if (root->has) cur = Hash(1000000007, 1000000009);
    
    Hash pp = Hash(1, 1);
    REP(i,30) {
        pp = pp * p;
        cur = cur + pp * visit(root->to[i]);
    }
    all.insert(cur);
    return cur;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("language.in", "r", stdin);
    freopen("language.out", "w", stdout);
    while (cin >> nWord) {
        root = NULL;
        FOR(i,1,nWord) {
            string s; cin >> s;
            insert(root, s, 0);
        }
        all.clear();
        visit(root);
        cout << all.size() << endl;
    }
    return 0;
}
