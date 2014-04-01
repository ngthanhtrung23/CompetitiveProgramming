#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

char a[111], b[111];

bool win(char a, char b) {
    if (a == '8' && b == '[') return true;
        else if (a == '[' && b == '(') return true;
            else if (a == '(' && b == '8') return true;
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (gets(a)) {
        gets(b);
        int sa = 0, sb = 0;
        for(int i = 0; i < strlen(a); i += 2)
            if (win(a[i], b[i])) ++sa;
            else if (win(b[i], a[i])) ++sb;

        if (sa == sb) puts("TIE");
        else if (sa > sb) puts("TEAM 1 WINS");
        else puts("TEAM 2 WINS");
    }
    return 0;
}
