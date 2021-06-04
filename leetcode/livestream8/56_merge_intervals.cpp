using Segment = vector<int>;

bool areIntersect(const Segment& a, const Segment& b) {
    if (a[1] < b[0]) return false;  // a completely on left of b
    if (b[1] < a[0]) return false;
    return true;
}

Segment combine(const Segment& a, const Segment& b) {
    return {
        min(a[0], b[0]),
        max(a[1], b[1])
    };
}

class Solution {
public:
    vector<Segment> merge(vector<Segment>& intervals) {
        if (intervals.empty()) return {};
        
        sort(intervals.begin(), intervals.end());
        vector<Segment> res;
        
        for (auto interval : intervals) {
            if (res.empty()) {
                res.push_back(interval);
            } else if (areIntersect(interval, res.back())) {
                res.back() = combine(res.back(), interval);
            } else {
                res.push_back(interval);
            }
        }
        
        return res;
    }
};
