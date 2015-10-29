
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

string prog;
vector<ll> func[2011];
vector<string> func_names[2011];

void read() {
    string t;
    while (cin >> t) {
        prog += ' ';
        for(char c : t) {
            if (c == '{' || c == '}' || c == ';') {
                prog += ' ';
                prog += c;
                prog += ' ';
            }
            else prog += c;
        }
    }
//    DEBUG(prog);
}

int nFunc;
vector<string> commands[2011];
map< vector<ll>, int > funcId;

#define hash hash__
ll hash(const string& s) {
    ll res = 0;
    for(char c : s)
        res = res * 301 + c;
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("polymorphism.in", "r", stdin);
    freopen("polymorphism.out","w", stdout);

    read();
    string t;
    stringstream ss(prog);
    vector<ll> cur;
    vector<string> cur_name;
    int cur_func = 0;
    while (ss >> t) {
        if (t == "namespace") {
            ss >> t; // name
            cur.push_back(hash(t));
            cur_name.push_back(t);
            ss >> t; // {
        }
        else if (t == "function") {
            ss >> t; // name
            cur.push_back(hash(t));
            cur_name.push_back(t);
            ++nFunc;
            func[nFunc] = cur;
            func_names[nFunc] = cur_name;

            cur_func = nFunc;

            funcId[cur] = nFunc;
            ss >> t; // {
        }
        else if (t == "}") {
            cur.pop_back();
            cur_name.pop_back();
            cur_func = 0;
        }
        else {
            commands[cur_func].push_back(t);
            ss >> t; //;
        }
    }
    FOR(i,1,nFunc) {
        cout << '[' << i << "] ";
        REP(j,SZ(func_names[i])) {
            cout << func_names[i][j];
            if (j < SZ(func_names[i]) - 1) cout << '.';
            else cout << '\n';
        }

        for(auto s : commands[i]) {
            string comm = s;
            REP(i,SZ(s))
                if (comm[i] == '.') comm[i] = ' ';
            stringstream ss(comm);

            string t;
            vector<ll> cur = func[i]; cur.pop_back();
            vector<ll> add;
            while (ss >> t) {
                add.push_back(hash(t));
            }
            bool ok = false;
            while (true) {
                vector<ll> t = cur; t.insert(t.end(), add.begin(), add.end());
                if (funcId.count(t)) {
                    cout << "  (" << funcId[t] << ")\n";
                    ok = true;
                    break;
                }
                if (cur.empty()) break;
                cur.pop_back();
            }
            if (!ok) cout << "  (ERROR)\n";
        }
    }
}

