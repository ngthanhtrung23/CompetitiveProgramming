#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

vector<string> word_list[2];
set<string> word_set[2];
map<string,int> one[2], two[2], idOf[2];

pair<string,string> phrase[2][511];
pair<int,int> phraseId[2][511];
int nPhrase, nWord;
bool hasSol;
int used[55], trans[55];

void init() {
    REP(turn,2) {
        word_list[turn].clear();
        word_set[turn].clear();
        one[turn].clear();
        two[turn].clear();
        idOf[turn].clear();

        hasSol = false;
        memset(used, -1, sizeof used);
        memset(trans, -1, sizeof trans);
    }
}

void attempt(int i) {
    if (i == nWord) {
        hasSol = true;
        REP(i,nWord) cout << word_list[0][i] << '/' << word_list[1][trans[i]] << '\n';
        cout << '\n';
        return ;
    }
    string s = word_list[0][i];
    REP(j,nWord) if (used[j] < 0) {
        string cur = word_list[1][j];
        if (one[0][s] == one[1][cur] && two[0][s] == two[1][cur]) {
            used[j] = i;
            trans[i] = j;

            bool can = true;

            bitset<26> left, right;
            left.reset(); right.reset();
            FOR(p,1,nPhrase) {
                if (phraseId[0][p].first == i && trans[phraseId[0][p].second] >= 0) {
                    left.set(trans[phraseId[0][p].second]);
                }
                if (phraseId[1][p].first == j && used[phraseId[1][p].second] >= 0) {
                    right.set(phraseId[1][p].second);
                }
            }
            if (left == right) {
                left.reset(); right.reset();
                FOR(p,1,nPhrase) {
                    if (phraseId[0][p].second == i && trans[phraseId[0][p].first] >= 0) {
                        left.set(trans[phraseId[0][p].first]);
                    }
                    if (phraseId[1][p].second == j && used[phraseId[1][p].first] >= 0) {
                        right.set(phraseId[1][p].first);
                    }
                }
                if (left == right) {
                    attempt(i+1);
                }
            }

            trans[i] = -1;
            used[j] = -1;
        }
    }
}

int main() {
    while (cin >> nPhrase && nPhrase) {
        init();
        REP(turn,2) {
            FOR(i,1,nPhrase) {
                cin >> phrase[turn][i].first >> phrase[turn][i].second;
                word_set[turn].insert(phrase[turn][i].first);
                word_set[turn].insert(phrase[turn][i].second);

                one[turn][phrase[turn][i].first]++;
                two[turn][phrase[turn][i].second]++;
            }

            for(auto s : word_set[turn]) {
                word_list[turn].push_back(s);
            }

            REP(i,word_list[turn].size()) {
                string s = word_list[turn][i];
                idOf[turn][s] = i;
            }

//            PR0(word_list[turn], word_list[turn].size());

            FOR(i,1,nPhrase) {
                phraseId[turn][i].first = idOf[turn][phrase[turn][i].first];
                phraseId[turn][i].second = idOf[turn][phrase[turn][i].second];
            }
        }
        nWord = word_list[0].size();
        attempt(0);
    }
    return 0;
}

