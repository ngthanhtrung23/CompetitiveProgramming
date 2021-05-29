class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        int res = 1;
        sort(points.begin(), points.end());
        
        int n = (int) points.size();

        // for pivot point
        for (int i = 0; i < n; i++) {
            int same = 1;  // same coordinate as pivot
            
            map< pair<int,int>, int > cnt;  // count frequency of normalized vector
            for (int j = i + 1; j < n; j++) {
                int dx = points[j][0] - points[i][0];  // >= 0
                int dy = points[j][1] - points[i][1];  // < 0 or >= 0
                
                if (dx == 0 && dy == 0) ++same;
                
                int g = __gcd(abs(dx), abs(dy));
                dx /= g;
                dy /= g;
                
                cnt[{dx, dy}]++;
            }
            
            for (const auto& [vec, freq] : cnt) {
                res = max(res, freq + same);
            }
        }
        return res;
    }
};
