#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

string a, b, ra;
bool has[333];
queue< int > qu;
set< long long > can;

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

bool hasSolution() {
    memset(has, false, sizeof has);
    REP(i,a.size()) has[a[i]] = true;

    REP(i,b.size()) if (!has[b[i]]) return false;
    return true;
}

int bitmask[22][22];
int d[TWO(19)];

long long codea[22], codeb[22], coder[22];

int getval(char c) {
    if (c == 'A') return 1;
    if (c == 'C') return 2;
    if (c == 'G') return 3;
    if (c == 'T') return 4;
    return -1;
}

long long p5[22];

long long getCode(long long code[], int i, int j) {
    if (i == 0) return code[j];
    else return (code[j] - code[i-1]) / p5[i];
}

long long nguocb[22][22], xuoib[22][22];
int nreg[TWO(18)];

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    p5[0] = 1;
    FOR(i,1,18) p5[i] = p5[i-1] * 5LL;

    REP(mask,TWO(18)) {
        nreg[mask] = 0;
        int i = 0;
        while (i < 18) {
            if (!CONTAIN(mask,i)) ++i;
            else {
                ++nreg[mask];
                while (CONTAIN(mask,i)) ++i;
            }
        }
    }

    FOR(i,0,20) {
        bitmask[i][i] = TWO(i);
        FOR(j,i+1,20)
            bitmask[i][j] = bitmask[i][j-1] | TWO(j);
    }
    while (ntest--) {
        cin >> a >> b;
        if (!hasSolution()) {
            cout << "impossible\n";
            continue;
        }
        ra = a; reverse(ra.begin(), ra.end());

        can.clear();
        REP(i,a.length()) {
            if (!i) codea[i] = getval(a[i]);
            else codea[i] = codea[i-1] + getval(a[i]) * p5[i];

            if (!i) coder[i] = getval(ra[i]);
            else coder[i] = coder[i-1] + getval(ra[i]) * p5[i];
        }
        REP(i,b.length()) {
            if (!i) codeb[i] = getval(b[i]);
            else codeb[i] = codeb[i-1] + getval(b[i]) * p5[i];
        }
        REP(i,b.length()) FOR(j,i,b.length()-1) {
            xuoib[i][j] = getCode(codeb, i, j);
            nguocb[i][j] = 0;
            for(int x = j, now = 0; x >= i; --x, ++now)
                nguocb[i][j] = nguocb[i][j] + getval(b[x]) * p5[now];
        }
        REP(i,a.length()) {
            for(int j = 0; i+j < a.length(); ++j) {
                can.insert(getCode(codea, i, i+j));
                can.insert(getCode(coder, i, i+j));
            }
        }
        // for(__typeof(can.begin()) it = can.begin(); it != can.end(); ++it) {
        //     cout << *it << ' ';
        // }
        // cout << endl;

        while (!qu.empty()) qu.pop();
        qu.push(0);
        memset(d, -1, sizeof d);
        d[0] = 0;

        set<long long> tmp;

        while (!qu.empty()) {
            int mask = qu.front();
            qu.pop();
            if (nreg[mask] >= 3) continue;

            if (mask == TWO(b.length())-1) {
                cout << d[mask] << endl;
                break;
            }

            tmp.clear();
            REP(i,b.length()) if (CONTAIN(mask, i)) {
                for(int j = 0; i+j < b.length(); ++j) {
                    tmp.insert(xuoib[i][i+j]);
                    tmp.insert(nguocb[i][i+j]);
                    if (!CONTAIN(mask, i+j+1)) break;
                }
            }

            REP(i,b.length()) if (!CONTAIN(mask, i)) {
                for(int j = 0; i+j < b.length(); ++j) {
                    long long need = getCode(codeb, i, i+j);
                    if (can.find(need) == can.end() && tmp.find(need) == tmp.end()) break;

                    int next = mask | bitmask[i][i+j];
                    // cout << mask << "  +  " << i << ' ' << j << "  -->  " << next << endl;
                    if (d[next] < 0) {
                        d[next] = d[mask] + 1;
                        qu.push(next);
                    }
                    if (CONTAIN(mask, i+j+1)) break;
                }
            }
        }
    }
    return 0;
}
