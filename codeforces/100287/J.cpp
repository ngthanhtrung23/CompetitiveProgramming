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
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

bool upper(char c) {
    return c >= 'A' && c <= 'Z';
}

bool lower(char c) {
    return c >= 'a' && c <= 'z';
}

int main() {
    freopen("java_c.in", "r", stdin); freopen("java_c.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    string s;
    while (cin >> s) {
        if (upper(s[0])) cout << "Error!";
        else if (s.back() == '_' || s[0] == '_') cout << "Error!";
        else if (s.find("__") != string::npos) cout << "Error!";
        else {
            bool has_ = false;
            bool hasUpper = false;

            REP(i,s.length()) {
                if (s[i] == '_') has_ = true;
                if (upper(s[i])) hasUpper = true;
            }
            if (hasUpper && has_) cout << "Error!";
            else if (hasUpper) {
                for(int i = 0; i < s.length(); ++i) {
                    if (upper(s[i])) cout << '_' << (char) (s[i] ^ ' ');
                    else cout << s[i];
                }
            }
            else {
                for(int i = 0; i < s.length(); ++i) {
                    if (s[i] == '_') {
                        ++i;
                        cout << (char) (s[i] ^ ' ');
                    }
                    else {
                        cout << s[i];
                    }
                }
            }
        }
        cout << endl;
    }
    return 0;
}