
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

struct Term {
    double b;
    double a[11];
} var[11];

string s;
int nTerm;
int id[300];
double value[11], delta[11];
char varName[11];

double init() {
    nTerm = 0;
    memset(id, 0, sizeof id);
    memset(var, 0, sizeof var);
    memset(delta, 0, sizeof delta);
    FOR(i,1,10) value[i] = 1.0;
}

bool isAlpha(char c) {
    return c >= 'a' && c <= 'z';
}

string addSpace(string s) {
    string res = "";
    if (s[0] != '+' && s[0] != '-') s = "+" + s;

    REP(i,SZ(s)) {
        char c = s[i];

        if (c == '^') {
            res += s[i-1];
            ++i;
        }
        else if (c == '+' || c == '-') {
            res += ' ';
            res += c;
            res += ' ';
        }
        else if (isAlpha(c)) {
            if (!isAlpha(s[i-1])) {
                res += ' ';
                res += c;
            }
            else if (!isAlpha(s[i+1])) {
                res += c;
                res += ' ';
            }
        }
        else res += c;
    }
    return res;
}

int getId(char c) {
    if (id[c]) return id[c];

    id[c] = ++nTerm;
    varName[nTerm] = c;
    return id[c];
}

void addTerm(string t, double coeff) {
    if (t.length() == 1) {
        int u = getId(t[0]);
        var[u].b += coeff;
    }
    else {
        int u = getId(t[0]);
        int v = getId(t[1]);

        if (u == v) {
            var[u].a[u] += coeff;
        }
        else {
            var[u].a[v] += coeff;
            var[v].a[u] += coeff;
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("formula1.in", "r", stdin);
    freopen("formula1.out","w", stdout);
    while (cin >> s) {
        init();

        s = addSpace(s);
//        DEBUG(s);
        double coeff = 1;
        stringstream ss(s);
        string token;

        double other = 0.0;
        vector<string> tokens;
        while (ss >> token) {
            tokens.push_back(token);
        }
        REP(i,SZ(tokens)) {
            string token = tokens[i];
            if (token == "+") coeff = 1.0;
            else if (token == "-") coeff = -1.0;
            else if (isAlpha(token[0])) {
                addTerm(token, coeff);
            }
            else {
                // number
                double x; stringstream ss(token);
                ss >> x;
                coeff *= x;
                if (i == SZ(tokens) - 1 || !isAlpha(tokens[i+1][0]))
                    other += coeff;
            }
        }
        REP(turn,100111) {
            FOR(i,1,nTerm) {
                delta[i] = 0.0;
                delta[i] = var[i].b;
                FOR(j,1,nTerm)
                    if (j == i) {
                        delta[i] += 2*var[i].a[i] * value[i];
                    }
                    else {
                        delta[i] += var[i].a[j] * value[j];
                    }
            }
            FOR(i,1,nTerm) {
                value[i] += delta[i] * 0.001;
                if (value[i] < 0) value[i] = 0;
                if (value[i] > 1) value[i] = 1;
            }
        }
        cout << (fixed) << setprecision(9);
        FOR(i,1,nTerm) {
            other += value[i] * var[i].b;
            FOR(j,i,nTerm)
                other += value[i] * var[i].a[j] * value[j];
        }
        cout << other << endl;
        FOR(i,1,nTerm) {
            cout << varName[i] << '=';
            cout << value[i] << endl;
        }
    }
}

