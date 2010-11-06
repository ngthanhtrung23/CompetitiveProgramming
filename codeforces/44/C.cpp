#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

int cnt[111];

int main(){
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, m; 
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        for(int j = a; j <= b; j++)
            cnt[j]++;
    }
    bool ok = true;
    for(int i = 1; i <= n; i++)
        if (cnt[i] != 1) {
            cout << i << " " << cnt[i] << endl;
            ok = false;
            break;
        }
    if (ok) puts("OK");
    return 0;
}
