#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0,_a=(a); i < _a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
using namespace std;

struct Function {
    string name;
    vector<string> types;
} f[1011], cur;

bool operator == (const Function &a, const Function &b) {
    if (a.name != b.name) return false;
    if (a.types.size() != b.types.size()) return false;
    REP(i,a.types.size())
    if (a.types[i] != "T" && b.types[i] != "T")
        if (a.types[i] != b.types[i]) return false;
    return true;
}

map<string,string> types;

int nFunc, nVar, nCall;
char s[1011];

#define refine() { REP(_,strlen(s)) if (s[_] == '(' || s[_] == ')' || s[_] == ',') s[_] = ' '; }

int main() {
    scanf("%d\n", &nFunc);
    FOR(i,1,nFunc) {
        gets(s);
        refine();
        istringstream sin(s);
        string tmp;
        sin >> tmp;
        sin >> f[i].name;
        f[i].types.clear();
        while (sin >> tmp) {
            f[i].types.PB(tmp);
        }
    }
    scanf("%d\n", &nVar);
    FOR(i,1,nVar) {
        gets(s);
        refine();
        string t, v;
        istringstream sin(s);
        sin >> t >> v;
        types[v] = t;
    }
    scanf("%d\n", &nCall);
    FOR(i,1,nCall) {
        gets(s); refine();
        istringstream sin(s);
        sin >> cur.name;
        cur.types.clear();
        string tmp;
        while (sin >> tmp) {
            cur.types.PB(types[tmp]);
        }

        int res = 0;
        FOR(j,1,nFunc) {
            if (cur == f[j]) ++res;
        }

        printf("%d\n", res);
    }
    return 0;
}
