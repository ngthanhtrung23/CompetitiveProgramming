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

int has[300], need[300];
int value[300];

struct Board {
    int m, n;
    int letter[22][22];
    int word[22][22];

    char a[22][22];

    void read() {
        cin >> m >> n;
        int nGift; cin >> nGift;
        FOR(i,1,m) FOR(j,1,n) {
            letter[i][j] = word[i][j] = 1;
        }
        while (nGift--) {
            char typ; cin >> typ;
            int mult; cin >> mult;

            int k; cin >> k;
            while (k--) {
                int u, v; cin >> u >> v;
                if (typ == 'L') {
                    letter[u][v] = mult;
                }
                else {
                    word[u][v] = mult;
                }
            }
        }
    }

    void readInit() {
        memset(a, '.', sizeof a);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
    }

    int canPut(string cur) {
        // hor
        int len = cur.length();
        int best = 0;
        FOR(i,1,m) {
            FOR(j,1,n-len+1) {
                // init
                FOR(c,'A','Z') need[c] = 0;

                // first, see which characters are missing
                bool ok = true;
                int res = 0;
                int mult = 1;
                bool atleast = false, atleast2 = false;
                REP(x,len) {
                    if (a[i][j+x] == '.') {
                        atleast2 = true;
                        ++need[cur[x]];
                        if (need[cur[x]] > has[cur[x]]) ok = false;

                        if (a[i-1][j+x] != '.') ok = false;
                        if (a[i+1][j+x] != '.') ok = false;
                    }
                    else {
                        if (a[i][j+x] != cur[x]) ok = false;
                        atleast = true;
                    }

                    res += value[ cur[x] ] * letter[i][j+x];
                    mult = mult * word[i][j+x];
                }
                res *= mult;
                ok = ok && atleast && atleast2;

                if (a[i][j-1] != '.') ok = false;
                if (a[i][j+len] != '.') ok = false;

                if (ok) {
                    best = max(best, res);
                }
            }
        }
        // ver
        FOR(j,1,n) {
            FOR(i,1,m-len+1) {
                // init
                FOR(c,'A','Z') need[c] = 0;

                // first, see which characters are missing
                bool ok = true;
                int res = 0;
                int mult = 1;
                bool atleast = false, atleast2 = false;
                REP(x,len) {
                    if (a[i+x][j] == '.') {
                        atleast2 = true;
                        ++need[cur[x]];
                        if (need[cur[x]] > has[cur[x]]) ok = false;

                        if (a[i+x][j-1] != '.') ok = false;
                        if (a[i+x][j+1] != '.') ok = false;
                    }
                    else {
                        if (a[i+x][j] != cur[x]) ok = false;
                        atleast = true;
                    }

                    res += value[ cur[x] ] * letter[i+x][j];
                    mult = mult * word[i+x][j];
                }
                res *= mult;
                ok = ok && atleast && atleast2;

                if (a[i-1][j] != '.') ok = false;
                if (a[i+len][j] != '.') ok = false;

                if (ok) {
                    best = max(best, res);
                }
            }
        }
        return best;
    }

} board;

int main() {
    ios :: sync_with_stdio(false);
    freopen("words.in", "r", stdin);
    freopen("words.out", "w", stdout);
    board.read();
    int k; cin >> k;
    while (k--) {
        string s; cin >> s;
        int cost; cin >> cost;
        for(char c : s) value[c] = cost;
    }
//    FOR(c,'A','Z') cout << value[c] << ' '; cout << endl;

    board.readInit();

    cin >> k; string s; cin >> s;
    for(char c : s) ++has[c];

    cin >> k;
    int res = 0;
    while (k--) {
        string cur; cin >> cur;
        res = max(res, board.canPut(cur));
    }
    cout << res << endl;
}