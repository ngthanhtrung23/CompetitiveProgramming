
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

int money;
int bound;
int nDrink;

int floatToInt(double x) {
    return (int) (x*100 + 1e-3);
}

struct Drink {
    string name;
    int strength;
    int value;
    int cost;
    int buy;

    void read() {
        cin >> name;
        cin >> strength;
        string t; cin >> t;
        if (t == "1/1") value = 6;
        else if (t == "1/2") value = 3;
        else if (t == "1/3") value = 2;

        value *= strength * 10;

        double x; cin >> x;
        cost = floatToInt(x);

        buy = 0;
    }
} drink[11];

int f[1011][1211];

int main() {
    ios :: sync_with_stdio(false);
    double m, b;
    while (cin >> m >> b >> nDrink) {
        bound = floatToInt(b) * 6 / 10;
        money = floatToInt(m);
        FOR(i,1,nDrink) drink[i].read();

        memset(f, -1, sizeof f);
        queue<int> qu;
        queue<int> qv;

        qu.push(0); qv.push(0);
        f[0][0] = 0;

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            int v = qv.front(); qv.pop();

            FOR(i,1,nDrink) {
                int uu = u + drink[i].cost;
                int vv = v + drink[i].value;

                if (uu <= money && vv <= bound && f[uu][vv] < 0) {
                    f[uu][vv] = i;
                    qu.push(uu);
                    qv.push(vv);
                }
            }
        }
        if (f[money][bound] < 0) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            while (money || bound) {
                int d = f[money][bound];
                drink[d].buy++;
                money -= drink[d].cost;
                bound -= drink[d].value;
            }
            FOR(i,1,nDrink)
                if (drink[i].buy)
                    cout << drink[i].name << ' ' << drink[i].buy << '\n';
        }
    }
}
