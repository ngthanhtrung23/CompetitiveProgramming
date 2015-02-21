
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
using namespace std;

const int HBOX = 1;
const int VBOX = 2;
const int WIDGET = 3;

struct Widget {
    vector<int> children;
    ll border, spacing;
    ll x, y;
    int typ;
    int finalized;

    Widget(int typ = 0, ll x = 0, ll y = 0) : typ(typ), x(x), y(y) {
        border = spacing = 0;
        children.clear();
        finalized = 0;

        if (typ == WIDGET) finalized = 1;
    }

    pair<ll,ll> getSize();
} widgets[111];
map<string,int> id;

pair<ll,ll> Widget::getSize() {
    if (finalized) {
        return make_pair(x, y);
    }

    if (children.empty()) {
        x = 0;
        y = 0;
    }
    else {
        x = y = 0;

        for(auto id : children) {
            auto child_size = widgets[id].getSize();

            if (typ == HBOX) {
                x += child_size.first;
                y = max(y, child_size.second);
            }
            else {
                x = max(x, child_size.first);
                y += child_size.second;
            }
        }

        if (typ == HBOX) x += spacing * ((int)children.size() - 1);
        else y += spacing * ((int) children.size() - 1);

        x += 2 * border;
        y += 2 * border;
    }

    finalized = 1;
    return make_pair(x, y);
}


string instructions[111];
char tmp[100111];

int main() {
    int n;
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) {
            gets(tmp);
            REP(t,strlen(tmp))
                if (tmp[t] == '(' || tmp[t] == ')' || tmp[t] == ',' || tmp[t] == '.')
                    tmp[t] = ' ';
            instructions[i] = string(tmp);
        }
        int nId = 0;
        id.clear();

        FOR(i,1,n) {
            istringstream ss(instructions[i].c_str());
            string req;
            ss >> req;
            if (req == "Widget" || req == "VBox" || req == "HBox") {
                string name; ss >> name;
                id[name] = ++nId;
            }
        }

//        for(auto p : id) cout << p.first << ' ' << p.second << endl;
        FOR(i,1,n) {
            istringstream ss(instructions[i].c_str());
            string req; ss >> req;

            if (req == "Widget") {
                string name; int x, y; ss >> name >> x >> y;
                int u = id[name];

                widgets[u] = Widget(WIDGET, x, y);
            }
            else if (req == "HBox") {
                string name; ss >> name;
                int u = id[name];
                widgets[u] = Widget(HBOX);
            }
            else if (req == "VBox") {
                string name; ss >> name;
                int u = id[name];
                widgets[u] = Widget(VBOX);
            }
            else {
                string name = req;
                ss >> req;
                if (req == "pack") {
                    string child_name; ss >> child_name;
                    widgets[ id[name] ].children.push_back( id[child_name] );
                }
                else if (req == "set_border") {
                    int value; ss >> value;
                    widgets[ id[name] ].border = value;
                }
                else if (req == "set_spacing") {
                    int value; ss >> value;
                    widgets[ id[name] ].spacing = value;
                }
                else {
                    cout << "UNKNOWN instructions: " << instructions[i] << endl;
                }
            }
        }
        for(auto p : id) {
            auto res = widgets[p.second].getSize();
            cout << p.first.c_str() << ' ' << res.first << ' ' << res.second << '\n';
        }
    }
    return 0;
}
