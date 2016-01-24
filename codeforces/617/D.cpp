
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

struct Point {
    int x, y;

    friend istream& operator >> (istream& cin, Point& p) {
        cin >> p.x >> p.y;
        return cin;
    }
} A, B, C;

bool check2(Point A, Point B, Point C) {
    if (A.y == B.y && (C.x <= min(A.x, B.x) || C.x >= max(A.x, B.x))) return true;
    if (A.x == B.x && (C.y <= min(A.y, B.y) || C.y >= max(A.y, B.y))) return true;
    return false;
}

int solve() {
    if (A.x == B.x && B.x == C.x) return 1;
    if (A.y == B.y && B.y == C.y) return 1;

    if (check2(A, B, C)
            || check2(B, C, A)
            || check2(C, A, B))
        return 2;

    return 3;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> A >> B >> C) {
        cout << solve() << endl;
    }
}
