
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

map<string,string> to;

string define(string a) {
    if (!to.count(a)) return a;
    return to[a] = define(to[a]);
}

bool isOp(char c) {
    if (c == '+' || c == '-') return true;
    if (c == '*' || c == '/' || c == '%') return true;
    if (c == '^') return true;

    return false;
}

int toInt(string s) {
    int res = 0, sign = 1;
    for(int i = 0; i < s.length(); ++i) {
        if (i == 0 && s[i] == '-') sign = -1;
        else if (s[i] >= '0' && s[i] <= '9') res = res * 10 + s[i] - '0';
        else return 0;
    }
    return res * sign;
}

int power(int a, int b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    int mid = power(a * a, b >> 1);
    if (b & 1) return mid * a;
    else return mid;
}

int _div(int a, int b) {
    int res = abs(a) / abs(b);
    if (a < 0) res = -res;
    if (b < 0) res = -res;
    return res;
}

int _mod(int a, int b) {
    int res = abs(a) % abs(b);
    if (a < 0) res = -res;
    if (b < 0) res = -res;
    return res;
}

int f(const string& s, int l, int r) {
    int level = 0;
    // binary operator + and -
    for(int i = r-1; i > l; --i) {
        if (s[i] == '(') ++level;
        else if (s[i] == ')') --level;
        else if (s[i] == '+' || s[i] == '-') {
            if (level == 0 && !isOp(s[i-1])) {
                int left = f(s, l, i);
                int right = f(s, i+1, r);

                if (s[i] == '+') return left + right;
                else return left - right;
            }
        }
    }

    // binary operator * / %
    level = 0;
    for(int i = r-1; i > l; --i) {
        if (s[i] == '(') ++level;
        else if (s[i] == ')') --level;
        else if (s[i] == '*' || s[i] == '/' || s[i] == '%') {
            if (level == 0) {
                int left = f(s, l, i);
                int right = f(s, i+1, r);

                if (s[i] == '*') return left * right;
                else if (s[i] == '/') {
                    return _div(left, right);
                }
                else return _mod(left, right);
            }
        }
    }

    // binary operator ^
    level = 0;
    for(int i = l; i < r-1; ++i) {
        if (s[i] == '(') ++level;
        else if (s[i] == ')') --level;
        else if (s[i] == '^') {
            if (level == 0) {
                int left = f(s, l, i);
                int right = f(s, i+1, r);

                return power(left, right);
            }
        }
    }

    // bracket
    if (s[l] == '(') return f(s, l+1, r-1);

    // unary operator + and -
    if (s[l] == '+') return f(s, l+1, r);
    if (s[l] == '-') return -f(s, l+1, r);

    return toInt(define(s.substr(l, r - l)));
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("plcool.in", "r", stdin);
    freopen("plcool.out", "w", stdout);
    string op;
    while (cin >> op) {
        if (op == "print") {
            string expr; getline(cin, expr);
            expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
            transform(expr.begin(), expr.end(), expr.begin(), ::tolower);
            printf("%d\n", f(expr, 0, expr.length()));
        } else { // op == "define"
            string a, b; cin >> a >> b;
            if (to.count(a)) continue;
            if (define(b) == a) continue;

            to[a] = b;
        }
    }
}

