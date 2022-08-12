// Compare 2 numbers in base 3
// -> basic implementation uses 8*4 = 32 states (48.5 points)
//    where 8 = number of digits (3**8 > 5000)
//          4 states for each digit:
//            0 -> read A
//            1, 2, 3 -> already read A (state store 1 + A's digit) & read B
// 
// To improve, notice that we don't need state 0. Instead when we know 2 digits
// are equal, read next digit and store it. (thus we will read 2 numbers
// alternatively).
// -> 1 + 8*3 = 25 state (65 points)
//
// For last digit, if it's either 0 or 2, we already know which number is smaller
// -> handle last digit manually and remove 2 states
// -> 2 + 7*3 = 23 states (80 points)
//
// Similarly, we can handle last 2 digits manually
// -> 22 states (90 points)

#include "debug.h"

#include "bits/stdc++.h"
using namespace std;
 
int p3[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561};
 
// base 3
int get_bit(int n, int bit) {
    return (n % p3[bit + 1]) / p3[bit];
}
 
const int NBIT = 8;  // 3**8 > 5000

int encode(int b, int t) {
    if (b < 0) return 0;
    return 1 + (NBIT - b - 1) * 3 + t;
}
 
std::vector<std::vector<int>> devise_strategy(int n) {
    const int NSTATE = 22;
    std::vector<std::vector<int>> res(NSTATE, std::vector<int> (n+1, 0));

    // 0
    {
        res[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            int t = get_bit(i, NBIT - 1);
            res[0][i] = encode(NBIT - 1, t);
        }
    }

    // compare each digit in base 3
    for (int bit = NBIT - 1; bit >= 1; --bit) {
        for (int t = 0; t < 3; ++t) {
            int state = encode(bit, t);

            // 7 -> read 1
            // 6 -> read 0
            int cur = bit % 2;
            int last = 1 - cur;

            res[state][0] = cur;

            for (int i = 1; i <= n; ++i) {
                int cur_bit = get_bit(i, bit);
                if (t < cur_bit) res[state][i] = -1 - last;
                else if (t > cur_bit) res[state][i] = -1 - cur;
                else {
                    // 2 digits are equal -> we continue to next digit
                    // to improve, we read next digit of current number and store it directly
                    // (alternating 2 numbers)
                    if (bit > 2) res[state][i] = encode(bit - 1, get_bit(i, bit - 1));
                    else {
                        // for last 2 digits, manual casework
                        int r = i % 9;
                        if (r == 0) res[state][i] = -1 - cur;
                        else if (r == 8) res[state][i] = -1 - last;
                        else if (r <= 4) res[state][i] = 19;  // 1 2 3 4
                        else res[state][i] = 20;              // 5 6 7
                    }
                }
            }
        }
    }

    // 19, 20
    for (int state : {19, 20}) {
        int cur = 1, last = 0;
        res[state][0] = cur;

        for (int i = 1; i <= n; ++i) {
            // last 2 digits
            int r = i % 9;
            if (r == 0) res[state][i] = -1 - cur;
            else if (r == 8) res[state][i] = -1 - last;
            else if (state == 19) {
                if (r == 1) res[state][i] = -1 - cur;
                else if (r >= 4) res[state][i] = -1 - last;
                else res[state][i] = 21;
            } else {
                // state == 20
                if (r <= 5) res[state][i] = -1 - cur;
                else if (r == 7) res[state][i] = -1 - last;
                else res[state][i] = 21;
            }
        }
    }

    // 21
    {
        int cur = 0, last = 1;
        res[21][0] = cur;

        for (int i = 1; i <= n; ++i) {
            int r = i % 9;
            if (r <= 4) {
                if (r <= 2) res[21][i] = -1 - cur;
                else res[21][i] = -1 - last;
            } else {
                if (r <= 6) res[21][i] = -1 - cur;
                else res[21][i] = -1 - last;
            }
        }
    }
 
    return res;
}

int main() {
    auto res = devise_strategy(3);
    DEBUG(res);
    return 0;
}
