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

string a[111];
int n, vao[111];
vector<int> ke[111];

bool ok;

void init() {
    FOR(i,0,36) {
        ke[i].clear();
    }
    memset(vao, 0, sizeof vao);
}

void addEdge(int u, int v) {
    u -= 'a' - 1; v -= 'a' - 1;
    vao[v] += 1;
    ke[u].push_back(v);
}

void update(string a, string b) {
    if (b.find(a) == 0) { // a is prefix of b
        return ;
    }
    else if (a.find(b) == 0) {
        ok = false;
        return ;
    }

    int equal = 0;
    while (a[equal] == b[equal]) ++equal;
    addEdge(a[equal], b[equal]);
}

bool used[311];
int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        init();

        FOR(i,1,n) cin >> a[i];
        ok = true;
        FOR(i,2,n) {
            update(a[i-1], a[i]);
        }
        if (!ok) {
            cout << "Impossible" << endl;
            continue;
        }

        vector<char> res;
        queue<int> qu;
        FOR(i,1,26) if (vao[i] == 0) {
            qu.push(i);
        }

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            res.push_back((char) (u - 1 + 'a'));
            for(int v : ke[u]) {
                vao[v]--;
                if (vao[v] == 0) qu.push(v);
            }
        }

        if (res.size() < 26) cout << "Impossible" << endl;
        else {
            for(char c : res)
                cout << c;
            cout << endl;
        }
    }
    return 0;
}
