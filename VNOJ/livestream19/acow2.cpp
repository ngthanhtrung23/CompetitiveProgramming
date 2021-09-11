#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int nPaper, n; cin >> nPaper >> n;
    map<string, int> id;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        id[s] = i;
    }

    vector<vector<char>> res(n, vector<char> (n, '?'));
    for (int i = 0; i < n; i++) {
        res[i][i] = 'B';
    }

    while (nPaper--) {
        vector<string> cur(n);
        for (auto& name : cur) cin >> name;
        vector<int> group(n);
        int curGroup = 0;

        for (int i = 0; i < n; i++) {
            if (i == 0 || cur[i] < cur[i-1]) {
                curGroup++;
            }
            group[i] = curGroup;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (group[i] != group[j]) {
                    res[id[cur[j]]][id[cur[i]]] = '1';
                    res[id[cur[i]]][id[cur[j]]] = '0';
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (char) res[i][j];
        }
        cout << endl;
    }
    return 0;
}
