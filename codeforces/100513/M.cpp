#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

struct Scope {
    vector< pair<int,int> > vars;

    Scope() {
        vars.resize(30);
        REP(i,30) vars[i] = make_pair(-1, -1);
    }

    void addVar(char c, int u, int v) {
        vars[c - 'a'] = make_pair(u, v);
    }
};

vector< Scope > scopes;
int n;
char a[55][55];

int main() {
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) gets(a[i]);

        scopes.clear();
        scopes.push_back(Scope());
        FOR(i,1,n) {
            REP(j,strlen(a[i])) {
                char c = a[i][j];
                if (c == '{') {
                    scopes.push_back(Scope());
                }
                else if (c == '}') {
                    scopes.pop_back();
                }
                else if (c != ' ') {
                    FORD(x,scopes.size()-2,0)
                        if (scopes[x].vars[c - 'a'].first >= 0) {
                            printf("%d:%d: warning: shadowed declaration of %c, the shadowed position is %d:%d\n", i, j+1, c,
                                    scopes[x].vars[c - 'a'].first,
                                    scopes[x].vars[c - 'a'].second);
                            break;
                        }
                    scopes.back().addVar(c, i, j + 1);
                }
            }
        }
        puts("");
    }
    return 0;
}

