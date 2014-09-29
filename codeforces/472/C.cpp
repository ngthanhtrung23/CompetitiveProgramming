#include <iostream>
#include <string>
#include <algorithm>
#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i) 
using namespace std;

const int MN = 100111;
pair<string,string> a[MN];
int p[MN];

int main() {
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i].first >> a[i].second;
        FOR(i,1,n) cin >> p[i];

        string now = "";
        bool ok = true;
        FOR(turn,1,n) {
            string x = a[p[turn]].first, y = a[p[turn]].second;
            if (x > y) swap(x, y);

            if (x >= now) now = x;
            else if (y >= now) now = y;
            else {
                ok = false;
                cout << "NO" << endl;
                break;
            }
        }
        if (ok) cout << "YES" << endl;
    }
}
