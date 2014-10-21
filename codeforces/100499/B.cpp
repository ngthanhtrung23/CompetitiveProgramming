#include <iostream>
#include <cstring>
using namespace std;

const int MN = 10111000;

int N, cnt[MN];
long long S, C1, C2, M;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);

    int test; cin >> test;
    while (test--) {
        int K;
        cin >> N >> K >> S >> C1 >> C2 >> M;

        memset(cnt, 0, sizeof cnt);
        long long A = 0;
        for(int i = 1; i <= N; ++i) {
            if (i == 1) {
                A = S;
            } else {
                A = (C1 * A + C2) % M;
            }
            ++cnt[A];
        }

        for(int i = 0; i < MN; ++i) {
            if (K <= 0) break;

            int cur = min(K, cnt[i]);
            K -= cur;
            while (cur--) {
                cout << i << ' ';
            }
        }
        cout << endl;
    }
}
