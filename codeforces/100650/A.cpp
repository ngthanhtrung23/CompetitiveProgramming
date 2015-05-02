
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

int nBad;
char tmp[100111];
vector<string> words;
string need;

int f[211][211];
int g[211][211];

void solve() {
//    DEBUG(need);
//    for(auto s : words) cout << s << ' ';
//    cout << endl;

    memset(f, 0, sizeof f);
    f[0][0] = 1;

    FOR(i,0,words.size()-1) FOR(j,0,need.size()-1) if (f[i][j]) {
        // now we use the (i+1)th word

        int l = words[i].length();
        int maxk = min((int) need.size()-j, l);
        FOR(x,0,l) FOR(y,0,l) g[x][y] = 0;

        FOR(x,0,l) FOR(y,0,maxk) {
            if (x == 0 && y == 0) {
                g[x][y] = 1;
            }
            else if (x == 0) {
                g[x][y] = 0;
            }
            else {
                g[x][y] = g[x-1][y];
                if (y > 0 && words[i][x-1] == need[j+y-1])
                    g[x][y] += g[x-1][y-1];
            }
        }

        // if we use k character --> g[l][k]
        FOR(k,1,l)
            if (g[l][k])
                f[i+1][j+k] += f[i][j] * g[l][k];
    }

    int res = f[words.size()][need.size()];
    if (!res) {
        printf("%s is not a valid abbreviation\n", need.c_str());
    }
    else {
        printf("%s can be formed in %d ways\n", need.c_str(), res);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d\n", &nBad) == 1 && nBad) {
        set<string> bad;
        FOR(i,1,nBad) {
            gets(tmp);
            REP(i,strlen(tmp))
                if (tmp[i] >= 'a' && tmp[i] <= 'z')
                    tmp[i] ^= ' ';
            bad.insert(string(tmp));
        }
        while (true) {
            gets(tmp);
            REP(i,strlen(tmp))
                if (tmp[i] >= 'a' && tmp[i] <= 'z')
                    tmp[i] ^= ' ';

            string s (tmp);
            if (s == "LAST CASE") break;


            stringstream ss(s);
            string t;

            words.clear();
            ss >> need;
            while (ss >> t) {
                if (bad.count(t)) continue;
                words.push_back(t);
            }

            solve();
        }
    }
    return 0;
}
