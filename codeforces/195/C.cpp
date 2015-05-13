
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

string s[100111];
char tmp[100111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (scanf("%d\n", &n) == 1) {
        FOR(i,1,n) {
            gets(tmp);
            s[i] = string(tmp);
        }
        stack< pair<string,string> > st;
        FORD(i,n,1) {
            REP(t,s[i].length()) {
                if (s[i][t] == '(' || s[i][t] == ')' || s[i][t] == ',') s[i][t] = ' ';
            }
            istringstream ss(s[i]);

            string command; ss >> command;
            if (command == "try") {
                st.pop();
            }
            else if (command == "throw") {
                string typ; ss >> typ;
                while (!st.empty() && st.top().first != typ) {
                    st.pop();
                }
                if (st.empty()) puts("Unhandled Exception");
                else puts(st.top().second.c_str());
                break;
            }
            else if (command == "catch") {
                string typ; ss >> typ;
                string msg = "";
                bool need = false;
                REP(t,s[i].length()) {
                    if (s[i][t] == '"') need = !need;
                    else {
                        if (need) msg += s[i][t];
                    }
                }
                st.push(make_pair(typ, msg));
            }
        }
    }
    return 0;
}
