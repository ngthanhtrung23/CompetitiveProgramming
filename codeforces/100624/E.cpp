
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

const int MN = 2011;

int n;
unordered_map<string, int> id;

bool isAdd[MN];
string value[MN], symbol[MN];
pair<string,string> eq[MN];
pair<int,int> child[MN];

char tmp[100111], t[MN];
int f[MN][MN], lt;

void init() {
    id.clear();
    memset(f, -1, sizeof f);
}

// symbol u, at position start in string t
// f[u][t] = index of first position that can not match
int get(int u, int start) {
    if (start == lt) return lt;
    if (f[u][start] >= 0) return f[u][start];

    if (isAdd[u]) {
        int x = child[u].first;
        int y = child[u].second;

        f[u][start] = get(y, get(x, start));
    }
    else {
        int res = start;
        for(char c : value[u]) {
            if (res < lt && c == t[res])
                ++res;
        }
        f[u][start] = res;
    }

//    DEBUG(u);
//    cout << symbol[u] << ' ' << start << ' ' << f[u][start] << endl;

    return f[u][start];
}

int main() {
    int ntest; scanf("%d\n", &ntest);
    while (ntest--) {
        scanf("%d\n", &n);
        init();

        int cnt = 0;
        FOR(i,1,n) {
            gets(tmp);
            isAdd[i] = false;
            REP(j,strlen(tmp)) {
                if (tmp[j] == '=') tmp[j] = ' ';
                if (tmp[j] == '+') {
                    tmp[j] = ' ';
                    isAdd[i] = true;
                }
            }
            if (isAdd[i]) {
                string a, b, c;
                istringstream ss(tmp);
                ss >> a >> b >> c;
                symbol[i] = a;
                eq[i] = make_pair(b, c);
            }
            else {
                string a, b;
                istringstream ss(tmp);
                ss >> a >> b;
                symbol[i] = a;
                value[i] = b;
            }
            id[symbol[i]] = ++cnt;
        }
        FOR(i,1,n) {
//            DEBUG(symbol[i]);
            if (isAdd[i]) {
//                cout << eq[i].first << ' ' << eq[i].second << endl;
//                if (id.count(eq[i].first)) DEBUG(id[eq[i].first]);
//                if (id.count(eq[i].second)) DEBUG(id[eq[i].second]);

                child[i].first = id[eq[i].first];
                child[i].second = id[eq[i].second];
            }
            else {
//                DEBUG(value[i]);
            }
        }
        gets(tmp);
        string start(tmp);
        gets(t);
        lt = strlen(t);

        int res = get(id[start], 0);
        if (res >= lt) puts("YES");
        else puts("NO");
    }
    return 0;
}
