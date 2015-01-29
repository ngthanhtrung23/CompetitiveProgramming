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

const int MN = 100111;
#define next _next

map<string,int> id;
pair<string,string> edges[MN];
string family[MN];
int next[MN], in[MN], save_in[MN], f[MN];
int n;
bool visited[MN];

void init() {
    id.clear();
    memset(in, 0, sizeof in);
    memset(next, 0, sizeof next);
    memset(f, 0, sizeof f);
    memset(visited, false, sizeof visited);
}

void get(int u) {
    if (f[u]) return ;

    int v = next[u];
    if (v) {
        get(v);
        f[u] = f[v] + 1;
    }
    else f[u] = 1;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        init();

        string t;
        FOR(i,1,n) {
            cin >> family[i] >> edges[i].first >> t >> t >> edges[i].second;
            id[edges[i].first] = i;
        }
        FOR(i,1,n) {
            int u = id[edges[i].first], v = id[edges[i].second];

            if (family[u] != family[v]) continue;

//            cout << u << ' ' << v << endl;
            next[u] = v;
            in[v]++;
        }
        FOR(i,1,n) save_in[i] = in[i];

        memset(visited, false, sizeof visited);
        FOR(i,1,n) if (!in[i] && !visited[i]) {
            int u = i;
            while (in[u] == 0) {
                visited[u] = true;
                int v = next[u];
                --in[v];

                u = v;
            }
        }
//        PR(visited, n);

        FOR(i,1,n) if (!visited[i]) {
            int cycleLen = 0;
            int u = i;
            stack<int> st;
            while (!visited[u]) {
                st.push(u);
                visited[u] = true;
                int v = next[u];
                u = v;

                ++cycleLen;
            }

            while (!st.empty()) {
                int u = st.top(); st.pop();
                f[u] = cycleLen;
            }
        }
//        PR(f, n);

        FOR(i,1,n) if (save_in[i] == 0) {
            get(i);
        }

        cout << *max_element(f+1, f+n+1) << endl;
    }
    return 0;
}
