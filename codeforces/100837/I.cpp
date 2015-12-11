#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

char tmp[100111];
int globalTime = 0;

struct Node {
    vector<Node*> parents;
    Node* married;
    int gender;
    vector< Node* > children;
    int lastModified;

    int dist;
};

Node* createNode(int x, int dist) {
    Node* res = new Node();
    res->gender = x;
    res->dist = dist;
    res->parents.clear();
    res->children.clear();
    res->lastModified = 0;

    res->married = new Node();
    res->married->gender = 1-x;
    res->married->dist = dist;
    res->married->parents.clear();
    res->married->children.clear();
    res->lastModified = 0;

    res->married->married = res;

    return res;
}

void setRelation(Node* parent, Node* child) {
    if (!child->parents.empty()) return;
    child->parents.push_back(parent);
    child->parents.push_back(parent->married);

    parent->children.push_back(child);
    parent->married->children.push_back(child);
}

vector<Node*> getParent(Node* x, int gender) {
    if (x->parents.empty()) {
        Node* p = createNode(1, x->dist + 1);
        setRelation(p, x);
    }

    vector<Node*> res;
    for(auto p : x->parents) {
        if (gender < 0 || p->gender == gender)
            res.push_back(p);
    }
    return res;
}

vector<Node*> getChild(Node* x, int gender) {
    vector<Node*> res;
    // existing child
    for(auto p : x->children) {
        if (gender < 0) res.push_back(p);  // any gender
        else if (p->gender == gender) res.push_back(p);
    }
    // new child
    if (x->lastModified == globalTime) return res;

    x->lastModified = globalTime;
    REP(g,2) {
        if (gender < 0 || g == gender) {
            Node* p = createNode(g, x->dist + 1);
            setRelation(x, p);
            res.push_back(p);
        }
    }

    return res;
}

vector<Node*> getAllChildren(vector<Node*> x, int gender) {
    vector<Node*> res;
    for(auto p : x) {
        auto t = getChild(p, gender);
        res.insert(res.end(), t.begin(), t.end());
    }
    return res;
}

vector<Node*> getAllParents(vector<Node*> x, int gender) {
    vector<Node*> res;
    for(auto p : x) {
        auto t = getParent(p, gender);
        res.insert(res.end(), t.begin(), t.end());
    }
    return res;
}

vector<Node*> getAllMarried(vector<Node*> x, int gender) {
    vector<Node*> res;
    for(auto p : x) {
        Node* cur = p->married;
        if (gender < 0 || cur->gender == gender)
            res.push_back(cur);
    }
    return res;
}

vector<Node*> getBrotherSister(Node* p, int gender) {
    vector<Node*> res;
    // up
    vector<Node*> t = getParent(p, -1);
    // down
    t = getAllChildren(t, gender);
    
    // must be different than myself
    for(auto a : t)
        if (a != p)
            res.push_back(a);
    return res;
}

vector<Node*> getAllBrotherSister(vector<Node*> x, int gender) {
    vector<Node*> res;
    for(auto p : x) {
        auto t = getBrotherSister(p, gender);
        res.insert(res.end(), t.begin(), t.end());
    }
    return res;
}

vector<Node*> getAllUncleAunt(vector<Node*> x, int gender) {
    vector<Node*> res;
    vector<Node*> t = getAllParents(x, -1);
    for(auto p : t) {
        vector<Node*> t2 = getBrotherSister(p, gender);
        res.insert(res.end(), t2.begin(), t2.end());
    }
    return res;
}

int used[11000111];

vector<Node*> selective(vector<Node*> cur) {
    if (SZ(cur) < 10000) return cur;
    vector<Node*> res;

    map<int,int> has;

    REP(i,SZ(cur)) {
        auto p = cur[i];
        if (has[p->dist] < 10) {
            res.push_back(p);
            ++has[p->dist];
            used[i] = true;
        }
        else used[i] = false;
    }

    REP(i,SZ(cur)) if (!used[i]) {
        used[i] = true;
        res.push_back(cur[i]);
        if (SZ(res) >= 10000) return res;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("i.in", "r", stdin);
    freopen("i.out", "w", stdout);
    while (gets(tmp)) {
        REP(i,strlen(tmp)) {
            if (tmp[i] == '\'') {
                tmp[i] = tmp[i+1] = ' ';
            }
        }
        stringstream ss(tmp);
        string t;
        ss >> t >> t >> t;  // C is A

        Node* A0 = createNode(0, 0);
        Node* A1 = createNode(1, 0);

        vector< Node* > cur;
        cur.push_back(A0);
        cur.push_back(A1);
        
        globalTime = 0;
        while (ss >> t) {
            ++globalTime;
            if (t == "father") {
                cur = getAllParents(cur, 1);
            }
            else if (t == "mother") {
                cur = getAllParents(cur, 0);
            }
            else if (t == "son") {
                cur = getAllChildren(cur, 1);
            }
            else if (t == "daughter") {
                cur = getAllChildren(cur, 0);
            }
            else if (t == "husband") {
                cur = getAllMarried(cur, 1);
            }
            else if (t == "wife") {
                cur = getAllMarried(cur, 0);
            }
            else if (t == "brother") {
                cur = getAllBrotherSister(cur, 1);
            }
            else if (t == "sister") {
                cur = getAllBrotherSister(cur, 0);
            }
            else if (t == "grandfather") {
                cur = getAllParents(cur, -1);
                cur = getAllParents(cur, 1);
            }
            else if (t == "grandmother") {
                cur = getAllParents(cur, -1);
                cur = getAllParents(cur, 0);
            }
            else if (t == "grandson") {
                cur = getAllChildren(cur, -1);
                cur = getAllChildren(cur, 1);
            }
            else if (t == "granddaughter") {
                cur = getAllChildren(cur, -1);
                cur = getAllChildren(cur, 0);
            }
            else if (t == "uncle") {
                cur = getAllUncleAunt(cur, 1);
            }
            else if (t == "aunt") {
                cur = getAllUncleAunt(cur, 0);
            }
            else if (t == "nephew") {
                cur = getAllBrotherSister(cur, -1);
                cur = getAllChildren(cur, 1);
            }
            else if (t == "niece") {
                cur = getAllBrotherSister(cur, -1);
                cur = getAllChildren(cur, 0);
            }
            else {
                assert(0);
            }
            
            if (SZ(cur) > 10000) cur = selective(cur);
        }

        int nn = 1e9, ln = -1e9;
        for(auto p : cur) {
            nn = min(nn, p->dist);
            ln = max(ln, p->dist);
        }
        cout << ln << ' ' << nn << endl;
    }
}

