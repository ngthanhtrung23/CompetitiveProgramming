
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

int nPeople, d;

struct Person {
    string name;
    int k;
    vector<string> children;
} people[1011];

vector<int> ke[1011];
int f[1011];

int dfs(int u, int cur, int need) {
    if (cur+1 == need) return ke[u].size();
    if (cur == need) return 1;
    
    int res = 0;
    for(int v : ke[u]) {
        res += dfs(v, cur+1, need);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> nPeople >> d;
        map<string,int> id;

        FOR(i,1,nPeople) {
            ke[i].clear();
            people[i].children.clear();

            cin >> people[i].name >> people[i].k;
            id[people[i].name] = i;

            REP(turn,people[i].k) {
                string s; cin >> s;
                people[i].children.push_back(s);
            }
        }

        FOR(i,1,nPeople) {
            int u = id[people[i].name];
            for(auto s : people[i].children) {
                int v;
                if (id.count(s)) v = id[s];
                else v = 0;

                ke[u].push_back(v);
            }
        }

        FOR(i,1,nPeople) {
            f[i] = dfs(i, 0, d);
        }
        vector< pair<int, string> > res;
        FOR(i,1,nPeople) if (f[i]) {
            res.push_back(make_pair(-f[i], people[i].name));
        }
        sort(res.begin(), res.end());

        int cnt = 0, last = 0;
        cout << "Tree " << test << ":\n";
        for(auto p : res) {
            if (cnt < 3 || p.first == last) {
                cout << p.second << ' ' << -p.first << '\n';
                last = p.first;
                ++cnt;
            }
            else break;
        }
        cout << '\n';
    }
    return 0;
}

