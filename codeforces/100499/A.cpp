#include <iostream>
using namespace std;

string res[10] = {
    "-1",
    "-1",
    "-1",
    "1210 2020",
    "21200",
    "-1",
    "3211000",
    "42101000",
    "521001000",
    "6210001000"
};

int main() {
    int test; cin >> test;
    while (test--) {
        int k; cin >> k;
        cout << res[k - 1] << endl;
    }
}