
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 10111000;
string a[777];

struct Node {
    int x;
    Node* next;
	int visited;
} *nil;

struct List {
    Node* first;
    Node* last;

    List() { first = last = nil; }
    void add(int x) {
        Node* p = new Node;
        p->x = x; p->next = nil; p->visited = -1;

        if (first == nil) first = last = p;
        else last->next = p, last = p;
    }
};

int qu[MN], suffixLink[MN];
List leaf[MN];
int link[MN][2];

struct Aho {
    int sz;
    void init() {
        sz = 0;
        memset(suffixLink, 0, sizeof suffixLink);
        leaf[0] = List();
        memset(link[0], -1, sizeof link[0]);
    }
    int getChild(int type, int v, int c) {
        while (1) {
            if (link[v][c] >= 0) return link[v][c];
            if (type == 1) return 0;
            if (!v) return 0;
            v = suffixLink[v];
        }
    }
    void buildLink() {
        int first, last;
        qu[first = last = 1] = 0;
        while (first <= last) {
            int u = qu[first++];
            REP(c,2) {
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
} aho;
char tmp[MN];
int n;

const int inf = 1000111;
struct Matching {
    int n;
    vector<int> matchL, matchR, dist;
    vector<bool> seen;
    vector< vector<int> > ke;

    Matching(int n) : n(n), matchL(n+1), matchR(n+1), dist(n+1), seen(n+1, false), ke(n+1) {}

    void addEdge(int u, int v) {
        ke[u].push_back(v);
    }

    bool bfs() {
        queue<int> qu;
        for(int u = 1; u <= n; ++u)
            if (!matchL[u]) {
                dist[u] = 0;
                qu.push(u);
            } else dist[u] = inf;
        dist[0] = inf;

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v) {
                if (dist[matchR[*v]] == inf) {
                    dist[matchR[*v]] = dist[u] + 1;
                    qu.push(matchR[*v]);
                }
            }
        }
        return dist[0] != inf;
    }

    bool dfs(int u) {
        if (u) {
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v)
                if (dist[matchR[*v]] == dist[u] + 1 && dfs(matchR[*v])) {
                    matchL[u] = *v;
                    matchR[*v] = u;
                    return true;
                }
            dist[u] = inf;
            return false;
        }
        return true;
    }

    int match() {
        int res = 0;
        while (bfs()) {
            for(int u = 1; u <= n; ++u)
                if (!matchL[u])
                    if (dfs(u)) ++res;
        }
        return res;
    }
};

bool ke[777][777];
bool chosen[777];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) {
            assert(scanf("%s\n", &tmp[0]));
            a[i] = string(tmp);
        }
//        PR(a, n);
        aho.init();
        FOR(i,1,n) {
            int p = 0;
            for(char c : a[i]) {
                int x = c - 'a';
                int t = aho.getChild(1, p, x);
                if (t > 0) p = t;
                else {
                    ++aho.sz;
                    leaf[aho.sz] = List();
                    memset(link[aho.sz], -1, sizeof link[aho.sz]);
                    link[p][x] = aho.sz;
                    p = aho.sz;
                }
            }
            leaf[p].add(i);
        }
        aho.buildLink();
//        DEBUG(aho.sz);

		memset(ke, 0, sizeof ke);
        FOR(i,1,n) {
            int p = 0;
            for(char c : a[i]) {
                int x = c - 'a';
                p = aho.getChild(2, p, x);
                
                Node* cur = leaf[p].first;
                while (cur != nil) {
					if (cur->visited == i) break;
					cur->visited = i;
					if (cur->x != i) {
						ke[i][cur->x] = true;
					}
                    cur = cur->next;
                }
            }
        }
		Matching mat(n);
		FOR(i,1,n) FOR(j,1,n)
			if (ke[i][j]) {
				mat.addEdge(i, j);
//				cout << i << ' ' << j << endl;
			}
		int k = n - mat.match();

		set<int> left, right;
		FOR(i,1,n) left.insert(i);
		FOR(i,1,n) right.insert(i);
		FOR(i,1,n) if (mat.matchL[i]) {
			if (mat.dist[i] < inf) {
				FOR(j,1,n) if (ke[i][j]) right.erase(j);
			}
			else left.erase(i);
		}

		cout << k << '\n';
		FOR(i,1,n) chosen[i] = true;
		for(auto x : left) chosen[x] = !chosen[x];
		for(auto x : right) chosen[x] = !chosen[x];
		FOR(i,1,n) if (chosen[i]) cout << i << ' '; cout << endl;
    }
}

