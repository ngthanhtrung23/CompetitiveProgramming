#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

string s;

bool isNumber(string token) {
    if (token.length() == 0) return false;
    for(char c : token)
        if (c < '0' || c > '9') return false;
    
    if (token.length() > 1 && token[0] == '0') return false;
    return true;
}

void print(const vector<string>& x) {
    if (x.empty()) {
        puts("-");
        return ;
    }
    putchar('"');
    REP(i,x.size()) {
        if (i > 0) putchar(',');
        printf("%s", x[i].c_str());
    }
    putchar('"');
    puts("");
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(0);
    while (cin >> s) {
        string token;
        vector<string> num, alpha;
        for(char c : s) {
            if (c == ',' || c == ';') {
                if (isNumber(token)) num.push_back(token);
                else alpha.push_back(token);
                token = "";
            }
            else {
                token += c;
            }
        }
        if (isNumber(token)) num.push_back(token);
        else alpha.push_back(token);
        print(num);
        print(alpha);
    }
}
