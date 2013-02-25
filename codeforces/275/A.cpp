#include <iostream>
using namespace std;

int a[10][10];

int main() {
    for(int i = 1; i <= 3; ++i)
        for(int j = 1; j <= 3; ++j) {
            int t; cin >> t;
            if (t % 2) {
                a[i][j] = 1 - a[i][j];
                for(int di = -1; di <= 1; ++di)
                    for(int dj = -1; dj <= 1; ++dj)
                        if (di*di + dj*dj == 1)
                            a[i+di][j-dj] = 1 - a[i+di][j-dj];
            }
        }

    for(int i = 1; i <= 3; ++i) {
        for(int j = 1; j <= 3; ++j)
            cout << 1 - a[i][j];
        cout << endl;
    }
    return 0;
}
