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
    int nWrong[22];
    bool accepted[22];
    int penalty, nAc;
    vector<pair<int,int> > scores;

    Team(string name = "") : name(name) {
        memset(nWrong, 0, sizeof nWrong);
        memset(accepted, false, sizeof accepted);
        penalty = nAc = 0;
        scores.clear();
    }

    void submit(int t, int prob, string status) {
        if (accepted[prob]) return ;

        if (status[0] == 'a') {
            penalty += nWrong[prob] * 20 + t;
            accepted[prob] = true;
            ++nAc;
            scores.push_back(make_pair(t, penalty));
        }
        else {
            ++nWrong[prob];
        }
    }
} teams[55];

bool lower(const Team &a, const Team &b) {
    if (a.nAc != b.nAc) return a.nAc > b.nAc;
    if (a.penalty != b.penalty) return a.penalty < b.penalty;
    FORD(i,a.scores.size()-1,0)
        if (a.scores[i].first < b.scores[i].first) return true;
        else if (a.scores[i].first > b.scores[i].first) return false;
        else if (a.scores[i].second != b.scores[i].second)
            return a.scores[i].second < b.scores[i].second;
    return false;
}

bool operator < (const Team &a, const Team &b) {
    if (a.nAc != b.nAc) return a.nAc > b.nAc;
    if (a.penalty != b.penalty) return a.penalty < b.penalty;
    FORD(i,a.scores.size()-1,0)
        if (a.scores[i].first < b.scores[i].first) return true;
        else if (a.scores[i].first > b.scores[i].first) return false;
        else if (a.scores[i].second != b.scores[i].second)
            return a.scores[i].second < b.scores[i].second;
    return a.name < b.name;
}

int nTeam, nSub;
#define rank rank_
int rank[55];

int getId(string name) {
    FOR(i,1,nTeam)
        if (teams[i].name == name) return i;
    return -1;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> nTeam >> nSub;
        FOR(i,1,nTeam) {
            string s; cin >> s;
            teams[i] = Team(s);
        }
        FOR(i,1,nSub) {
            int t; string name, prob, status;
            cin >> t >> name >> prob >> status;

            int id = getId(name);
            teams[id].submit(t, prob[0] - 'A', status);
        }
        sort(teams+1, teams+nTeam+1);

        FOR(i,1,nTeam) {
            if (i == 1) rank[i] = 1;
            else if (lower(teams[i-1], teams[i])) rank[i] = i;
            else rank[i] = rank[i-1];
            cout << rank[i] << ' ' << teams[i].name << ' ' << teams[i].nAc << ' ' << teams[i].penalty << endl;
        }
    }
    return 0;
}
