class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        

        int n = items.size();

        vector<int> dp(budget + 1, 0);

        int minPrice = INT_MAX;

        for (auto &item : items) {
            minPrice = min(minPrice, item[1]);

        }

        for (int i = 0; i < n; i++) {
            int factor = items[i][0];

            int price = items[i][1];

            int freeItems = 0;

            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % factor == 0) {
                    freeItems++;
                }
            }

            int profit = 1 + freeItems;

            for (int j = budget; j >= price; j--) {
                dp[j]= max(dp[j], dp[j - price] + profit);

            }
        }

        int ans = 0;

        for (int i = 0; i <= budget; i++) {
            int remaining = budget - i;


            int total = dp[i] + remaining / minPrice;

            ans = max(ans, total);
        }

        return ans;
    }
};