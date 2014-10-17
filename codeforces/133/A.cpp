#include <iostream>
#include <string>
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        bool ok = false;
        REP(i,s.length()) if (s[i] == 'H' || s[i] == 'Q' || s[i] == '9') ok = true;
        cout << (ok ? "YES" : "NO") << endl;
    }
}
