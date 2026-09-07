class Solution {
public:
    int distinctSubseqII(string s) {
        

        const int MOD = 1e9 + 7;

        vector<long long> dp(26, 0);
        long long total = 0;


        for (char c : s) {
            int idx = c - 'a';

            long long add = (total + 1) % MOD;

            total =(total + add - dp[idx] + MOD) % MOD;

            dp[idx] = add;

        }

        return total;
    }
};