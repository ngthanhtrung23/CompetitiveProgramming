class Solution {
public:
    string decodeString(string s) {
        if (s == "") return "";

        // find matching bracket
        int n = s.size();
        vector<int> matching(n, -1);
        stack<int> st;
        
        for (int i = 0; i < n; i++) {
            if (s[i] == '[') st.push(i);
            else if (s[i] == ']') {
                assert(!st.empty());

                int j = st.top();
                matching[i] = j;
                matching[j] = i;
                st.pop();
            }
        }
        
        // recursively decode string
        return solve(s, 0, n-1, matching);
    }
   
private:
    string solve(const string& s, int l, int r, const vector<int>& matching) {
        if (l > r) return "";
        string res = "";
        
        int i = l;
        while (i <= r) {
            if (s[i] >= '0' && s[i] <= '9') {
                int repeat = s[i] - '0';
                int j = i + 1;
                while (s[j] != '[') {
                    assert(s[j] >= '0' && s[j] <= '9');

                    repeat = repeat * 10 + s[j] - '0';
                    ++j;
                }

                // now s[j] == [
                assert(s[j] == '[');
                assert(s[matching[j]] == ']');

                string child = solve(s, j + 1, matching[j] - 1, matching);
                for (int tmp = 0; tmp < repeat; tmp++) {
                    res += child;
                }
                
                i = matching[j] + 1;
            } else {
                res += s[i];
                ++i;
            }
        }
        
        return res;
    }
};
