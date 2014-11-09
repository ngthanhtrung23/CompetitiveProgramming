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

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

struct String {
    int first, last;
    long long nAc, len;
    String() {}
    String(int first, int last, long long nAc, long long len) : first(first), last(last), nAc(nAc), len(len) {}

    String operator + (String other) {
        return String(first, other.last,
                nAc + other.nAc + ((last == 1 && other.first == 3) ? 1 : 0),
                len + other.len);
    }

    void print() {
        cout << len << ' ' << first << ' ' << last << ' ' << nAc << endl;
    }

    string toString() {
        if (len == 1) {
            string res = "";
            res += (char) ('A' + first - 1);
            return res;
        }
        if (len == 2) {
            string res = "";
            res += (char) ('A' + first - 1);
            res += (char) ('A' + last - 1);
            return res;
        }
        if (first == 1) {
            string res = "";
            REP(turn,nAc) res += "AC";
            if (nAc == 0) res += (char) ('A' + first - 1);
            while (res.length() < len - 1) res += 'B';
            if (res.length() < len) res += (char) ('A' + last - 1);
            return res;
        }
        else {
            string res = "";
            res += (char) ('A' + first - 1);
            REP(turn,nAc) res += "AC";
            while (res.length() < len - 1) res += 'B';
            if (res.length() < len) res += (char) ('A' + last - 1);
            return res;
        }
    }
} s[55];
int k, n, m;
long long x;

int getMin(int n, int first, int last) {
    if (first == 2 || last == 2) return 0;
    if (n == 1) return 0;
    if (n == 2 && first == 1 && last == 3) return 1;
    return 0;
}

int getMax(int n, int first, int last) {
    if (first != 1) --n;
    if (n % 2 == 0) {
        if (last == 3) return n / 2;
        else return (n - 1) / 2;
    }
    else {
        return n / 2;
    }
}

bool solve() {
    FOR(first1, 1, 3) FOR(last1, 1, 3) FOR(nAc1, getMin(n, first1, last1), getMax(n, first1, last1))
        if (first1 == last1 || n > 1)
        FOR(first2, 1, 3) FOR(last2, 1, 3) FOR(nAc2, getMin(m, first2, last2), getMax(m, first2, last2))
        if (first2 == last2 || m > 1) {
            s[1] = String(first1, last1, nAc1, n);
            s[2] = String(first2, last2, nAc2, m);
            FOR(i,3,k) s[i] = s[i-2] + s[i-1];

            if (s[k].nAc == x) {
                cout << s[1].toString() << endl << s[2].toString() << endl;
                // FOR(i,1,k) s[i].print();
                return true;
            }
        }
    return false;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> k >> x >> n >> m) {
        if (!solve()) cout << "Happy new year!" << endl;
    }
    return 0;
}

