#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

vector <int> v;
int k, a, b;
char s[10000];

int main () {
    scanf ("%d%d%d", &k, &a, &b);
    scanf ("%s", s);
    int slen = strlen (s);
    int each = slen / k;
    for (int i = 0; i < k; i++) {
        v.push_back (each);
        slen -= each;
    }
    for (int i = 0; i < slen; i++)
        v[i]++;
    bool flag = true;
    for (int i = 0; i < v.size(); i++)
        if (v[i] < a || v[i] > b)
            flag = false;
    if (flag) {
        int x = 0;
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i]; j++)
                printf ("%c", s[x++]);
            puts ("");
        }
    } else puts ("No solution");
    return 0;
}
