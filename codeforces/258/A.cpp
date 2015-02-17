#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

char buf[100010];
string s,t;

int main(void){
    int i;
    
    scanf("%s", buf);
    s = buf;
    int N = s.length();
    int x = 0;
    REP(i,N) if(s[i] == '0'){
        x = i;
        break;
    }
    REP(i,N) if(i != x) t += s[i];
    printf("%s\n", t.c_str());
    
    return 0;
}