class Solution {
public:
    string lexPalindromicPermutation(string s, string target) { 
        int n = s.size();
        int m = n / 2;

        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        char mid = 0;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                if (mid != 0)
                    return "";
                mid = 'a' + i;
            }
            cnt[i] /= 2;
        }

        if (m == 0) {
            string ans(1, mid);
            return ans > target ? ans : "";
        }

        vector<int> rem = cnt;
        bool possible = true;

        for (int i = 0; i < m; i++) {
            int x = target[i] - 'a';

            if (rem[x] == 0) {
                possible = false;
                break;
            }

            rem[x]--;
        }

        if (possible) {
            string left = target.substr(0, m);

            string right = left;
            reverse(right.begin(), right.end());

            string pal = left;

            if (mid != 0)
                pal += mid;

            pal += right;

            if (pal > target)
                return pal;
        }

        rem = cnt;

        int pivot = -1;
        int pivotChar = -1;

        for (int i = 0; i < m; i++) {
            int x = target[i] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (rem[c] > 0) {
                    pivot = i;
                    pivotChar = c;
                }
            }

            if (rem[x] == 0)
                break;

            rem[x]--;
        }

        if (pivot == -1)
            return "";

        rem = cnt;

        string left = "";

        for (int i = 0; i < pivot; i++) {
            int x = target[i] - 'a';
            left += target[i];
            rem[x]--;
        }

        for (int c = target[pivot] - 'a' + 1; c < 26; c++) {
            if (rem[c] > 0) {
                pivotChar = c;
                break;
            }
        }

        left += char('a' + pivotChar);
        rem[pivotChar]--;

        for (int c = 0; c < 26; c++) {
            left.append(rem[c], char('a' + c));
        }

        string ans = left;

        if (mid != 0)
            ans += mid;

        string right = left;
        reverse(right.begin(), right.end());

        ans += right;

        return ans;
    }
};
