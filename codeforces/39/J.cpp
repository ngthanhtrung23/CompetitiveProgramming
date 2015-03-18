#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 1000111;
string a, b;
bool isPrefix[MN], isSuffix[MN];
char tmp[MN];

int main() {
    while (gets(tmp)) {
        a = string(tmp);
        gets(tmp); b = string(tmp);
        b = b + " ";

        REP(i,a.length()) {
            if (i == 0) isPrefix[i] = true;
            else isPrefix[i] = isPrefix[i-1];
            isPrefix[i] &= a[i] == b[i];
        }
        b = " " + b;
        FORD(i,a.length()-1,0) {
            if (i == a.length()-1) isSuffix[i] = true;
            else isSuffix[i] = isSuffix[i+1];
            isSuffix[i] &= a[i] == b[i];
        }

        vector<int> res;
        REP(i,a.length()) {
            if (i == 0) {
                if (isSuffix[1]) res.push_back(i);
            }
            else if (i == a.length()-1) {
                if (isPrefix[i-1]) res.push_back(i);
            }
            else {
                if (isPrefix[i-1] && isSuffix[i+1])
                    res.push_back(i);
            }
        }
        cout << res.size() << endl;
        for(auto x : res) printf("%d ", x + 1); cout << endl;
    }
    return 0;
}

