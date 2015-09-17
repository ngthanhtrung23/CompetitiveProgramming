
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

static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

const int MN = 211;
char tmp[100111];

int nItems;
struct Item {
    string name;
} items[MN];


bool changed;
set<int> cur_items;
vector<string> res;

int nChars;
struct Char {
    string name;
    vector<int> need;
    vector<int> give;

    bool can() {
        for(int it : need) {
            if (!cur_items.count(it)) return false;
        }
        return true;
    }

    void talk() {
        stringstream ss; ss << "talk to " << name;
        res.push_back(ss.str());

        stringstream ss1; ss1 << "give ";
        REP(id,SZ(need)) {
            int x = need[id];

            if (id == 0) {}
            else if (id < SZ(need)-1) ss1 << ", ";
            else ss1 << " and ";
            ss1 << ::items[x].name;

            cur_items.erase(x);
            changed = true;
        }
        ss1 << " to " << name;
        res.push_back(ss1.str());

        stringstream ss2; ss2 << "take ";
        REP(id,SZ(give)) {
            int x = give[id];

            if (id == 0) {}
            else if (id < SZ(give)-1) ss2 << ", ";
            else ss2 << " and ";
            ss2 << ::items[x].name;

            cur_items.insert(x);
            changed = true;
        }
        ss2 << " from " << name;
        res.push_back(ss2.str());
    }
} chars[MN];

int nObjs;
struct Obj {
    string name;
    vector<int> need;
    vector<int> give;

    bool can() {
        for(int it : need) {
            if (!cur_items.count(it)) return false;
        }
        return true;
    }

    void talk() {
        stringstream ss1;
        ss1 << "use ";

        REP(id,SZ(need)) {
            int x = need[id];
            if (id == 0) {}
            else if (id < SZ(need)-1) ss1 << ", ";
            else ss1 << " and ";
            ss1 << ::items[x].name;
        }
        ss1 << " on " << name;
        res.push_back(ss1.str());

        stringstream ss2;
        ss2 << "take ";
        REP(id,SZ(give)) {
            int x = give[id];

            if (id == 0) {}
            else if (id < SZ(give)-1) ss2 << ", ";
            else ss2 << " and ";
            ss2 << ::items[x].name;

            cur_items.insert(x);
            changed = true;
        }
        ss2 << " from " << name;
        res.push_back(ss2.str());
    }
} objs[MN];

int nDoor;
struct Door {
    int from, to;
    int key;
    bool opened;
} doors[MN];

map<string,int> idRoom, idDoor, idItem, idChar, idObj;

int getItem(string s) {
    if (idItem.count(s)) {
        return idItem[s];
    }
    ++nItems;
    items[nItems].name = s;
    return idItem[s] = nItems;
}

int getChar(string s) {
    if (idChar.count(s)) return idChar[s];

    ++nChars;
    chars[nChars].name = s;

    gets(tmp);
    istringstream ss1(tmp);
    string token;
    while (getline(ss1, token, ',')) {
        chars[nChars].need.push_back(getItem(trim(token)));
    }

    gets(tmp);
    istringstream ss2(tmp);
    while (getline(ss2, token, ',')) {
        chars[nChars].give.push_back(getItem(trim(token)));
    }
    return idChar[s] = nChars;
}

int getObj(string s) {
    if (idObj.count(s)) return idObj[s];

    ++nObjs;
    objs[nObjs].name = s;

    gets(tmp);
    istringstream ss1(tmp);
    string token;
    while (getline(ss1, token, ',')) {
        objs[nObjs].need.push_back(getItem(trim(token)));
    }

    gets(tmp);
    istringstream ss2(tmp);
    while (getline(ss2, token, ',')) {
        objs[nObjs].give.push_back(getItem(trim(token)));
    }

    return idObj[s] = nObjs;
}

int nRoom;
struct Room {
    string name;
    vector<int> ke; // opened door only
    vector<int> doors;

    set<int> chars;
    set<int> objs;
    set<int> items;

