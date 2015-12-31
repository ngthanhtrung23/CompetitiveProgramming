
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 2011;
string a, b;
int top;
int la, lb;
char st[MN];

string minimum(string a) {
    top = 0;
    for(char c : a) {
        if (top && st[top] == (c ^ ' ')) --top;
        else st[++top] = c;
    }
    string res = "";
    FOR(i,1,top) res += st[i];
    return res;
}

#define equal equal____
int equal[MN][MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("subword.in", "r", stdin);
    freopen("subword.out", "w", stdout);
    while (cin >> a >> b) {
        int old_lenb = SZ(b);
        string oldb = b;

        a = minimum(a);
        b = minimum(b);
        la = SZ(a);
        lb = SZ(b);

//        DEBUG(a);
//        DEBUG(b);
        
        if (lb == 0) {
            cout << a + oldb << endl;
            continue;
        }
        memset(equal, 0, sizeof equal);

        int best = 0;
        int al = 0, ar = -1, bl = 0, br = -1;
        FORD(i,la-1,0) FORD(j,lb-1,0) {
            if (a[i] != b[j]) equal[i][j] = 0;
            else equal[i][j] = equal[i+1][j+1] + 1;

            if (equal[i][j] > best) {
                best = equal[i][j];
                al = i; ar = al + equal[i][j] - 1;
                bl = j; br = bl + equal[i][j] - 1;
            }
        }
//        DEBUG(best);
        string res = "";

        FOR(i,0,al-1) res += a[i];
        FORD(i,bl-1,0) res += b[i] ^ ' ';

        res += oldb;

        FORD(i,lb-1,br+1) res += b[i] ^ ' ';
        FOR(i,ar+1,la-1) res += a[i];

        cout << res << endl;
    }
}
