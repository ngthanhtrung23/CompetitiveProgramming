class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector< pair<int,int> > events;
        for (auto interval : intervals) {
            events.push_back({interval[0], +1});
            events.push_back({interval[1], -1});
        }
        sort(events.begin(), events.end());

        int res = 0;
        int room = 0;
        for (auto [time, val] : events) {
            room += val;
            res = max(res, room);
        }
        return res;
    }
};
