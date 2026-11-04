class Solution {
    multiset<int> low, high;

    long long lowSum = 0, highSum = 0;

    void add(int val) {
        if (low.empty() || val <= *low.rbegin()) {
            low.insert(val);
            lowSum += val;

        } else {
            high.insert(val);
            highSum += val;
        }
        balance();
    }
    void remove(int val) {
        auto it = low.find(val);

        if (it != low.end()) {
            low.erase(it);
            lowSum -= val;
        } else {
            it = high.find(val);
            high.erase(it);
            highSum -= val;
        }
        balance();

    }
    void balance() {
        int target =(low.size() + high.size() + 1) / 2;

        while (low.size() > target) {
            int val = *low.rbegin();
            low.erase(prev(low.end()));
            lowSum -= val;

            high.insert(val);
            highSum += val;

        }

        while(low.size() < target) {
            int val = *high.begin();
            high.erase(high.begin());
            highSum -= val;



            low.insert(val);
            lowSum += val;
        }
    }

    long long getCost() {
        long long median = *low.rbegin();


        return median * (long long)low.size() - lowSum + highSum - median * (long long)high.size();
    }
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        

        int n =nums.size();

        vector<int> maritovexi = nums;

        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++) {
            add(maritovexi[i]);
        }

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            remove(maritovexi[i - x]);
            add(maritovexi[i]);


            cost[i - x + 1] = getCost();
        }

        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp( k + 1, vector<long long>(n + 1, INF)
        );

        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            for (int t = 0; t <= k; t++) {
                if (dp[t][i] == INF)
                continue;

                dp[t][i + 1] = min (dp[t][i + 1], dp[t][i] 
                
                );
      if (t < k && i + x <= n) {
        dp[t + 1][i + x] = min(
            dp[t + 1][i + x],
            dp[t][i] + cost[i]
        );
      }

            }
        }

        return dp[k][n];
    }
};