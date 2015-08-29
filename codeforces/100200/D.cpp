
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

#define negate negate__
using namespace std;

const int LESS = -1;
const int ARB = 0;
const int GREATER = 1;

int nVar, nEqu;
string goal;

struct Vector {
    int x[111];
} C, sign_x, B, sign_B;

Vector negate(const Vector& a) {
    Vector b;
    REP(i,111) b.x[i] = -a.x[i];
    return b;
}

struct Matrix {
    int x[111][111];
} A;

Matrix transpose(const Matrix& a) {
    Matrix res;
    REP(i,111) REP(j,111)
        res.x[i][j] = a.x[j][i];
    return res;
}

string pad(string s) {
    string res = "";
    for(char c : s) {
        if (c == 'x' || c == '+' || c == '-' || c == '<' || c == '>' || c == '=') {
            res += ' ';
            res += c;
            res += ' ';
        }
        else res += c;
    }
    return res;
}

int to_num(string s) {
    stringstream ss(s);
    int res; ss >> res;
    return res;
}

void readInput() {
    string inp;
    getline(cin, inp);
    // Read optimization goal
    getline(cin, inp); inp = pad(inp);
    stringstream ss(inp);
    ss >> goal;
    string t;
    if (goal == "ma") {
        ss >> t;
        goal = "max";
    }
    int val = 1;
    while (ss >> t) {
        if (t == "x") {
            int id; ss >> id;
            C.x[id] = val;
            val = 1;
        }
        else if (t == "-") {
            val = -val;
        }
        else if (t == "+") {
        }
        else {
            val *= to_num(t);
        }
    }
//    PR(C.x, nVar);

    // Read constraints
    getline(cin, inp); // with
    FOR(i,1,nVar) {
        getline(cin, inp); inp = pad(inp);
        stringstream ss(inp);

        ss >> t >> t; // x id
        ss >> t;
        if (t[0] == 'a') sign_x.x[i] = ARB;
        else if (t[0] == '<') sign_x.x[i] = LESS;
        else sign_x.x[i] = GREATER;
    }
//    PR(sign_x.x, nVar);

    // read A
    getline(cin, inp); // under
    FOR(i,1,nEqu) {
        getline(cin, inp); inp = pad(inp);

        val = 1;
        stringstream ss(inp);

        while (ss >> t) {
            if (t == "x") {
                int id; ss >> id;
                A.x[i][id] = val;

                val = 1;
            }
            else if (t == "-") {
                val = -val;
            }
            else if (t == "+") {
            }
            else if (t == "<") {
                sign_B.x[i] = LESS;
            }
            else if (t == ">") {
                sign_B.x[i] = GREATER;
            }
            else if (t == "=") {
                break;
            }
            else {
                val *= to_num(t);
            }
        }

        val = 1;
        while (ss >> t) {
            if (t == "-") val = -val;
            else {
                B.x[i] = val * to_num(t);
            }
        }
    }
    FOR(i,1,nEqu) {
//        PR(A.x[i], nVar);
    }
//    PR(B.x, nEqu);
//    PR(sign_B.x, nEqu);
}

void printOutput() {
    cout << nEqu << ' ' << nVar << endl;

    // Goal
    cout << (goal == "min" ? "max" : "min") << ' ';
    
    bool ok = false;
    FOR(i,1,nEqu) {
        int val = B.x[i];
        if (val == 0) continue;

        if (val == 1) {
            if (ok) cout << '+';
        } else if (val == -1) {
            cout << '-';
        }
        else {
            if (ok && val > 0) cout << '+';
            cout << val;
        }
        ok = true;
        cout << 'y';
        cout << i;
    }
    if (!ok) cout << '0';
    cout << endl;

    cout << "with" << endl;
    FOR(i,1,nEqu) {
        if (sign_B.x[i] == 0) {
            cout << 'y' << i << " arbitary" << endl;
        }
        else if (sign_B.x[i] == LESS) {
            cout << 'y' << i << "<=0" << endl;
        }
        else {
            cout << 'y' << i << ">=0" << endl;
        }
    }

    cout << "under" << endl;
    FOR(i,1,nVar) {
        bool ok = false;
        FOR(j,1,nEqu) {
            if (A.x[i][j] == 0) continue;
            
            if (A.x[i][j] == 1) {
                if (ok) cout << '+';
            }
            else if (A.x[i][j] == -1) cout << '-';
            else {
                if (ok && A.x[i][j] > 0) cout << '+';
                cout << A.x[i][j];
            }
            ok = true;

            cout << 'y';
            cout << j;
        }
        if (!ok) cout << '0';

        if (sign_x.x[i] == 0) cout << "=" << C.x[i] << endl;
        else if (sign_x.x[i] == LESS) cout << "<=" << C.x[i] << endl;
        else cout << ">=" << C.x[i] << endl;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("dual.in", "r", stdin);
    freopen("dual.out", "w", stdout);
    cin >> nVar >> nEqu;
    readInput();
    if (goal == "max") sign_B = negate(sign_B);
    else sign_x = negate(sign_x);
    A = transpose(A);
    printOutput();
}
