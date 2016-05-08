
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

map<string,int> id;
vector<int> ke[333];
int f[333];
string a[333], b[333], c[333];

int getId(string s) {
    if (id.find(s) != id.end()) return id[s];

    int nid = SZ(id) + 1;
    return id[s] = nid;
}

void add(int u, int v) {
    ke[u].push_back(v);
    ke[v].push_back(u);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        id.clear();
        FOR(i,1,300) ke[i].clear();

        int k; cin >> k;
        FOR(i,1,k) {
            cin >> a[i] >> b[i] >> c[i];
            int u = getId(a[i]);
            int v = getId(b[i]);
            int w = getId(c[i]);

            add(u, v);
            add(u, w);
            add(v, w);
        }

        memset(f, -1, sizeof f);
        queue<int> qu;
        int start = getId("Ahmad");
        f[start] = 0;
        qu.push(start);

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(int v : ke[u]) {
                if (f[v] < 0) {
                    f[v] = f[u] + 1;
                    qu.push(v);
                }
            }
        }
        vector< pair<int,string> > all;
        for(auto p : id) {
            auto s = p.first;
            all.emplace_back(f[getId(s)], s);
        }
        sort(all.begin(), all.end());
        cout << SZ(all) << endl;
        for(auto p : all) if (p.first >= 0) {
            cout << p.second << ' ';
            if (p.first < 0) cout << "undefined";
            else cout << p.first;
            cout << endl;
        }
        for(auto p : all) if (p.first < 0) {
            cout << p.second << ' ';
            if (p.first < 0) cout << "undefined";
            else cout << p.first;
            cout << endl;
        }
    }
}
