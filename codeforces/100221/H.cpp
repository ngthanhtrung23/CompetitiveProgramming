
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

bool isDigit(char a) {
    return '0' <= a && a <= '9';
}
bool isNumber(char a, char b) {
    if (a == '-' && isDigit(b)) return true;
    if (isDigit(a) && isDigit(b)) return true;
    return false;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("tex.in", "r", stdin);
    freopen("tex.out", "w", stdout);

    int in_math = false;
    bool bad = false;
    FOR(line,1,10001110) {
        string s;
        if (!(getline(cin, s))) break;

        s += ' ';
        REP(i,SZ(s)) {
            if (s[i] == '\\') {
                // escape character
                ++i;
            }
            else if (s[i] == '$') {
                if (s[i+1] == '$') ++i;
                in_math = !in_math;
            }
            else if (s[i] == '^' || s[i] == '_') {
                if (in_math && i + 2 < SZ(s)) {
                    if (isNumber(s[i+1], s[i+2])) {
                        printf("Warning at line %d, position %d\n", line, i+1);
                        bad = true;
                    }
                }
            }
        }
    }
    if (!bad) puts("No warnings");
}
