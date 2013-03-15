#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#define MP make_pair
#define PB push_back
#include<cstdio>

using namespace std;

char a[1000111], b[1000111];

int main() {
    gets(a);
    gets(b);
    if (strlen(a) != strlen(b)) {
        cout << "NO"; return 0;
    }
    if (strcmp(a, b) == 0) {
        cout << "YES"; return 0;
    }
    if (strlen(a) == 1) {
        cout << "NO"; return 0;
    }
    bool check = false;
    for(int i=0; i<strlen(a); i++)
        if (a[i] == '1') {
            check = true; break;
        }
    if (!check) { cout << "NO"; return 0;}
    check = false;
    for(int i=0; i<strlen(a); i++)
        if (b[i] == '1') {
            check = true; break;
        }
    if (!check) { cout << "NO"; return 0;}
    
    cout << "YES";
    return 0;
}