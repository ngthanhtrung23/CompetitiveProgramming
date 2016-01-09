#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
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

string cipher, crib;
int len;

bool solve() {
    FOR(s,1,25) FOR(m,5,20) {
        string plain = "";
        for(int first = 0; first < len; first += m) {
            int last = first + m - 1;
            if (last >= len) last = len - 1;

            for(int i = last; i >= first; --i) {
                char c = cipher[i] - s;
                if (c < 'A') c += 26;

                plain += c;
            }
        }
        if (plain.find(crib) != string::npos) {
            cout << s << ' ' << m << endl;
            return true;
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> len;
        cipher = "";
        while (cipher.size() < len) {
            string tmp; cin >> tmp;
            cipher += tmp;
        }
        cin >> crib;
        if (!solve()) cout << "Crib is not encrypted.\n";
    }
    return 0;
}