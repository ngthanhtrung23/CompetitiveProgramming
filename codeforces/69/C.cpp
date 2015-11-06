
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

map<string,int> id;
string name[111];

int getId(string s) {
    if (!id.count(s)) {
        int cur = SZ(id);
        id[s] = cur + 1;

        name[cur + 1] = s;
    }
    return id[s];
}

map<int, int> art[111];
vector< pair<int,int> > need[55];
char tmp[1000111];

bool canComp(int ally, int comp) {
    REP(j,SZ(need[comp])) {
        pair<int,int> p = need[comp][j];
        if (art[ally][p.first] < p.second) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    int nAlly, nBasic, nComp, nPurchase;
    while (scanf("%d%d%d%d\n", &nAlly, &nBasic, &nComp, &nPurchase) == 4) {
        FOR(i,1,nAlly) art[i].clear();
        id.clear();
        FOR(i,1,nComp) need[i].clear();

        FOR(i,1,nBasic) {
            gets(tmp); string s(tmp);
            int u = getId(s);
        }
        FOR(i,1,nComp) {
            gets(tmp);
            REP(i,strlen(tmp))
                if (tmp[i] == ':' || tmp[i] == ',')
                    tmp[i] = ' ';
            stringstream ss(tmp);

            string cur; ss >> cur;
            int u = getId(cur);
            string t;
            int cnt;
            while (ss >> t >> cnt) {
                need[i].push_back(make_pair(getId(t), cnt));
            }
        }
        FOR(i,1,nPurchase) {
            int u;
            scanf("%d %s\n", &u, &tmp[0]);
            string s(tmp);
            int v = getId(s);
            art[u][v] += 1;

            FOR(j,1,nComp)
                if (canComp(u, j)) {
                    for(auto p : need[j]) {
                        art[u][p.first] -= p.second;
                    }
                    art[u][j + nBasic] += 1;
                    break;
                }
        }
        FOR(i,1,nAlly) {
            int cnt = 0;
            for(auto p : art[i])
                if (p.second > 0)
                    ++cnt;
            cout << cnt << '\n';
            vector< pair<string,int> > res;
            for(auto p : art[i])
                if (p.second > 0) {
                    res.push_back(make_pair(name[p.first], p.second));
                }
            sort(res.begin(), res.end());
            for(auto p : res) cout << p.first << ' ' << p.second << '\n';
        }
    }
}

