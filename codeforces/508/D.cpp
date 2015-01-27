#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

struct Edge;
typedef list<Edge>::iterator iter;

struct Edge
{
    int next_vertex;

    Edge(int next_vertex)
        :next_vertex(next_vertex)
        { }
};

int num_vertices;
list<Edge> adj[4011];        // adjacency list

vector<int> path;

void find_path(int v) {
    while(adj[v].size() > 0) {
        int vn = adj[v].front().next_vertex;
        adj[v].pop_front();
        find_path(vn);
    }
    path.push_back(v);
}

void add_edge(int a, int b) {
    adj[a].push_front(Edge(b));
    iter ita = adj[a].begin();
}

int encode(char a) {
    if (a >= 'a' && a <= 'z') return a - 'a';
    if (a >= 'A' && a <= 'Z') return a - 'A' + 26;
    if (a >= '0' && a <= '9') return a - '0' + 52;
}
int encode(char a, char b) {
    return encode(a) * 62 + encode(b);
}

char decode1(int u) {
    if (u < 26) return 'a' + u;
    else if (u < 52) return 'A' + (u - 26);
    return '0' + (u - 52);
}

pair<char,char> decode(int u) {
    return make_pair(decode1(u / 62), decode1(u % 62));
}

int m, n;
string s[200111];
int in[10111], out[10111];
bool visited[4011];
int res[200111];

bool bfs(int start) {
    queue<int> qu;
    qu.push(start);
    memset(visited, 0, sizeof visited);
    visited[start] = 1;

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();

        REP(v,n) if (!visited[v]) {
            visited[v] = true;
            qu.push(v);
        }
    }

    REP(i,n)
        if (in[i] || out[i])
            if (!visited[i]) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> m) {
        FOR(i,1,m) cin >> s[i];

        n = encode('9', '9') + 1;
//        DEBUG(n);

        memset(in, 0, sizeof in);
        memset(out, 0, sizeof out);

        FOR(i,1,m) {
            int u = encode(s[i][0], s[i][1]);
            int v = encode(s[i][1], s[i][2]);

            out[u] += 1;
            in[v] += 1;
//            cout << u << ' ' << v << endl;
            add_edge(u, v);
        }

//        cout << "DONE BUILD GRAPH" << endl;

        int start = -1, target = -1;
        bool bad = false;

        REP(i,n) {
            if (out[i] == in[i]) {
            }
            else if (out[i] == in[i] + 1) {
                if (start == -1) start = i;
                else bad = true;
            }
            else if (out[i] == in[i] - 1) {
                if (target == -1) target = i;
                else bad = true;
            }
            else {
                bad = true;
            }
        }
        if (bad) {
            cout << "NO" << endl;
            continue;
        }

        if (start < 0) {
            REP(i,n)
                if (in[i] || out[i]) {
                    start = target = i;
                    break;
                }
        }

        if (start < 0 || target < 0 || !bfs(start)) {
            cout << "NO" << endl;
            continue;
        }

        path.clear();
        find_path(start);
//        DEBUG(path.size());

        if (path.size() != m + 1) {
            cout << "NO" << endl;
            continue;
        }

        cout << "YES" << endl;
        reverse(path.begin(), path.end());
        REP(i,path.size()) {
//            cout << path[i] << endl;
            pair<char,char> cur = decode(path[i]);
            if (i == 0) cout << cur.first;
            cout << cur.second;
        }
        cout << endl;
    }
    return 0;
}
