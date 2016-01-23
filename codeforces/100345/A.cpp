
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

struct Author {
    vector<string> names;

    Author() {}

    friend ostream& operator << (ostream& cout, Author& a) {
        REP(i,SZ(a.names)) {
            if (i == 0) cout << a.names[i];
            else {
                cout << a.names[i][0];
                cout << '.';
            }
            if (i < SZ(a.names) - 1) cout << ' ';
        }
        return cout;
    }
};

const int ARTICLE = 0;
const int BOOK = 1;

struct Ref {
    vector< Author> authors;
    string title;
    int year;
    int volume;

    int typ;
    string journal;
    string publisher;
    string number;
    string pages;

    Ref() { volume = -1; }

    friend ostream& operator << (ostream& cout, Ref& a) {
        REP(i,SZ(a.authors)) {
            cout << a.authors[i];
            if (i < SZ(a.authors) - 1) cout << ", ";
        }
        cout << ' ';
        cout << a.title;

        if (a.typ == ARTICLE) {
            cout << " // ";
            cout << a.journal;
            if (a.volume >= 0) {
                cout << ", ";
                cout << a.volume;
            }
            if (a.number != "") {
                cout << " (" << a.number << ")";
            }
            cout << " -- " << a.year;
            if (a.pages != "") {
                cout << " -- ";
                int t = a.pages.find("--");
                if (t >= 0 && t < SZ(a.pages)) cout << "pp. ";
                else cout << "p. ";
                cout << a.pages;
            }
        }
        else {
            if (a.volume >= 0) {
                cout << ", Vol. " << a.volume;
            }
            cout << " -- ";
            cout << a.publisher;
            cout << ", " << a.year;
        }
        return cout;
    }
};

bool operator < (const Author& a, const Author& b) {
    return a.names < b.names;
}
bool operator == (const Author& a, const Author& b) {
    return a.names == b.names;
}

bool operator < (const Ref& a, const Ref& b) {
    if (a.authors != b.authors) return a.authors < b.authors;
    if (a.title != b.title) return a.title < b.title;
    return a.volume < b.volume;
}

string readUntil(stringstream& ss, char c, bool& found) {
    string res = "";
    char t;
    found = false;
    while (ss >> t) {
        if (t == c) {
            found = true;
            break;
        }
        res += t;
    }
    return res;
}

string trim(string s) {
    while (s[0] == ' ') s = s.substr(1);
    while (s.back() == ' ') s = s.substr(0, SZ(s) - 1);
    return s;
}

int toInt(string s) {
    stringstream ss(s);
    int res;
    ss >> res;
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("bibtex.in", "r", stdin);
    freopen("bibtex.out", "w", stdout);
    string s = "";
    string t;
    while (getline(cin, t)) {
        s += t;
        s += ' ';
    }
    vector<Ref> refs;

    stringstream ss(s);
    ss >> std::noskipws;
    while (true) {
        bool found;
        string tmp = readUntil(ss, '@', found);
        if (!found) break;

        string typ = trim(readUntil(ss, '{', found));

        Ref cur;
        if (typ == "book") {
            cur.typ = BOOK;
        }
        else {
            cur.typ = ARTICLE;
        }

//        cout << "----------------------------" << endl;
//        DEBUG(typ);
        while (true) {
            char c = ' ';
            while ((c < 'a' || c > 'z') && c != '}') {
                ss >> c;
            }
            if (c == '}') break;
            
//            DEBUG(c);

            string key = "";
            key += c;
            key += trim(readUntil(ss, '=', found));

            string tmp = readUntil(ss, '"', found);
            string value = readUntil(ss, '"', found);

//            cout << key << " --> " << value << endl;

            if (key == "author") {
                stringstream ss2(value + " and");
                Author author;
                while (ss2 >> t) {
                    if (t == "and") {
                        rotate(author.names.begin(), author.names.begin() + SZ(author.names) - 1, author.names.end());
                        cur.authors.push_back(author);
                        author.names.clear();
                    }
                    else {
                        author.names.push_back(t);
                    }
                }
                sort(cur.authors.begin(), cur.authors.end());
//                PR0(cur.authors, SZ(cur.authors));
            }
            else if (key == "title") {
                cur.title = value;
            }
            else if (key == "journal") {
                cur.journal = value;
            }
            else if (key == "publisher") {
                cur.publisher = value;
            }
            else if (key == "year") {
                cur.year = toInt(value);
            }
            else if (key == "volume") {
                cur.volume = toInt(value);
            }
            else if (key == "number") {
                cur.number = value;
            }
            else if (key == "pages") {
                cur.pages = value;
            }
        }

        refs.push_back(cur);
    }

    sort(refs.begin(), refs.end());
    REP(i,SZ(refs)) {
        cout << '[' << i+1 << "] ";
        cout << refs[i];
        cout << endl;
    }
}
