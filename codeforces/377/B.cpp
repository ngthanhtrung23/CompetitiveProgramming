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

const int MN = 100111;

int nStudent, nBug, nPass, trace[MN];
struct Bug {
    int difficulty;
    int id, assigned;
} bugs[MN];
struct Student {
    int ability, pass, capacity;
    int id;
} students[MN];

bool operator < (const Bug& a, const Bug& b) {
    if (a.difficulty != b.difficulty) return a.difficulty < b.difficulty;
    return a.id < b.id;
}

bool operator < (const Student& a, const Student& b) {
    if (a.ability != b.ability) return a.ability < b.ability;
    return a.id < b.id;
}

bool check(int val) {
    FOR(i,1,nStudent) students[i].capacity = val;

    set< pair<int,int> > s;
    
    int j = nStudent + 1;
    long long total = 0;
    FORD(i,nBug,1) {
        while (j > 1 && students[j-1].ability >= bugs[i].difficulty) {
            --j;
            s.insert(make_pair(students[j].pass, j));
        }

        if (s.empty()) return false;
        int cur = s.begin()->second;
        s.erase(s.begin());

        bugs[i].assigned = students[cur].id;
        if (students[cur].capacity == val) total += students[cur].pass;
        students[cur].capacity--;

//        if (val == 2) cout << bugs[i].id << " --> " << students[cur].id << endl;

        if (students[cur].capacity) {
            s.insert(make_pair(0, cur));
        }
    }
//    DEBUG(total);
    return total <= nPass;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> nStudent >> nBug >> nPass) {
        FOR(i,1,nBug) {
            cin >> bugs[i].difficulty;
            bugs[i].id = i;
        }
        FOR(i,1,nStudent) cin >> students[i].ability;
        FOR(i,1,nStudent) {
            cin >> students[i].pass;
            students[i].id = i;
        }
        sort(bugs+1, bugs+nBug+1);
        sort(students+1, students+nStudent+1);

//        FOR(i,1,nBug) cout << bugs[i].difficulty << ' '; cout << endl;
//        FOR(i,1,nStudent) cout << students[i].ability << ' '; cout << endl;
        
        int l = 1, r = nBug + 1, res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        if (res > nBug) cout << "NO" << endl;
        else {
            cout << "YES" << endl;
            check(res);
            FOR(i,1,nBug) {
                trace[ bugs[i].id ] = bugs[i].assigned;
            }
            FOR(i,1,nBug) cout << trace[i] << ' '; cout << endl;
        }
    }
    return 0;
}
