
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int test;
int n, need[22], f[TWO(18)], value[22];
char tmp[1011];
string name[22];
map<string,int> id;

int main() {
    ios :: sync_with_stdio(false);
    int test; scanf("%d", &test);
    while (test--) {
        id.clear();
        int w; scanf("%d%d\n", &n, &w);
        REP(i,n) {
            gets(tmp);
            bool good = false;
            FORD(x,strlen(tmp)-1,0) {
                if (tmp[x] == ' ') {
                    if (!good) good = true;
                    else tmp[x] = '-';
                }
                stringstream ss(tmp);
                ss >> name[i];
                id[name[i]] = i;
                ss >> value[i];
            }
        }
//        PR0(name, n);
//        PR0(value, n);
        memset(need, 0, sizeof need);

        while (w--) {
            gets(tmp);
            stringstream ss(tmp);

            string name1 = "", name2 = "";
            int turn = 0;
            string s;
            while (ss >> s) {
                if (s == "-->") ++turn;
                else if (turn == 0) {
                    if (name1 == "") name1 = s;
                    else name1 = name1 + "-" + s;
                }
                else {
                    if (name2 == "") name2 = s;
                    else name2 = name2 + "-" + s;
                }
            }

            int u = id[name1], v = id[name2];
            need[v] |= TWO(u);
        }
//        PR0(need, n);

        memset(f, -1, sizeof f);
        f[0] = 0;
        REP(mask,TWO(n)-1) if (f[mask] >= 0) {
            int cur = __builtin_popcount(mask) + 1;
            REP(u,n) if (!CONTAIN(mask,u))
                if ((mask | need[u]) == mask) {
                    int next = mask | TWO(u);
                    f[next] = max(f[next], f[mask] + cur * value[u]);
                }
        }
        cout << f[TWO(n)-1] << endl;
    }
    return 0;
}
