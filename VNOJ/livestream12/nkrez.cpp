#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 30111;
pair<int,int> events[MN];

vector<int> endAt[MN];  // endAt[i] = yeu cau ket thuc tai i
int f[MN]; // f(t)

int32_t main() {
    ios::sync_with_stdio(0);
    int nEvent; cin >> nEvent;
    for (int i = 1; i <= nEvent; i++) {
        cin >> events[i].first >> events[i].second;
        endAt[events[i].second].push_back(i);
    }

    for (int t = 1; t <= 30000; t++) {
        f[t] = f[t - 1];
        for (int id : endAt[t]) {
            f[t] = max(f[t],
                    f[events[id].first]
                    + events[id].second - events[id].first);
        }
    }
    cout << f[30000] << endl;
    return 0;
}
