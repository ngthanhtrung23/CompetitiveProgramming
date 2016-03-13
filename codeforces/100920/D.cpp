#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 1000111;
char s[MN];
bool good[MN];
int match[MN], len;

int ATOM = 0;
int MUL = 1;
int ADD = 2;

int parse(int l, int r) {
    if (s[l] == '(' && match[l] == r) {
        int typ = parse(l+1, r-1);

        if (typ == ATOM) {
            good[l] = good[r] = true;
        }
        else if (typ == MUL) {
            if (l > 0 && s[l-1] == '/') {
                // cannot :(
            }
            else {
                good[l] = good[r] = true;
            }
        }
        else { // typ == ADD
            if (l > 0 && (s[l-1] == '*' || s[l-1] == '/' || s[l-1] == '-')) {
            }
            else if (r < len-1 && (s[r+1] == '*' || s[r+1] == '/')) {
            }
            else {
                good[l] = good[r] = true;
            }
        }

        if (good[l]) return typ;
        else return ATOM;
    }

    int i = l;
    int typ = ATOM;
    while (i <= r) {
        if (s[i] == 'x') {
            ++i;
        }
        else {
            assert(s[i] == '(');
            int t = parse(i, match[i]);
            typ = max(typ, t);
            i = match[i] + 1;
        }
        if (i > r) break;

        if (s[i] == '*' || s[i] == '/') typ = max(typ, MUL);
        if (s[i] == '+' || s[i] == '-') typ = max(typ, ADD);
        ++i;
    }

    return typ;
}

int main() {
    int ntest; scanf("%d\n", &ntest);
    while (ntest--) {
        scanf("%s\n", &s[0]);
        len = strlen(s);
        REP(i,len) good[i] = 0;

        stack<int> st;
        REP(i,len) {
            if (s[i] == '(') st.push(i);
            else if (s[i] == ')') {
                int j = st.top(); st.pop();
                match[i] = j;
                match[j] = i;
            }
        }
        parse(0, len-1);

        REP(i,len) if (!good[i]) putchar(s[i]); puts("");
    }
}
