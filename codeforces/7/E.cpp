
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

const int MN = 111;
string name[MN], expr[MN];
int n;
map<string,int> cache;

int parse(const string& s, int l, int r) {
//    DEBUG(s.substr(l, r - l + 1));
    int sum = 0;
    FORD(i,r,l) {
        if (s[i] == ')') ++sum;
        else if (s[i] == '(') --sum;
        else if (s[i] == '+' || s[i] == '-') {
            if (sum == 0) {
                int left = parse(s, l, i - 1);
                int right = parse(s, i+1, r);

                if (!left) return 0;  // left side is invalid
                if (!right) return 0;  // right side is invalid
                if (s[i] == '-' && right == 1) return 0; // right side is add/sub --> invalid
                return 1;  // sum
            }
        }
    }
    assert(sum == 0);
    FORD(i,r,l) {
        if (s[i] == ')') ++sum;
        else if (s[i] == '(') --sum;
        else if (s[i] == '*' || s[i] == '/') {
            if (sum == 0) {
                int left = parse(s, l, i-1);
                int right = parse(s, i+1, r);

                if (left <= 1) return 0; // left side is invalid / add
                if (right <= 1) return 0; // right side is invalid / add
                if (s[i] == '/' && right <= 2) return 0;
                return 2; // mult
            }
        }
    }
    assert(sum == 0);

    if (s[l] == '(') {
        int t = parse(s, l+1, r-1);
        if (t == 0) return 0;
        return 3; // atomic
    }

    string tmp = s.substr(l, r - l + 1);
    if (cache.count(tmp)) return cache[tmp];
    else return 3; // atomic
}

string refine(string s) {
    string res = "";
    for(char c : s) if (c != ' ') res += c;
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) {
            char hash = ' '; while (hash != '#') cin >> hash;

            string def;
            cin >> def >> name[i];
            
            getline(cin, expr[i]);
            expr[i] = refine(expr[i]);

            cache[name[i]] = parse(expr[i], 0, SZ(expr[i]) - 1);
        }
//        cout << "--------------" << endl;
//        FOR(i,1,n) cout << name[i] << " ---> " << expr[i] << endl;

        string s;
        getline(cin, s);
        s = refine(s);

        if (parse(s, 0, SZ(s) - 1)) cout << "OK"; else cout << "Suspicious";
        cout << endl;
    }
}
