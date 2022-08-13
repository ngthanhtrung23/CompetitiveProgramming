#include "insects.h"
#include "bits/stdc++.h"

#define SZ(s) ((int) s.size())
using namespace std;

#ifndef RR
#define DEBUG(X)
#endif

int min_cardinality(int n) {
    std::set<int> insides;  // set of insects inside machine
    // lambda functions {{{
    // lambda function to add one insect to machine
    auto add = [&] (int i) { move_inside(i); insides.insert(i); };
    // lambda function to remove one insect from machine
    auto remove = [&] (int i) { move_outside(i); insides.erase(i); };
    // }}}

    // machine_states(f) = set of insects inside machine after we
    //                     binary search with value f
    std::map<int, std::set<int>> machine_states;

    // Step 1: Find set containing unique insects {{{
    for (int i = 0; i < n; ++i) {
        add(i);
        if (press_button() > 1) {  // this species appeared before
            remove(i);
        }
    }
    int unique_vals = SZ(insides);
    // }}}

    machine_states[1] = insides;
    machine_states[n] = std::set<int>();
    for (int i = 0; i < n; ++i) machine_states[n].insert(i);

    // Step 2: Binary search for min f
    int l = 2, r = n / unique_vals, res = 1;
    while (l <= r) {
        int mid = (l + r) / 2;

        assert(mid > res);
        auto it = machine_states.lower_bound(mid);
        std::set<int> just_added;
        for (int i : it->second) if (!insides.count(i)) {
            add(i);
            if (press_button() > mid) remove(i);
            else just_added.insert(i);
        }
        int total = SZ(insides);
        machine_states[mid] = insides;

        if (total >= unique_vals * mid) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
            for (int i : just_added) {
                remove(i);
            }
        }
    }
    return res;
}
