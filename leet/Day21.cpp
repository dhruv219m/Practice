//2243. Calculate Digit Sum of a String
class Solution {
public:
    string digitSum(string s, int k) {
        while (s.length() > k) {
            string next_s;
            for (int i = 0; i < s.length(); i += k) {
                int group_sum = 0;
                for (int j = i; j < i + k && j < s.length(); ++j) {
                    group_sum += s[j] - '0';
                }
                next_s += to_string(group_sum);
            }
            s = move(next_s);
        }
        return s;
    }
};
