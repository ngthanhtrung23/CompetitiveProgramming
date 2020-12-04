// Brute force with priority (number of options, length covered)

#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

int rand16() {
    return rand() & (TWO(16) - 1);
}
int my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

char a[15][15], orig[15][15];
int m, n;

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

void attempt(int depth) {
    // Find cell with min number of possible option (1 option = 1 number that can extend to this cell).
    // Break tie by length of extension.
    int savei = -1, savej = -1;

    {
        const int MAX = 99;
        int minOptions = MAX;
        int maxExtension = 0;

        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
            int options = 0;
            int extension = MAX;
            int need;

            // up
            need = 1;
            FORD(ii,i-1,1) {
                char cur = a[ii][j];
                if (is_digit(cur)) {
                    int val = cur - '0';
                    if (val >= need) {
                        ++options;
                        extension = min(extension, need);
                    }
                    break;
                }
                if (cur == '.') ++need;
                if (cur != '.' &&  cur != 'v') break;
            }
            // down
            need = 1;
            FOR(ii,i+1,m) {
                char cur = a[ii][j];
                if (is_digit(cur)) {
                    int val = cur - '0';
                    if (val >= need) {
                        ++options;
                        extension = min(extension, need);
                    }
                    break;
                }
                if (cur == '.') ++need;
                if (cur != '.' && cur != '^') break;
            }
            // left
            need = 1;
            FORD(jj,j-1,1) {
                char cur = a[i][jj];
                if (is_digit(cur)) {
                    int val = cur - '0';
                    if (val >= need) {
                        ++options;
                        extension = min(extension, need);
                    }
                    break;
                }
                if (cur == '.') ++need;
                if (cur != '.' && cur != '>') break;
            }
            // right
            need = 1;
            FOR(jj,j+1,n) {
                char cur = a[i][jj];
                if (is_digit(cur)) {
                    int val = cur - '0';
                    if (val >= need) {
                        ++options;
                        extension = min(extension, need);
                    }
                    break;
                }
                if (cur == '.') ++need;
                if (cur != '.' && cur != '<') break;
            }

            if (options < minOptions
                    || (options == minOptions && extension > maxExtension)) {
                savei = i;
                savej = j;
                minOptions = options;
                maxExtension = extension;
            }
        }
        if (minOptions == 0) {
            // Sadly no solution in this branch.
            return;
        }

        if (minOptions == MAX) {
            // OMG we found answer.
            throw 1;
        }
//        cout << depth << ": " << minOptions << " --> " << savei << ' ' << savej << endl;

    }

    int i = savei, j = savej;
    char save[15][15];
    int need;
    // up
    need = 1;
    FORD(ii,i-1,1) {
        char cur = a[ii][j];
        if (is_digit(cur)) {
            int val = cur - '0';
            if (val >= need) {
                FOR(x,ii,i) {
                    save[x][j] = a[x][j];
                    if (x == ii) a[x][j] -= need;
                    else a[x][j] = 'v';
                }
                attempt(depth + 1);
                FOR(x,ii,i) a[x][j] = save[x][j];
            }
            break;
        }
        if (cur == '.') ++need;
        if (cur != '.' &&  cur != 'v') break;
    }
    // down
    need = 1;
    FOR(ii,i+1,m) {
        char cur = a[ii][j];
        if (is_digit(cur)) {
            int val = cur - '0';
            if (val >= need) {
                FORD(x,ii,i) {
                    save[x][j] = a[x][j];
                    if (x == ii) a[x][j] -= need;
                    else a[x][j] = '^';
                }
                attempt(depth + 1);
                FORD(x,ii,i) a[x][j] = save[x][j];
            }
            break;
        }
        if (cur == '.') ++need;
        if (cur != '.' && cur != '^') break;
    }
    // left
    need = 1;
    FORD(jj,j-1,1) {
        char cur = a[i][jj];
        if (is_digit(cur)) {
            int val = cur - '0';
            if (val >= need) {
                FOR(x,jj,j) {
                    save[i][x] = a[i][x];
                    if (x == jj) a[i][x] -= need;
                    else a[i][x] = '>';
                }
                attempt(depth + 1);
                FOR(x,jj,j) a[i][x] = save[i][x];
            }
            break;
        }
        if (cur == '.') ++need;
        if (cur != '.' && cur != '>') break;
    }
    // right
    need = 1;
    FOR(jj,j+1,n) {
        char cur = a[i][jj];
        if (is_digit(cur)) {
            int val = cur - '0';
            if (val >= need) {
                FOR(x,j,jj) {
                    save[i][x] = a[i][x];
                    if (x == jj) a[i][x] -= need;
                    else a[i][x] = '<';
                }
                attempt(depth + 1);
                FOR(x,j,jj) a[i][x] = save[i][x];
            }
            break;
        }
        if (cur == '.') ++need;
        if (cur != '.' && cur != '<') break;
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    cin >> m >> n;
    FOR(i,1,m) FOR(j,1,n) {
        cin >> a[i][j];
        orig[i][j] = a[i][j];
    }
    try {
        attempt(0);
        
        cout << "NO SOLUTION" << endl;
    } catch (...) {
        FOR(i,1,m) {
            FOR(j,1,n) {
                if (is_digit(a[i][j])) assert(a[i][j] == '0');

                if (a[i][j] == '0') cout << orig[i][j];
                else cout << a[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}
