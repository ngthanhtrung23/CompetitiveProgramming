
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

const int MN = 12000111;

char s[MN];
int match[MN], nextQuote[MN], id[MN], cur;
vector< pair<string,int> > a[10111];

void parse(int l, int r) {
    if (s[l] != '{') return ;

    id[l] = ++cur;

    int i = l + 1;
    while (i < r) {
        assert(s[i] == '"');

        string t = "";
        int j = nextQuote[i+1];
        FOR(x,i+1,j-1) t += s[x];

        a[id[l]].push_back(make_pair(t, j+2));

        if (s[j+2] == '{') {
            parse(j+2, match[j+2]);
            i = match[j+2];
        }
        else i = nextQuote[j+3];
        ++i;
        if (s[i] == ',') ++i;
    }
}

char tmp[MN];

int main() {
    ios :: sync_with_stdio(false);
    int ntest; scanf("%d\n", &ntest);
    while (ntest--) {
        gets(s);
        stack<int> st;
        int l = strlen(s);

        nextQuote[l] = l;
        FORD(i,l-1,0) {
            if (s[i] == '"') nextQuote[i] = i;
            else nextQuote[i] = nextQuote[i+1];
        }

        REP(i,l) {
            if (s[i] == '{') {
                st.push(i);
            }
            else if (s[i] == '}') {
                int j = st.top(); st.pop();
                match[i] = j;
                match[j] = i;
            }
        }

        cur = 0;
        parse(0, l-1);

        int q; scanf("%d\n", &q);
        while (q--) {
            gets(tmp);
            REP(i,strlen(tmp)) if (tmp[i] == '.') tmp[i] = ' ';
            istringstream ss(tmp);

            int u = 0, v = l-1;
            try {
                string t;
                while (ss >> t) {
                    t = t.substr(1, t.length() - 2);
                    if (s[u] != '{') throw 1;

                    auto it = lower_bound(a[id[u]].begin(), a[id[u]].end(), make_pair(t, 0));
                    if (it == a[id[u]].end()) throw 1;
                    if (it->first != t) throw 1;

                    u = it->second;
                    if (s[u] == '{') v = match[u];
                    else v = nextQuote[u+1];
                }
                FOR(i,u,v) putchar(s[i]); puts("");
            }
            catch (...) {
                puts("Error!");
            }
        }

        REP(i,l) {
            if (s[i] == '{') {
                a[id[i]].clear();
            }
        }
    }
}

