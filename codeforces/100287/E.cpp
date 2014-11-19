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
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 10111;

struct Query {
    char typ;
    int u, prize;
} queries[MN];

struct buyCmp {
    bool operator () (int a, int b) {
        if (queries[a].prize != queries[b].prize)
            return queries[a].prize > queries[b].prize;
        return a < b;
    }
};

struct sellCmp {
    bool operator () (int a, int b) {
        if (queries[a].prize != queries[b].prize)
            return queries[a].prize < queries[b].prize;
        return a < b;
    }
};

int nQuery;
set<int, buyCmp> buyId;
set<int, sellCmp> sellId;
map<int,int> totalBuy, totalSell;

void init() {
    buyId.clear();
    sellId.clear();
    totalBuy.clear();
    totalSell.clear();
}

int main() {
    freopen("exchange.in", "r", stdin); freopen("exchange.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nQuery) {
        init();
        FOR(i,1,nQuery) {
            string tmp;
            cin >> queries[i].typ >> tmp;
            if (queries[i].typ == 'C') cin >> queries[i].u;
            else cin >> queries[i].u >> queries[i].prize;
        }

        FOR(i,1,nQuery) {
            if (queries[i].typ == 'C') {
                int id = queries[i].u;

                if (queries[id].u) {
                    if (queries[id].typ == 'B') {
                        buyId.erase(id);
                        totalBuy[ queries[id].prize ] -= queries[id].u;
                    }
                    else if (queries[id].typ == 'S') {
                        sellId.erase(id);
                        totalSell[ queries[id].prize ] -= queries[id].u;
                    }
                    queries[id].u = 0;
                }
            }
            else if (queries[i].typ == 'B') {
                while (!sellId.empty() && queries[i].prize >= queries[*sellId.begin()].prize) {
                    int sId = *sellId.begin();
                    sellId.erase(sellId.begin());

                    int can = min(queries[i].u, queries[sId].u);
                    cout << "TRADE " << can << ' ' << queries[sId].prize << "\n";
                    queries[i].u -= can;
                    queries[sId].u -= can;
                    totalSell[queries[sId].prize] -= can;
                    
                    if (queries[sId].u) sellId.insert(sId);
                    if (queries[i].u == 0) break;
                }

                if (queries[i].u) {
                    buyId.insert(i);
                    totalBuy[queries[i].prize] += queries[i].u;
                }
            }
            else if (queries[i].typ == 'S') {
                while (!buyId.empty() && queries[i].prize <= queries[*buyId.begin()].prize) {
                    int bId = *buyId.begin();
                    buyId.erase(buyId.begin());

                    int can = min(queries[i].u, queries[bId].u);
                    cout << "TRADE " << can << ' ' << queries[bId].prize << "\n";

                    queries[i].u -= can;
                    queries[bId].u -= can;
                    totalBuy[ queries[bId].prize ] -= can;

                    if (queries[bId].u) buyId.insert(bId);
                    if (queries[i].u == 0) break;
                }

                if (queries[i].u) {
                    sellId.insert(i);
                    totalSell[queries[i].prize] += queries[i].u;
                }
            }

            cout << "QUOTE ";
            if (buyId.empty()) cout << 0 << ' ' << 0;
            else cout << totalBuy[ queries[*buyId.begin()].prize ] << ' ' << queries[*buyId.begin()].prize;
            cout << " - ";

            if (sellId.empty()) cout << 0 << ' ' << 99999;
            else cout << totalSell[ queries[*sellId.begin()].prize ] << ' ' << queries[*sellId.begin()].prize;
            cout << "\n";
        }
    }
    return 0;
}
