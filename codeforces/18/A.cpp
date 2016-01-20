
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

bool good(int a, int b, int c) {
    return a == b + c;
}

bool right(int a, int b, int c) {
    if (a == 0 || b == 0 || c == 0) return false;
    return good(a, b, c)
        || good(b, a, c)
        || good(c, a, b);
}

int dist(int x1, int y1, int x2, int y2) {
    return sqr(x1 - x2) + sqr(y1 - y2);
}

bool right(int x1, int y1, int x2, int y2, int x3, int y3) {
    int a = dist(x1, y1, x2, y2);
    int b = dist(x2, y2, x3, y3);
    int c = dist(x3, y3, x1, y1);
    return right(a, b, c);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int x1, y1, x2, y2, x3, y3;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        if (right(x1, y1, x2, y2, x3, y3)) cout << "RIGHT" << endl;
        else {
            bool good = false;
            FOR(u1,x1-1,x1+1)
            FOR(v1,y1-1,y1+1)
                FOR(u2,x2-1,x2+1)
                FOR(v2,y2-1,y2+1)
                    FOR(u3,x3-1,x3+1)
                    FOR(v3,y3-1,y3+1) {
                        int moved = 0;
                        moved += abs(u1 - x1);
                        moved += abs(v1 - y1);
                        moved += abs(u2 - x2);
                        moved += abs(v2 - y2);
                        moved += abs(u3 - x3);
                        moved += abs(v3 - y3);

                        if (moved == 1 && right(u1, v1, u2, v2, u3, v3)) {
                            good = true;
                        }
                    }
            if (good) cout << "ALMOST" << endl;
            else cout << "NEITHER" << endl;
        }
    }
}
