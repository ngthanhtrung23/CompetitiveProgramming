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

const int NLINE = 100111;
const int NSTOP = 300111;

struct Line {
    vector<int> stops;
    int x;
    bool visited;
} lines[NLINE];

struct Stop {
    vector<int> lines;
    int x, time;
    bool visited;
} stops[NSTOP];

int nLines, nStops, start, target;
map<string,int> lineId, stopId;
int qu[NLINE], first, last;
string startName, targetName;

void init() {
    lineId.clear();
    stopId.clear();
    first = last = 0;

    nLines = nStops = 0;
}

void read() {
    string tmp, s;
    cin >> tmp;
    while (cin >> s) {
        bool ok = false;
        if (s[s.length()-1] == ',') {
            ok = true;
            s = s.substr(0, s.length()-1);
        }
        stopId[s] = ++nStops;
        if (!ok) break;
    }

    cin >> tmp;
    while (cin >> s) {
        bool ok = false;
        if (s[s.length()-1] == ',') {
            ok = true;
            s = s.substr(0, s.length()-1);
        }
        lineId[s] = ++nLines;
        if (!ok) break;
    }

    FOR(i,1,nStops) {
        stops[i].visited = false, stops[i].x = -1; stops[i].time = -1;
        stops[i].lines.clear();
    }
    FOR(i,1,nLines) {
        lines[i].visited = false, lines[i].x = -1;
        lines[i].stops.clear();
    }

    FOR(i,1,nLines) {
        cin >> tmp;
        int curLine = lineId[tmp];
        cin >> tmp;
        while (cin >> s) {
            bool ok = false;
            if (s[s.length()-1] == ',') {
                ok = true;
                s = s.substr(0, s.length()-1);
            }
            int curStop = stopId[s];

            stops[curStop].lines.push_back(curLine);
            lines[curLine].stops.push_back(curStop);
            if (!ok) break;
        }
    }

    // DEBUG(nStops);
    // DEBUG(nLines);
    // cout << "Stops:\n";
    // for(__typeof(stopId.begin()) it = stopId.begin(); it != stopId.end(); ++it) {
    //     cout << it->first << ' ' << it->second << endl;
    //     REP(i,stops[it->second].lines.size())
    //         cout << stops[it->second].lines[i] << ' ';
    //     cout << endl;
    // }
    // cout << "Lines:\n";
    // for(__typeof(lineId.begin()) it = lineId.begin(); it != lineId.end(); ++it) {
    //     cout << it->first << ' ' << it->second << endl;
    //     REP(i,lines[it->second].stops.size())
    //         cout << lines[it->second].stops[i] << ' ';
    //     cout << endl;
    // }

    cin >> tmp >> tmp >> tmp; cin >> s; start = stopId[s]; startName = s;
    cin >> tmp >> tmp >> tmp; cin >> s; target = stopId[s]; targetName = s;
}

void bfs() {
    first = 1; last = 0;
    REP(id,stops[start].lines.size()) {
        int curLine = stops[start].lines[id];
        if (!lines[curLine].visited) {
            ++last;
            qu[last] = curLine;
            lines[curLine].x = 0;
            lines[curLine].visited = true;
        }
    }
    stops[start].x = 0;
    stops[start].visited = true;

    while (first <= last) {
        int curLine = qu[first++];
        REP(t1,lines[curLine].stops.size()) {
            int curStop = lines[curLine].stops[t1];
            if (stops[curStop].visited) continue;

            stops[curStop].x = lines[curLine].x + 1;
            stops[curStop].visited = true;

            REP(t2,stops[curStop].lines.size()) {
                int nextLine = stops[curStop].lines[t2];
                if (lines[nextLine].visited) continue;

                ++last; qu[last] = nextLine;
                lines[nextLine].visited = true;
                lines[nextLine].x = lines[curLine].x + 1;
            }
        }
    }

    // cout << "stops.x = \n";
    // FOR(i,1,nStops) cout << stops[i].x << ' '; cout << endl;
    // cout << "lines.x = \n";
    // FOR(i,1,nLines) cout << lines[i].x << ' '; cout << endl;
}

void solve() {
    stops[start].time = 0;
    FOR(q,1,last) {
        int curLine = qu[q];
        REP(turn,2) {
            int best = -1000111000;
            REP(id,lines[curLine].stops.size()) {
                int curStop = lines[curLine].stops[id];
                if (stops[curStop].x == lines[curLine].x) {
                    best = max(best + 1, stops[curStop].time);
                }
                else {
                    ++best;
                    stops[curStop].time = max(stops[curStop].time, best);
                }
            }
            reverse(lines[curLine].stops.begin(), lines[curLine].stops.end());
        }
        // cout << "stops.time = \n";
        // FOR(i,1,nStops) cout << stops[i].time << ' '; cout << endl;
    }

    cout << "optimal travel from " << startName << " to " << targetName << ": ";
    cout << stops[target].x << " line" << ((stops[target].x == 1) ? ", " : "s, ");
    cout << stops[target].time << " minute" << ((stops[target].time == 1) ? "\n" : "s\n");
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        // cout << "--------------\n";
        init();
        read();
        bfs();
        solve();
    }
    return 0;
}
