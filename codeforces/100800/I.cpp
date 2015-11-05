
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

bool isLower(char c) {
    return 'a' <= c && c <= 'z';
}
bool isUpper(char c) {
    return 'A' <= c && c <= 'Z';
}

char hard[8] = {'b', 'c', 'd', 'g', 'k', 'n', 'p', 't'};

char toHard(char c) {
    char res = hard[0];
    FOR(i,1,7)
        if (abs(hard[i] - c) < abs(res - c))
            res = hard[i];
    return res;
}

bool isHard(char c) {
    REP(i,8) if (hard[i] == c) return true;
    return false;
}

string transform(string s) {
    string res = s;

    // to lower case
    REP(i,SZ(res)) if (isUpper(res[i])) res[i] ^= ' ';

    // part 1:
    // hard consonants
    res[0] = toHard(res[0]);

    // part 2:
    bool seenDash = false;
    REP(i,SZ(res)) {
        if (res[i] == '-') seenDash = true;
        else {
            if (isHard(res[i]) && seenDash)
                res[i] = res[0];
        }
    }

    // part 3:
    if (isHard(res.back())) {
        char add = 'a';
        char last = res.back();

        if (abs(last - 'o') < abs(last - add)) add = 'o';
        if (abs(last - 'u') < abs(last - add)) add = 'u';

        res += add;
        res += 'h';
    }

    // revert the case!
    REP(i,SZ(s)) if (isUpper(s[i])) res[i] ^= ' ';

    // remove dash
    string final = "";
    REP(i,SZ(res))
        if (res[i] != '-') final += res[i];
    return final;
}

int main() {
    ios :: sync_with_stdio(false);
    string s;
    while (cin >> s) {
        cout << transform(s) << ' ';
    }
}

