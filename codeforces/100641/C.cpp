
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

int a[11][11];
pair< char, pair<int,int> > dominos[22];
bool used[11][11];
bool isFirst;

void init() {
    memset(a, 0, sizeof a);
    memset(used, 0, sizeof used);
    isFirst = true;
}

void move(int& i, int& j) {
    while (a[i][j]) {
        ++j;
        if (j == 6) {
            j = 1;
            ++i;
        }
    }
}

int has[11];
int get(int a, int b, int c, int d, int e) {
    int x[5] = {a, b, c, d, e};
    memset(has, 0, sizeof has);
    sort(x, x+5);
    // all same
    if (x[0] == x[4]) {
        if (isFirst) {
            isFirst = false;
            return 50;
        }
        else return 100;
    }
    // 5 consecutive values
    if (x[0] + 1 == x[1]
            && x[1] + 1 == x[2]
            && x[2] + 1 == x[3]
            && x[3] + 1 == x[4])
        return 40;

    REP(i,5) has[x[i]]++;

    // 4 consecutive values
    if (has[1] && has[2] && has[3] && has[4]) return 30;
    if (has[2] && has[3] && has[4] && has[5]) return 30;
    if (has[3] && has[4] && has[5] && has[6]) return 30;

    // 3 of a kind and a pair
    FOR(i,1,6) FOR(j,1,6)
        if (i != j && has[i] >= 3 && has[j] >= 2)
            return 25;

    // 4 of a kind
    FOR(i,1,6) if (has[i] >= 4) return 4 * i;
    
    // 3 of a kind
    FOR(i,1,6) if (has[i] >= 3) return 3 * i;

    return 0;
}

int getScore() {
    int res = 0;
    isFirst = true;
    FOR(i,1,5) {
        res += get(a[i][1], a[i][2], a[i][3], a[i][4], a[i][5]);
        res += get(a[1][i], a[2][i], a[3][i], a[4][i], a[5][i]);
    }
    res += get(a[1][1], a[2][2], a[3][3], a[4][4], a[5][5]);
    res += get(a[1][5], a[2][4], a[3][3], a[4][2], a[5][1]);
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        init();
        int i = 1, j = 1;
        int nDomino = 0;
        FOR(turn,1,13) {
            char typ; cin >> typ;
            if (typ == 'S') {
                move(i, j);
                int u; cin >> u; a[i][j] = u;
            }
            else if (typ == 'V') {
                move(i, j);
                dominos[++nDomino] = make_pair(typ, make_pair(i, j));
                int u; cin >> u; a[i][j] = u;
                int v; cin >> v; a[i+1][j] = v;
                used[u][v] = used[v][u] = true;
            }
            else if (typ == 'H') {
                move(i, j);
                dominos[++nDomino] = make_pair(typ, make_pair(i, j));
                int u; cin >> u; a[i][j] = u;
                int v; cin >> v; a[i][j+1] = v;
                used[u][v] = used[v][u] = true;
            }
        }
//        FOR(i,1,5) {
//            PR(a[i], 5);
//        }
        int res = getScore();

        FOR(d,1,nDomino) {
            int i = dominos[d].second.first;
            int j = dominos[d].second.second;
            // we try to replace the d-th domino
            FOR(x,1,6) FOR(y,1,6) if (!used[x][y]) {
                // with the domino (x, y)
                int save1, save2;
                if (dominos[d].first == 'V') {
                    save1 = a[i][j];   a[i][j] = x;
                    save2 = a[i+1][j]; a[i+1][j] = y;
                }
                else {
                    save1 = a[i][j];   a[i][j] = x;
                    save2 = a[i][j+1]; a[i][j+1] = y;
                }

                res = max(res, getScore());

                if (dominos[d].first == 'V') {
                    a[i][j] = save1;
                    a[i+1][j] = save2;
                }
                else {
                    a[i][j] = save1;
                    a[i][j+1] = save2;
                }
            }
        }

        cout << "Case " << test << ": " << res << '\n';
    }
    return 0;
}
