#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

char a[100111], tmp[1011];
int nChar, pos = 0;

map<string,int> cnt;
map<string,string> abbr;

bool isAlpha(char c) {
    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= '0' && c <= '9') return true;
    return false;
}

char eatChar() {
    return a[pos++];
}

string eatWord() {
    string res = "";
    while (isAlpha(a[pos]))
        res += a[pos++];
    return res;
}

bool isAbbr(string s) {
    REP(i,s.length())
        if (s[i] >= '0' && s[i] <= '9') return true;
    return false;
}

void add(string s) {
    stringstream ss; ss << s[0] << s.length()-2 << s[s.length()-1];
    string a = ss.str();
    if (cnt.find(a) != cnt.end()) {
        if (abbr[a] != s) cnt[a]++;
    }
    else {
        cnt[a] = 1;
        abbr[a] = s;
    }
}

void addAbbr(string s) {
    // To lowercase
    REP(i,s.length()) if (s[i] >= 'A' && s[i] <= 'Z') s[i] ^= ' ';
    add(s);

    s[0] ^= ' ';
    add(s);

    REP(i,s.length()) s[i] ^= ' '; s[0] ^= ' ';
    add(s);
}

int main() {
    freopen("i18n.in", "r", stdin);
    freopen("i18n.out", "w", stdout);

    while (gets(tmp)) {
        REP(i,strlen(tmp)) a[nChar++] = tmp[i];
        a[nChar++] = '\n';
    }
    while (pos < nChar) {
        if (isAlpha(a[pos])) {
            string word = eatWord();
            if (isAbbr(word)) {
                if (cnt.find(word) == cnt.end() || cnt[word] > 1) {
                    printf("%s", word.c_str());
                }
                else {
                    printf("%s", abbr[word].c_str());
                }
            }
            else {
                printf("%s", word.c_str());
                addAbbr(word);
            }
        }
        else {
            char cur = eatChar();
            putchar(cur);
        }
    }
    return 0;
}
