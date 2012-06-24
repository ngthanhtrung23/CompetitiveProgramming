#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0; i < a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
using namespace std;

struct Team {
    int score, goal, miss;
    string name;
} a[10], save[10];

bool operator < (const Team &a, const Team &b) {
    if (a.score != b.score) return a.score > b.score;
    if (a.goal - a.miss != b.goal - b.miss) return a.goal - a.miss > b.goal - b.miss;
    if (a.goal != b.goal) return a.goal > b.goal;
    return a.name < b.name;
}

struct Match {
    string a, b;
    int ga, gb;
} m[10];

set<string> s;
map<string,int> id;
set< pair<string,string> > ok;

bool check(int x, int y) {
    FOR(i,1,4) a[i] = save[i];

    FOR(i,1,4) FOR(j,1,4)
    if (i != j && a[i].name == "BERLAND")
    if (ok.find(MP(a[i].name, a[j].name)) == ok.end()) {
        if (x > y) {
            a[i].score += 3;
        }
        else if (x < y) {
            a[j].score += 3;
        }
        else {
            a[i].score += 1;
            a[j].score += 1;
        }

        a[i].goal += x;
        a[i].miss += y;

        a[j].goal += y;
        a[j].miss += x;
    }

    sort(a+1, a+5);
    if (a[1].name == "BERLAND" || a[2].name == "BERLAND") return true;
    else return false;
}

int main() {
    FOR(i,1,5) {
        char c;
        cin >> m[i].a >> m[i].b >> m[i].ga >> c >> m[i].gb;
        s.insert(m[i].a);
        s.insert(m[i].b);
        ok.insert(MP(m[i].a, m[i].b));
        ok.insert(MP(m[i].b, m[i].a));
    }
    int cur = 0;
    for(set<string> :: iterator it = s.begin(); it != s.end(); it++) {
        ++cur;
        a[cur].name = *it;
        id[*it] = cur;
    }
    FOR(i,1,5) {
        int x = id[m[i].a], y = id[m[i].b];
        if (m[i].ga > m[i].gb) {
            a[x].score += 3;
        }
        else if (m[i].ga < m[i].gb) {
            a[y].score += 3;
        }
        else {
            a[x].score += 1;
            a[y].score += 1;
        }
        a[x].goal += m[i].ga;
        a[x].miss += m[i].gb;

        a[y].goal += m[i].gb;
        a[y].miss += m[i].ga;
    }
//    FOR(i,1,4) cout << a[i].name << ' ' << a[i].score << ' ' << a[i].goal << ' ' << a[i].miss << endl;

    FOR(i,1,4) save[i] = a[i];

    FOR(diff,1,100) FOR(y,0,100) {
        int x = y + diff;
        if (check(x, y)) {
            cout << x << ':' << y << endl;
            return 0;
        }
    }
    puts("IMPOSSIBLE");
    return 0;
}
