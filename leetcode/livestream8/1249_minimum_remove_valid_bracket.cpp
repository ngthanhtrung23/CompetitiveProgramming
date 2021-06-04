// (a()
// --> (a) or a()

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        string res = "";
        int sum = 0;
        // left -> right: remove )
        for (char c : s) {
            if (c == '(') ++sum;
            else if (c == ')') --sum;
            
            if (sum < 0) sum++;
            else res += c;
        }
        
        s = res;
        reverse(s.begin(), s.end());
        // right -> left: remove (
        sum = 0;
        res = "";
        for (char c : s) {
            if (c == ')') ++sum;
            else if (c == '(') --sum;
            
            if (sum < 0) sum++;
            else res += c;
        }

        reverse(res.begin(), res.end());
        return res;
    }
};
