#include <bits/stdc++.h>
using namespace std;

const int MN = 100111;
pair<int,int> a[MN];
int n;

int main() {
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> a[i].first >> a[i].second;
    
    sort(a, a+n);
    
    bool ok = false;
    for(int i = 1; i < n; ++i) {
        if (a[i].second < a[i-1].second) {
            cout << "Happy Alex" << endl;
            ok = true;
            break;
        }
    }
    if (!ok) cout << "Poor Alex" << endl;
}
