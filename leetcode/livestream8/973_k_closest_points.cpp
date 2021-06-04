using Point = vector<int>;

int dist(const Point& a) {
    return a[0]*a[0] + a[1]*a[1];
}

int cmp(const Point& a, const Point& b) {
    int da = dist(a);
    int db = dist(b);
    
    if (da == db) return 0;
    if (da < db) return -1;
    return 1;
}

class Solution {
public:
    vector<vector<int>> kClosest(vector<Point>& points, int k) {
        if (points.size() <= k) return points;
        
        random_shuffle(points.begin(), points.end());
        findK(points, k);
        points.resize(k);
        return points;
    }

private:
    void findK(vector<Point>& points, int k) {
        if (points.size() <= k) return;
        
        const Point pivot = points[rand() % points.size()];
        
        vector<Point> smaller, equal, larger;
        for (auto point : points) {
            int c = cmp(point, pivot);
            if (c < 0) smaller.push_back(point);
            else if (c == 0) equal.push_back(point);
            else larger.push_back(point);
        }
        
        // points.size() > k
        if (smaller.size() + equal.size() >= k) {
            findK(smaller, k);
        } else {
            findK(larger, k - smaller.size() - equal.size());
        }

        points = smaller;
        points.insert(points.end(), equal.begin(), equal.end());
        points.insert(points.end(), larger.begin(), larger.end());
    }
};
