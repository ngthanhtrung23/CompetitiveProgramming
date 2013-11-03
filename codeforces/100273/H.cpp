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

string move[11];
int last;
long long save[55];
vector<int> a, b, c;

bool can(vector<int> &a, vector<int> &b) {
    if (a.size() == 0) return false;
    if (a[a.size()-1] == last) return false;

    if (b.size() == 0) return true;
    return a[a.size()-1] < b[b.size()-1];
}

void go(vector<int> &a, vector<int> &b) {
    last = a[a.size()-1];
    b.push_back(a[a.size()-1]);
    a.pop_back();
}

int n;
bool check1() {
    FOR(i,2,n)
        if (save[i] != save[i-1] * 3 + 2) return false;

    FOR(i,2,50) save[i] = save[i-1] * 3LL + 2;
    return true;
}
bool check2() {
    FOR(i,2,n)
        if (save[i] != save[i-1] * 2 + 1) return false;

    FOR(i,2,50) save[i] = save[i-1] * 2LL + 1;
    return true;
}
bool check3() {
    FOR(i,2,n)
        if (save[i] != save[i-1] * 3) return false;

    FOR(i,2,50) save[i] = save[i-1] * 3LL;
    return true;
}

int main() {
    freopen("hanoi.in", "r", stdin);
    freopen("hanoi.out", "w", stdout);

    ios :: sync_with_stdio(false);

    int k; cin >> k;
    REP(i,6) cin >> move[i];

    FOR(n,1,5) {
        ::n = n;
        int res = 0;
        a.clear(); b.clear(); c.clear();

        FORD(i,n,1) a.push_back(i);
        last = -1;

        while (c.size() != n && b.size() != n) {
            ++res;
            REP(i,6) {
                string cur = move[i];
                if (cur == "AB" && can(a, b)) {
                    go(a, b);
                    break;
                }
                else if (cur == "AC" && can(a, c)) {
                    go(a, c);
                    break;
                }
                else if (cur == "BA" && can(b, a)) {
                    go(b, a);
                    break;
                }
                else if (cur == "BC" && can(b, c)) {
                    go(b, c);
                    break;
                }
                else if (cur == "CA" && can(c, a)) {
                    go(c, a);
                    break;
                }
                else if (cur == "CB" && can(c, b)) {
                    go(c, b);
                    break;
                }
            }
        }

        save[n] = res;
    }

    if (check1()) cout << save[k] << endl;
    if (check2()) cout << save[k] << endl;
    if (check3()) cout << save[k] << endl;

    return 0;
}
