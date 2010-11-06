#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(){
//    freopen("test.in","r",stdin);
//    freopen("test.out","w",stdout);
    int n; cin >> n;
    string a, b;
    set<pair<string, string> > s;
    for(int i = 0; i < n; i++) {
        cin >> a >> b;
        s.insert(make_pair(a,b));
    }
    cout << s.size() << endl;
    return 0;
}
