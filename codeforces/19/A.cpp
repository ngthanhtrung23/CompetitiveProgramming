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

struct Team {
    string name;
    int score;
    int goals, missed;
} a[55];
int n;
map<string,int> id;

bool operator < (const Team &a, const Team &b) {
    if (a.score != b.score) return a.score > b.score;
    if (a.goals - a.missed != b.goals - b.missed) return a.goals - a.missed > b.goals - b.missed;
    return a.goals > b.goals;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        id.clear();
        FOR(i,1,n) {
            cin >> a[i].name;
            id[a[i].name] = i;
        }
        FOR(i,1,n-1) FOR(j,i+1,n) {
            string names, scores;
            cin >> names >> scores;

            REP(i,names.length()) if (names[i] == '-') names[i] = ' ';
            REP(i,scores.length()) if (scores[i] == ':') scores[i] = ' ';

            string name1, name2;
            int id1, id2;
            int score1, score2;

            stringstream ss1(names); ss1 >> name1 >> name2;
            stringstream ss2(scores); ss2 >> score1 >> score2;

            id1 = id[name1]; id2 = id[name2];
            a[id1].goals += score1;
            a[id2].goals += score2;
            a[id1].missed += score2;
            a[id2].missed += score1;
            
            if (score1 > score2) {
                a[id1].score += 3;
            }
            else if (score1 == score2) {
                a[id1].score += 1;
                a[id2].score += 1;
            }
            else {
                a[id2].score += 3;
            }
        }
        sort(a+1, a+n+1);
        // FOR(i,1,n) {
            // cout << a[i].name << ":  " << a[i].score << ' ' << a[i].goals - a[i].missed << ' ' << a[i].goals << endl;
        // }
        set<string> s;
        FOR(i,1,n/2) s.insert(a[i].name);
        for(string u : s)
            cout << u << endl;
    }
    return 0;
}