    void visit() {
        // take all items
        for(int x : items) {
            stringstream ss; ss << "pick " << ::items[x].name;
            res.push_back(ss.str());

            cur_items.insert(x);
            changed = true;
        }
        items.clear();

        // talk to all possible chars
        set<int> t;
        for(int x : chars) if (::chars[x].can()) {
            t.insert(x);
        }
        for(int x : t) {
            chars.erase(x);
            ::chars[x].talk();
        }
        t.clear();

        // use all objects
        for(int x : objs) if (::objs[x].can()) {
            t.insert(x);
        }
        for(int x : t) {
            objs.erase(x);
            ::objs[x].talk();
        }
    }

    void go_to() {
        stringstream ss; ss << "go to " << name;
        res.push_back(ss.str());
    }

    void print() {
        cout << "Room: " << name << endl;
        for(int x : chars) cout << ::chars[x].name << ' '; cout << endl;
        for(int x : objs) cout << ::objs[x].name << ' '; cout << endl;
        for(int x : items) cout << ::items[x].name << ' '; cout << endl;
    }
} rooms[MN];

void init() {
    idRoom.clear(); idDoor.clear(); idItem.clear(); idChar.clear(); idObj.clear();
    res.clear();
    cur_items.clear();
    nItems = nChars = nObjs = 0;

    REP(i,MN) {
        rooms[i].ke.clear();
        rooms[i].doors.clear();
    }
}

bool win;
int target;
bool visited[MN];
vector< pair<int,int> > temp_edges;

void dfs(int u) {
    visited[u] = true;
    if (win) return ;

    if (u == target) {
        win = true;
        res.push_back("save princess");
        return ;
    }

    rooms[u].visit();

    for(int door_id : rooms[u].doors) {
        if (!doors[door_id].opened && cur_items.count(doors[door_id].key)) {
            doors[door_id].opened = true;

            int v = (doors[door_id].from == u) ? doors[door_id].to : doors[door_id].from;

            stringstream ss; ss << "open door to " << rooms[v].name;
            res.push_back(ss.str());

            temp_edges.push_back(make_pair(u, v));
        }
    }

    for(int v : rooms[u].ke) if (!visited[v]) {
        rooms[v].go_to();
        dfs(v);
        if (win) return ;
        rooms[u].go_to();
    }
}

bool solve(int start, int target) {
    int u = start;
    ::target = target;
    win = false;
    while (!win) {
        memset(visited, 0, sizeof visited);
        changed = false;

        temp_edges.clear();
        dfs(u);
//        cout << "---------------------" << endl;
//        for(string s : res) cout << s << endl;
//        cout << "STATE: " << endl;
//        cout << "items = "; for(int x : cur_items) cout << items[x].name << ' '; cout << endl;

        if (!temp_edges.empty()) {
            for(auto p : temp_edges) {
                int u = p.first, v = p.second;
                rooms[u].ke.push_back(v);
                rooms[v].ke.push_back(u);
            }
        }
        else if (!changed) break;
    }
    return win;
}

int main() {
    freopen("quest.in", "r", stdin);
    freopen("quest.out", "w", stdout);
    while (scanf("%d\n", &nRoom) == 1) {
        init();
        FOR(i,1,nRoom) {
            gets(tmp);
            rooms[i].name = string(tmp);
            idRoom[ rooms[i].name ] = i;
        }

        scanf("%d\n", &nDoor);
        FOR(i,1,nDoor) {
            scanf("%d %d ", &doors[i].from, &doors[i].to);

            rooms[ doors[i].from ].doors.push_back(i);
            rooms[ doors[i].to   ].doors.push_back(i);
            gets(tmp);
            doors[i].key = getItem(string(tmp));

            doors[i].opened = false;
        }
//        DEBUG(nDoor);

        FOR(i,1,nRoom) {
            int c, o, t;
            scanf("%d %d %d\n", &c, &o, &t);
            while (c--) {
                gets(tmp);
                rooms[i].chars.insert(getChar(string(tmp)));
            }
            while (o--) {
                gets(tmp);
                rooms[i].objs.insert(getObj(string(tmp)));
            }
            while (t--) {
                gets(tmp);
                rooms[i].items.insert(getItem(string(tmp)));
            }
        }

//        FOR(i,1,nRoom) rooms[i].print();

        gets(tmp); int start = idRoom[string(tmp)];
        gets(tmp); int target = idRoom[string(tmp)];

        if (solve(start, target)) {
            for(string s : res) puts(s.c_str());
        }
        else {
            puts("dead princess");
        }
    }
}

