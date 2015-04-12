
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

int m, n, rows[111], cols[111], x[111];
char a[111][111];
vector<int> ls[111];
unordered_map<int, int> tr;

void init() {
    memset(rows, 0, sizeof rows);
    memset(cols, 0, sizeof cols);
    tr.clear();

    FOR(i,0,3) ls[i].clear();
    REP(mask,1<<5) {
        FOR(i,1,5) x[i] = (mask >> (i-1)) & 1;
        int cnt = 0;
        FOR(i,1,5) if (x[i-1] == 0 && x[i] == 1) ++cnt;

        ls[cnt].push_back(mask);
    }
//    FOR(i,0,3) {
//        PR0(ls[i], ls[i].size());
//    }
}

const int w[] = {1, 11, 11*11, 11*11*11, 11*11*11*11, 11*11*11*11*11, 11*11*11*11*11*21};
struct State {
    int c[6];
    int last;
    int j;

    int encode() {
        return c[1] * w[0]
            + c[2] * w[1]
            + c[3] * w[2]
            + c[4] * w[3]
            + c[5] * w[4]
            + j * w[5]
            + last * w[6];
    }
    void decode(int x) {
        c[1] = x % w[1];
        c[2] = (x % w[2]) / w[1];
        c[3] = (x % w[3]) / w[2];
        c[4] = (x % w[4]) / w[3];
        c[5] = (x % w[5]) / w[4];
        j    = (x % w[6]) / w[5];
        last = x / w[6];
    }
};

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

void trace(int x) {
    if (x == 0) return ;
    State cur; cur.decode(x);

    int j = cur.j;
    FOR(i,1,5)
        a[i][j] = CONTAIN(cur.last, i-1) ? '*' : '.';

    int y = tr[x];
    trace(y);
}
int get(int u) { return (u>>1) + (u&1); }

int main() {
    while (cin >> m >> n) {
        init();
        FOR(i,1,m) cin >> rows[i];
        FOR(j,1,n) cin >> cols[j];

        int savem = m;
        m = 5;
        State start;
        memset(start.c, 0, sizeof start.c);
        start.last = start.j = 0;
        int x = start.encode();
        tr[x] = x;
        queue<int> qu;
        qu.push(x);

        int maxj = 0;
        while (!qu.empty()) {
            int x = qu.front(); qu.pop();
            State cur; cur.decode(x);
            if (cur.j == n) continue;
            int j = cur.j + 1;

            for(auto next : ls[ cols[j] ]) {
                State v = cur;
                REP(i,5)
                    if (!CONTAIN(cur.last,i) && CONTAIN(next,i)) {
                        ++v.c[i+1];
                    }
                v.last = next;
                v.j = j;

                bool ok = true;
                FOR(i,1,5)
                    if (v.c[i] > rows[i] || v.c[i] + get(n - j) < rows[i]) {
                        ok = false;
                        break;
                    }
                if (!ok) continue;

                int y = v.encode();
                if (!tr.count(y)) {
                    tr[y] = x;
                    qu.push(y);
                }
            }
        }

        State cur;
        cur.j = n;
        FOR(i,1,5) cur.c[i] = rows[i];
        REP(mask,TWO(5)) {
            cur.last = mask;
            int x = cur.encode();

            if (tr.count(x)) {
                trace(x);
                break;
            }
        }

        FOR(i,1,savem) {
            FOR(j,1,n) cout << a[i][j];
            cout << endl;
        }
    }
    return 0;
}
