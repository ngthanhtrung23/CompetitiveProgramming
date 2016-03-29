
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

struct Move {
    int typ;
    int x[4];

    Move(int typ, int a, int b) : typ(typ) {
        x[0] = a;
        x[1] = b;
    }
    Move(int typ, int a, int b, int c, int d) : typ(typ) {
        x[0] = a;
        x[1] = b;
        x[2] = c;
        x[3] = d;
    }

    void print(bool rev) {
        if (typ == 3) {
            if (rev) reverse(x, x+4);

            printf("%lld", typ);
            REP(i,4) printf(" %lld", x[i]);
            puts("");
        } else {
            if (rev) reverse(x, x+2);

            printf("%lld", typ);
            REP(i,2) printf(" %lld", x[i]);
            puts("");
        }
    }
};
vector<Move> res;
int a, b, c, d;

void move1(int& a, int& b) {
    res.push_back(Move(1, a, b));
    a++;
    b++;
}

void move2(int& a, int& b) {
    res.push_back(Move(2, a, b));
    assert(a % 2 == 0);
    assert(b % 2 == 0);

    a >>= 1;
    b >>= 1;
}

void move3(int& a, int& b, int c, int d) {
    assert(b == c);
    res.push_back(Move(3, a, b, c, d));

    b = d;
}

bool rev;

void answer() {
    printf("%lld\n", SZ(res));
    for(auto p : res) p.print(rev);
}

void solveEqual() {
    while (a > c) {
        if (a % 2 == 0) move2(a, b);
        else {
            move1(a, b);
            move2(a, b);
        }
    }
    while (a < c) {
        move1(a, b);
    }
    answer();
}

#undef int
int main() {
#define int long long
    while (cin >> a >> b >> c >> d) {
        res.clear();
        rev = false;
        if (a > b) {
            rev = true;
            swap(a, b);
            swap(c, d);
        }
        try {
            if (a == b) {
                if (c == d) {
                    solveEqual();
                    continue;
                }
                else throw 1;
            }
            if (c == d) throw 1;

            if (c > d) throw 1; // can not lah

//            cout << "INIT: " << a << ' ' << b << endl;
            while ((b - a) % 2 == 0) {
                if (a % 2 == 0) {
                    move2(a, b);
                }
                else {
                    move1(a, b);
                    move2(a, b);
                }
            }
//            cout << "DIV2 " << a << ' ' << b << endl;

            if ((d - c) % (b - a)) {
                throw 1;
            }
            
            while (a > c) {
                if (a % 2 == 1) {
                    move1(a, b);
                }
                int aa, bb;
                aa = a;
                bb = b;
                REP(turn,b-a) {
                    move1(aa, bb);
                }
                move3(a, b, aa, bb);
                move2(a, b);
            }
//            cout << "LOWER " << a << ' ' << b << endl;

            while (a < c) {
                move1(a, b);
            }
//            cout << "EQUAL " << a << ' ' << b << endl;

            assert(b <= d);
            int aa = a, bb = b;
            while (b < d) {
                REP(turn,b-aa) {
                    move1(aa, bb);
                }
                move3(a, b, aa, bb);
            }
//            cout << "DONE " << a << ' ' << b << endl;

            answer();
        } catch (...) {
            puts("0");
        }
    }
}
