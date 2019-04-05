/**
Problem:
- Given a trie
- Given N queries, each query is a string.
- For each query, count how many words in trie has that query as suffix.

Solution:
- Build AhoCorasick on reverse of queries.
- For each node of AhoCorasick, keep linked list of all queries associated with that node.
- DFS trie -> for each node of AhoCorasick, we know how many string in trie match it.
- For each node of AhoCorasick, loop through linked list to update results of queries.
*/
#include "bits/stdc++.h"
using namespace std;

#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
// On CF, GNU C++ seems to have some precision issues with long double?
// #define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define stat akjcjalsjcjalscj
#define hash ajkscjlsjclajsc
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (((S) >> (X)) & 1)

long long rand16() {
    return rand() & (TWO(16) - 1);
}
long long my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(long long& x) { return scanf("%lld", &x); }

const int MN = 1000111; // MN > total length of all patterns
int res[MN];

const int MC = 26;
struct Node {
    int x; Node *next;
} *nil;
int iter;
struct List {
    int f;
    Node *first, *last;
    List() { first = last = nil; }
    void add(int x) {
        Node *p = new Node;
        p->x = x; p->next = nil;
        if (first == nil) last = first = p;
        else last->next = p, last = p;
    }

    void print() {
        Node* p = first;
        while (p) {
            res[p->x] += f;
            p = p->next;
        }
    }
};

namespace Aho {
    int qu[MN], suffixLink[MN];
    List leaf[MN];
    int link[MN][MC];
    int sz;

    void init() {
        sz = 0;
        memset(suffixLink, 0, sizeof suffixLink);
        leaf[0] = List();
        memset(link[0], -1, sizeof link[0]);
    }
    int getChild(int type, int v, int c) {
        if (link[v][c] >= 0) return link[v][c];
        if (type == 1) return 0;
        if (!v) return link[v][c] = 0;
        return link[v][c] = getChild(type, suffixLink[v], c);
    }
    void buildLink() {
        int first, last;
        qu[first = last = 1] = 0;
        while (first <= last) {
            int u = qu[first++];
            REP(c,MC) {
                int v = link[u][c]; if (v < 0) continue;
                qu[++last] = v;
                if (u == 0) suffixLink[v] = 0;
                else suffixLink[v] = getChild(2, suffixLink[u], c);

                if (leaf[suffixLink[v]].first != nil) {
                    if (leaf[v].first == nil) {
                        leaf[v].first = leaf[suffixLink[v]].first;
                        leaf[v].last = leaf[suffixLink[v]].last;
                    }
                    else {
                        leaf[v].last->next = leaf[suffixLink[v]].first;
                        leaf[v].last = leaf[suffixLink[v]].last;
                    }
                }
            }
        }
    }
};

struct Trie {
    Trie* children[26];
};
Trie* createNode() {
    Trie* res = new Trie();
    memset(res->children, 0, sizeof res->children);
    return res;
}
Trie* trie[1000111];

void dfs(Trie* p, int ahoId) {
    Aho::leaf[ahoId].f++;

    REP(c,26) if (p->children[c]) {
        int to = Aho::getChild(2, ahoId, c);
        dfs(p->children[c], to);
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    Aho::init();
    Trie* root = createNode();
    int n, q;
    cin >> n >> q;
    trie[0] = root;

    FOR(i,1,n) {
        char c;
        int parent;
        cin >> c >> parent;

        trie[i] = createNode();
        trie[parent]->children[c - 'A'] = trie[i];
    }

    FOR(i,1,q) {
        int p = 0;
        string s; cin >> s;
        reverse(ALL(s));
        for (char c : s) {
            int x = c - 'A';
            int t = Aho::getChild(1, p, x);
            if (t > 0) p = t;
            else {
                ++Aho::sz;
                Aho::leaf[Aho::sz] = List();
                memset(Aho::link[Aho::sz], -1, sizeof Aho::link[Aho::sz]);

                Aho::link[p][x] = Aho::sz;
                p = Aho::sz;
            }
        }
        Aho::leaf[p].add(i);
    }
    Aho::buildLink();

    dfs(root, 0);

    FOR(i,0,Aho::sz) {
        Aho::leaf[i].print();
    }
    FOR(i,1,q) printf("%d\n", res[i]);
    return 0;
}

