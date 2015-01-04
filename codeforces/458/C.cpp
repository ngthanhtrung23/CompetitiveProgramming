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

int a[MN], b[MN], currentVote, cnt[MN];
vector<int> cost[MN], sumCost[MN], ls[MN];

int f(int votes) {
    memset(cnt, 0, sizeof cnt);

    int res = 0, needToBuy = votes - currentVote;
    FOR(nVote,1,100000) {
        // If opponent has nVote, then we need to buy:
        int need = nVote - votes + 1;
        if (need < 0) need = 0;

        for(int opponentId : ls[nVote]) {
            // We buy the necessary votes
            if (need > 0) res += sumCost[opponentId][need-1];
            needToBuy -= need;

            // And then put the rest of the votes into our DS
            FOR(x,need,cost[opponentId].size()-1)
                cnt[cost[opponentId][x]]++;
        }
    }
    if (needToBuy < 0) needToBuy = 0;
    FOR(value,0,10000) {
        int now = min(cnt[value], needToBuy);
        needToBuy -= now;
        res += now * value;
    }
    if (needToBuy) return 1000111000;
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        FOR(i,1,100000) {
            cost[i].clear();
            sumCost[i].clear();
            ls[i].clear();
        }

        currentVote = 0;
        FOR(i,1,n) {
            cin >> a[i] >> b[i];
            if (!a[i]) currentVote++;
            else {
                cost[a[i]].push_back(b[i]);
            }
        }

        FOR(i,1,100000)
            if (!cost[i].empty()) {
                sort(cost[i].begin(), cost[i].end());
                ls[cost[i].size()].push_back(i);

//                PR0(cost[i], cost[i].size());
                sumCost[i].resize(cost[i].size());

                sumCost[i][0] = cost[i][0];
                FOR(x,1,cost[i].size()-1)
                    sumCost[i][x] = sumCost[i][x-1] + cost[i][x];

//                PR0(sumCost[i], sumCost[i].size());
            }

        int l = max(currentVote,1), r = n, best = min(f(l), f(r));
        REP(turn,100) {
            int x1 = (l + l + r) / 3;
            int x2 = (l + r + r) / 3;
            int y1 = f(x1), y2 = f(x2);
            best = min(best, min(y1, y2));

            if (y1 < y2) r = x2;
            else l = x1;
        }
        cout << best << endl;
    }
    return 0;
}
