#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);

int nEquip;
struct myEquip {
    string name;
    string type;
    int atk, def, res, size;
    vector<int> current, want;
} equip[111];

int nResident;
struct myResident {
    string name, type;
    int bonus;
    string location;
} resident[1011];

map<string, int> equipMap;

void print(int saveW, int saveA, int saveO) {
    cout << equip[saveW].name;
    int cnt = 0;
    FOR(i,1,nResident) if (resident[i].location == equip[saveW].name) cnt++;
    cout << ' ' << cnt;
    FOR(i,1,nResident) if (resident[i].location == equip[saveW].name)
        cout << ' ' << resident[i].name;
    puts("");
    
    cout << equip[saveA].name;
    cnt = 0;
    FOR(i,1,nResident) if (resident[i].location == equip[saveA].name) cnt++;
    cout << ' ' << cnt;
    FOR(i,1,nResident) if (resident[i].location == equip[saveA].name)
        cout << ' ' << resident[i].name;
    puts("");
    
    cout << equip[saveO].name;
    cnt = 0;
    FOR(i,1,nResident) if (resident[i].location == equip[saveO].name) cnt++;
    cout << ' ' << cnt;
    FOR(i,1,nResident) if (resident[i].location == equip[saveO].name)
        cout << ' ' << resident[i].name;
    puts("");
}

int index[1011], n;
bool mark[1011];

void init(string s) {
    n = 0;
    FOR(i,1,nResident)
//    if (!mark[i])
        if (resident[i].type == s) {
            index[++n] = i;
        }
    
    FOR(i,1,n-1)
    FOR(j,i+1,n)
        if (resident[index[i]].bonus > resident[index[j]].bonus) {
            swap(index[i], index[j]);
        }
}

bool contain(vector<int> a, int x) {
    REP(i,a.size())
        if (a[i] == x) return true;
    return false;
}

void match(vector<int> a, vector<int> b, int e) {
    int canAdd = a.size() - b.size();
    REP(x,a.size()) {
        if (contain(b, a[x])) continue;
        if (canAdd) {
            resident[a[x]].location = equip[e].name;
            canAdd--;
            continue;
        }
        REP(i, b.size())
            if (!contain(a, b[i]) && resident[b[i]].location == equip[e].name) {
                int u = a[x];
                int v = b[i];
//                cout << "swap : " << u << ' ' << v << endl;
                swap(resident[u].location, resident[v].location);
                break;
            }
    }
}

void initLocation() {
    FOR(i,1,nEquip) equip[i].current.clear();
    FOR(i,1,nResident) {
        int loc = equipMap[resident[i].location];
        equip[loc].current.PB(i);
    }
    FOR(i,1,nEquip) {
        sort(equip[i].current.begin(), equip[i].current.end());
    }
}

void solve() {
    initLocation();
    int saveW, bestW, saveA, bestA, saveO, bestO;
    saveW = bestW = saveA = bestA = saveO = bestO = -1;
    
    init("gladiator");
//    FOR(i,1,n) cout << index[i] << ' '; puts("");
    
    FOR(i,1,nEquip) if (equip[i].type == "weapon") {
        int now = equip[i].atk;
        for(int x = 0, god = n; x < equip[i].size && god >= 1; x++, god--) {
            now += resident[index[god]].bonus;
        }
        if (now > bestW) {
            bestW = now;
            saveW = i;
        }
    }
    for(int x = 0, god = n; x < equip[saveW].size && god >= 1; x++, god--) {
        equip[saveW].want.PB(index[god]);
        mark[index[god]] = true;
    }
    match(equip[saveW].want, equip[saveW].current, saveW);
    
    initLocation();
    init("sentry");
//    FOR(i,1,n) cout << index[i] << ' '; puts("");
    
    FOR(i,1,nEquip) if (equip[i].type == "armor") {
        int now = equip[i].def;
        for(int x = 0, god = n; x < equip[i].size && god >= 1; x++, god--) {
            now += resident[index[god]].bonus;
        }
        if (now > bestA) {
            bestA = now;
            saveA = i;
        }
    }
    for(int x = 0, god = n; x < equip[saveA].size && god >= 1; x++, god--) {
        equip[saveA].want.PB(index[god]);
        mark[index[god]] = true;
    }
    match(equip[saveA].want, equip[saveA].current, saveA);
    
    initLocation();
    init("physician");
//    FOR(i,1,n) cout << index[i] << ' '; puts("");
    FOR(i,1,nEquip) if (equip[i].type == "orb") {
        int now = equip[i].res;
        for(int x = 0, god = n; x < equip[i].size && god >= 1; x++, god--) {
            now += resident[index[god]].bonus;
        }
        if (now > bestO) {
            bestO = now;
            saveO = i;
        }
    }
    for(int x = 0, god = n; x < equip[saveO].size && god >= 1; x++, god--) {
        equip[saveO].want.PB(index[god]);
    }
    match(equip[saveO].want, equip[saveO].current, saveO);
    
    print(saveW, saveA, saveO);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> nEquip;
    FOR(i,1,nEquip) {
        cin >> equip[i].name >> equip[i].type 
            >> equip[i].atk >> equip[i].def >> equip[i].res >> equip[i].size;
    }
    cin >> nResident;
    FOR(i,1,nResident) {
        cin >> resident[i].name >> resident[i].type 
            >> resident[i].bonus >> resident[i].location;
    }
    FOR(i,1,nEquip) equipMap[equip[i].name] = i;
    
    int sumSize = 0;
    FOR(i,1,nEquip) sumSize += equip[i].size;
    
    if (sumSize == nResident) { // cannot move :(
        int saveW = -1, saveA = -1, saveO = -1;
        int bestW = -1, bestA = -1, bestO = -1;
        
        FOR(i,1,nEquip) if (equip[i].type == "weapon") {
            int nowW = equip[i].atk;
            FOR(j,1,nResident)
            if (resident[j].location == equip[i].name
                    && resident[j].type == "gladiator") {
                nowW += resident[j].bonus;
            }
            if (nowW > bestW) {
                bestW = nowW;
                saveW = i;
            }
        }
        
        FOR(i,1,nEquip) if (equip[i].type == "armor") {
            int now = equip[i].def;
            FOR(j,1,nResident)
            if (resident[j].location == equip[i].name
                    && resident[j].type == "sentry") {
                now += resident[j].bonus;
            }
            if (now > bestA) {
                bestA = now;
                saveA = i;
            }
        }
        
        FOR(i,1,nEquip) if (equip[i].type == "orb") {
            int now = equip[i].res;
            FOR(j,1,nResident)
            if (resident[j].location == equip[i].name
                    && resident[j].type == "physician") {
                now += resident[j].bonus;
            }
            if (now > bestO) {
                bestO = now;
                saveO = i;
            }
        }
        
        print(saveW, saveA, saveO);
    }
    else {
        solve();
    }
    return 0;
}
