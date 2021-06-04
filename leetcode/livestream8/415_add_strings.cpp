class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        int rem = 0;
        
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        
        for (int i = 0; i < num1.size() || i < num2.size(); i++) {
            int cur = rem;
            if (i < num1.size()) cur += num1[i] - '0';
            if (i < num2.size()) cur += num2[i] - '0';
            
            rem = cur / 10;
            cur %= 10;
            res += (char) (cur + '0');
        }
        if (rem > 0) {
            res += '1';
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};
