
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

map<string,int> mp;
int get(string s) {
    if (mp.count(s)) return mp[s];
    else {
        cout << "strange" << endl;
        exit(0);
    }
}

int dist(int a, int b) {
    if (a <= b) return b - a;
    else return b + 12 - a;
}

bool major(int a, int b, int c) {
    if (dist(a, b) == 4 && dist(b, c) == 3) return true;
    if (dist(c, b) == 4 && dist(b, a) == 3) return true;
    return false;
}
bool minor(int a, int b, int c) {
    if (dist(a, b) == 3 && dist(b, c) == 4) return true;
    if (dist(c, b) == 3 && dist(b, a) == 4) return true;
    return false;
}

int main() {
    ios :: sync_with_stdio(false);

    mp["C" ] = 0;
    mp["C#"] = 1;
    mp["D" ] = 2;
    mp["D#"] = 3;
    mp["E" ] = 4;
    mp["F" ] = 5;
    mp["F#"] = 6;
    mp["G" ] = 7;
    mp["G#"] = 8;
    mp["A" ] = 9;
    mp["B" ] = 10;
    mp["H" ] = 11;

    string x, y, z;
    while (cin >> x >> y >> z) {
        int a = get(x), b = get(y), c = get(z);
        int typ = 3;
        if (major(a, b, c) || major(a, c, b) || major(b, a, c)) typ = 1;
        if (minor(a, b, c) || minor(a, c, b) || minor(b, a, c)) typ = 2;

        cout << (typ == 1 ? "major" : (typ == 2 ? "minor" : "strange")) << endl;
    }
    return 0;
}

