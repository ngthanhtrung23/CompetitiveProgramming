#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
using namespace std;

int n, l;
char s[100111];

int main() {
    while (scanf("%d\n", &n) == 1) {
        gets(s); l = strlen(s);
        int res = 0;
        for(int i = 0; i < l; i += n) if (i > 2) {
            if (s[i-1] == s[i-2] && s[i-2] == s[i-3]) ++res;
        }
        cout << res << endl;
    }
    return 0;
}

