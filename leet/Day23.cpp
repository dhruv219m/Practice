//2914. Minimum Number of Changes to Make Binary String Beautiful
class Solution {
public:
    int minChanges(string s) {
        int changes = 0;

        for (int i = 0; i < s.length(); i += 2) {
            if (s[i] != s[i + 1]) {
                changes++;
            }
        }

        return changes;
    }
};
