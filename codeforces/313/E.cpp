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

const int MN = 100111;
int a[MN], inA[MN], b[MN], inB[MN];

stack< pair<int,int> > st;
vector<int> res;
int n, m;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        memset(inA, 0, sizeof inA);
        memset(inB, 0, sizeof inB);
        FOR(i,1,n) cin >> a[i], inA[a[i]]++;
        FOR(i,1,n) cin >> b[i], inB[b[i]]++;

        res.clear();
        REP(v1,m) {
            while (inA[v1]) {
                st.push(make_pair(1, v1));
                --inA[v1];
            }

            int v2 = m - v1 - 1;

            while (inB[v2]) {
                if (!st.empty() && st.top().first == 1) {
                    res.push_back((st.top().second + v2) % m);
                    st.pop();
                }
                else st.push(make_pair(2, v2));
                --inB[v2];
            }
        }
        vector<int> v1, v2; v1.clear(); v2.clear();
        while (!st.empty()) {
            if (st.top().first == 1)
                v1.push_back(st.top().second);
            else v2.push_back(st.top().second);
            st.pop();
        }
        reverse(v2.begin(), v2.end());
        REP(i,v1.size())
            res.push_back((v1[i] + v2[i]) % m);
        sort(res.begin(), res.end(), greater<int>());
        REP(i,res.size()) printf("%d ", res[i]); puts("");
    }
    return 0;
}
