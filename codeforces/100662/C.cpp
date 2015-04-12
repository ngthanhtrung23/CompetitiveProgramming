
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

struct Num {
    int sign;
    int dir;

    Num(int sign = 1, int dir = 0) : sign(sign), dir(dir) {}
    Num(char c) {
        sign = 1;
        if (c == 'i') dir = 1;
        else if (c == 'j') dir = 2;
        else if (c == 'k') dir = 3;
        else dir = 0;
    }

    bool operator == (const Num& a) {
        return dir == a.dir && sign == a.sign;
    }

    Num operator + (const Num& a) const {
        Num res;
        if (dir == 0) { res.dir = a.dir; res.sign = 1; }
        else if (dir == 1) {
            res.dir = a.dir ^ 1;
            res.sign = (a.dir % 2 == 1) ? -1 : 1;
        }
        else if (dir == 2) {
            res.dir = (a.dir >= 2) ? (a.dir - 2) : (a.dir + 2);
            res.sign = (a.dir == 1 || a.dir == 2) ? -1 : 1;
        }
        else {
            res.dir = (a.dir >= 2) ? (a.dir - 2) : (a.dir + 2);
            res.dir ^= 1;
            res.sign = (a.dir >= 2) ? -1 : 1;
        }

        if (sign < 0) res.sign = -res.sign;
        if (a.sign < 0) res.sign = -res.sign;
        return res;
    }

    string toString() {
        string res = "";
        if (sign < 0) res = "-";
        if (dir == 0) res += '1';
        else if (dir == 1) res += 'i';
        else if (dir == 2) res += 'j';
        else res += 'k';
        return res;
    }
};

Num power(const Num& a, long long k) {
    if (k == 0) return Num(1, 0);
    if (k == 1) return a;
    Num mid = power(a + a, k >> 1);
    if (k & 1) return mid + a;
    else return mid;
}

int l;
long long rep;
string orig, a;

#define left __left
#define right __right
Num left[100111], right[100111];

int main() {
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> l >> rep >> orig;
        Num each(1, 0);
        REP(i,orig.length())
            each = each + Num(orig[i]);
        Num all = power(each, rep);

        bool res = true;
        if (all == Num(-1, 0)) {
            if (rep < 4) {
                a = " ";
                REP(turn,rep) a = a + orig;
            }
            else a = " " + orig + orig + orig + orig;

//            DEBUG(a);

            left[0] = Num(1, 0);
            int n = a.length() - 1;
            FOR(i,1,n) left[i] = left[i-1] + Num(a[i]);

            right[n+1] = Num(1, 0);
            FORD(i,n,1) right[i] = Num(a[i]) + right[i+1];

//            FOR(i,1,n) cout << left[i].toString() << ' '; cout << endl;
//            FOR(i,1,n) cout << right[i].toString() << ' '; cout << endl;

            long long u = -1, v = -1;
            FOR(i,1,n) if (left[i] == Num(1, 1)) {
                u = i;
                break;
            }
            if (u == -1) res = false;
            else {
                long long l = orig.length() * rep;
                FORD(i,n,1) if (right[i] == Num(1, 3)) {
                    v = l - (n - i);
                    break;
                }
                if (v == -1) res = false;
                else res = u + 1 < v;
            }
        }
        else res = false;

        cout << "Case #" << test << ": " << (res ? "YES" : "NO") << endl;
        cerr << test << endl;
    }
    return 0;
}

