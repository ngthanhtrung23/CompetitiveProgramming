#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

string a, b;
set<string> all[2];

void gen(int t, string s) {
    all[t].clear();
    queue< pair<string,int> > qu;
    qu.push(make_pair(s, 0));

    int l = s.length();
    while (!qu.empty()) {
        string u = qu.front().first;
        int dist = qu.front().second;
        qu.pop();
        
        if (dist == 2) continue;

        REP(i,l) FOR(j,i,l-1) {
            string v = u;
            reverse(v.begin() + i, v.begin() + j + 1);

            if (!all[t].count(v)) {
                all[t].insert(v);
                qu.push(make_pair(v, dist+1));
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("dna.in", "r", stdin);
    freopen("dna.out","w", stdout);
    while (cin >> a >> b) {
        gen(0, a);
        gen(1, b);

        bool ok = false;
        EACH(s, all[0]) {
            if (all[1].count(*s)) {
                cout << "Similar" << endl;
                ok = true;
                break;
            }
        }
        if (!ok) cout << "Different" << endl;
    }
}
