#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

pair<string,int> a[2][22];

pair<int,int> better(pair<int,int> a, pair<int,int> b, int who) {
    if (a.first == 3) a.first = who;
    if (b.first == 3) b.first = who;

    if (a.first == who && b.first == who) return make_pair(who, min(a.second, b.second));
    if (a.first != who && b.first != who) return make_pair(1-who, max(a.second, b.second));
    if (a.first == who) return a;
    else return b;
}

map<int, pair<int,int> > cache;
pair<int,int> get(int who, int can_use, int hp[2], int atk[2], int def[2]) {
    int h = def[0] + def[1]*6 + atk[0]*36 + atk[1]*216 + hp[0]*1296 + hp[1]*12960 + who*129600 + can_use*1296000;
    if (cache.count(h)) return cache[h];

    if (can_use == 11) {
        return cache[h] = make_pair(3, 13);
    }
    int can_heal = -1, can_atk = -1, can_def = -1, can_hit = 0;
    FOR(i,1,can_use) {
        auto cur = a[who][i];
        if (cur.first[1] == 'I') can_hit = 1;
        else if (cur.first[0] == 'A') can_atk = max(can_atk, cur.second);
        else if (cur.first[0] == 'D') can_def = max(can_def, cur.second);
        else can_heal = max(can_heal, cur.second);
    }

    int new_hp[2] = {hp[0], hp[1]};
    int new_atk[2] = {atk[0], atk[1]};
    int new_def[2] = {def[0], def[1]};

    pair<int,int> best = make_pair(1-who, -1);
    if (can_hit) {
        int dam = max(0, atk[who] - def[1-who]);
        if (dam >= hp[1-who]) return cache[h] = make_pair(who, (can_use - 4) * 2 - 1 + who);
        
        new_hp[1-who] -= dam;
        if (dam) best = better(best, get(1-who, can_use + who, new_hp, new_atk, new_def), who);
        new_hp[1-who] += dam;
    }
    if (can_heal > 0) {
        new_hp[who] = min(hp[who] + can_heal, 10);
        best = better(best, get(1-who, can_use + who, new_hp, new_atk, new_def), who);
        new_hp[who] = hp[who];
    }
    if (can_atk > atk[who]) {
        new_atk[who] = max(atk[who], can_atk);
        best = better(best, get(1-who, can_use + who, new_hp, new_atk, new_def), who);
        new_atk[who] = atk[who];
    }
    if (can_def > def[who]) {
        new_def[who] = max(def[who], can_def);
        best = better(best, get(1-who, can_use + who, new_hp, new_atk, new_def), who);
        new_def[who] = def[who];
    }
    best = better(best, get(1-who, can_use + who, hp, atk, def), who);
    return cache[h] = best;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        REP(turn,2) {
            FOR(i,1,10) {
                cin >> a[turn][i].first;
                if (a[turn][i].first != "HIT!") cin >> a[turn][i].second;
            }
        }
        cache.clear();
        int hp[2] = {10, 10};
        int atk[2] = {0, 0};
        int def[2] = {0, 0};
        cout << "Case #" << test << ": ";
        pair<int,int> res = get(0, 5, hp, atk, def);
        if (res.first == 0) cout << "win "; else cout << "lose ";
        cout << res.second << endl;
    }
    return 0;
}
