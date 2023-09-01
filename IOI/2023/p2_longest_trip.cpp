// 100
// Solution write-up: https://www.facebook.com/code.cung.rr/posts/pfbid02yyoPchQpaUfaeSkQ7WZyWJTDB3WNNJfrThzeVLJXrCx7EeJvUV7LFCGdM1iAkSCjl
//
// Subtasks:
// 1. graph is complete -> any permutation is good
// 2. D = 2. Maintain a path that contains ALL vertices. For each i,
//    we can either add it to beginning or end of path
// 3. D = 1. Maintain 2 paths that contains ALL vertices. For each i:
//    - either add it to end of 1 path
//    - or we can connect 2 paths
// 4. Similar to 3, but we can merge 2 paths

#include "longesttrip.h"
#include <bits/stdc++.h>
using namespace std;

// Subtask 1: D == 3
vector<int> sub1(int n) {
    vector<int> res(n);
    std::iota(res.begin(), res.end(), 0);
    return res;
}

// Subtask 2: D == 2
bool has_edge(int u, int v) {
    return are_connected({u}, {v});
}

vector<int> sub2(int n) {
    vector<int> res {0};
    for (int i = 1; i < n; i++) {
        if (has_edge(0, i)) {
            res.push_back(i);
            break;
        }
    }

    for (int i = 1; i < n; i++) {
        if (i == res[1]) continue;

        if (has_edge(res.back(), i)) {
            res.push_back(i);
        } else {
            res.insert(res.begin(), i);
        }
    }

    return res;
}

// Subtask 3: D == 1, return path with length >= Lmax / 2
vector<int> sub3(int n) {
    // maintain 2 paths
    vector<int> p1 {0}, p2 {1};

    for (int i = 2; i < n; ++i) {
        // consider p1.back(), p2.back(), i
        // -> there's at least 1 edge

        if (has_edge(p1.back(), i)) {
            p1.push_back(i);
        } else if (has_edge(p2.back(), i)) {
            p2.push_back(i);
        } else {
            reverse(p2.begin(), p2.end());
            p1.insert(p1.end(), p2.begin(), p2.end());
            p2 = {i};
        }
    }
    if (p1.size() > p2.size()) return p1;
    return p2;
}

// Subtask 4: D == 1
vector<int> sub4(int n) {
    // Use subtask 3 to get 2 paths {{{
    vector<int> p1 {0}, p2 {1};
    bool last_to_2 = false;
    for (int i = 2; i < n; ++i) {
        if (has_edge(p1.back(), i)) {
            p1.push_back(i);
            last_to_2 = false;
        } else if (last_to_2 || has_edge(p2.back(), i)) {
            p2.push_back(i);
            last_to_2 = true;
        } else {
            reverse(p2.begin(), p2.end());
            p1.insert(p1.end(), p2.begin(), p2.end());
            p2 = {i};
            last_to_2 = false;
        }
    }
    // }}}
    
    // Make p1 longer path
    if (p1.size() < p2.size()) swap(p1, p2);
    if (p2.empty()) return p1;

    // Impossible to merge 2 paths
    if (!are_connected(p1, p2)) {
        return p1;
    }
    
    // Merge 2 paths:
    // Consider: p1[0], p1.back() and p2[0] -> at least 1 edge
    if (has_edge(p1.back(), p2[0])) {
        p1.insert(p1.end(), p2.begin(), p2.end());
        return p1;
    } else if (has_edge(p1[0], p2[0])) {
        reverse(p2.begin(), p2.end());
        p2.insert(p2.end(), p1.begin(), p1.end());
        return p2;
    }

    // p1 is now a circle
    // Consider: p2[0], p2.back() and p1[0] -> at least 1 edge
    if (p2.size() > 1) {
        if (has_edge(p2[0], p1[0])) {
            reverse(p1.begin(), p1.end());
            p1.insert(p1.end(), p2.begin(), p2.end());
            return p1;
        } else if (has_edge(p2.back(), p1[0])) {
            p2.insert(p2.end(), p1.begin(), p1.end());
            return p2;
        }
    }

    // p2 is now also a circle
    // Find one edge from p1 -> p2
    int l1 = 0, r1 = p1.size() - 1;  // p1[l1..r1] has at least one edge to p2
    while (l1 < r1) {
        int mid = (l1 + r1) / 2;
        if (are_connected(vector<int>(p1.begin() + l1, p1.begin() + mid + 1), p2)) {
            r1 = mid;
        } else l1 = mid + 1;
    }
    int l2 = 0, r2 = p2.size() - 1;  // p2[l2..r2] has at least one edge to p1[l1]
    while (l2 < r2) {
        int mid = (l2 + r2) / 2;
        if (are_connected({p1[l1]}, vector<int>(p2.begin() + l2, p2.begin() + mid + 1))) {
            r2 = mid;
        } else l2 = mid + 1;
    }

    vector<int> res;
    res.insert(res.end(), p1.begin() + l1 + 1, p1.end());
    res.insert(res.end(), p1.begin(), p1.begin() + l1 + 1);
    res.insert(res.end(), p2.begin() + l2, p2.end());
    res.insert(res.end(), p2.begin(), p2.begin() + l2);
    return res;
}

vector<int> longest_trip(int n, int d) {
    if (d == 3) return sub1(n);
    if (d == 2) return sub2(n);
    return sub4(n);
}


