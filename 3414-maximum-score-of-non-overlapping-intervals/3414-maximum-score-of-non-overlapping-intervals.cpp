class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        
        int n = intervals.size();

        vector<array<long long, 4>> a(n);

        for(int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };

        }

sort(a.begin(), a.end(), [](const auto &x, auto &y) {
            if (x[1] != y[1])
            return x[1] < y[1];

            return x[0] < y[0];
        });

    vector<int> prev(n);

    for (int i = 0; i < n; i++) {

int low = 0;
int high = i - 1;
int ans = -1;

while (low <= high) {
    int mid = low + (high - low) / 2;
    if (a[mid][1] < a[i][0]) {
                    ans = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            prev[i] = ans;
        }

        /*
            dp[i][k]:
            Best result using first i intervals
            while selecting at most k intervals.

            pair.first  = maximum weight
            pair.second = selected original indices
        */
        vector<vector<pair<long long, vector<int>>>> dp(
            n + 1,
            vector<pair<long long, vector<int>>>(5)
        );

        for (int i = 1; i <= n; i++) {

            // Option 1: Don't select current interval
            for (int k = 0; k <= 4; k++) {
                dp[i][k] = dp[i - 1][k];
            }

            // Previous non-overlapping interval
            int p = prev[i - 1] + 1;

            // Option 2: Select current interval
            for (int k = 1; k <= 4; k++) {

                long long newWeight =
                    dp[p][k - 1].first + a[i - 1][2];

                vector<int> candidate =
                    dp[p][k - 1].second;

                candidate.push_back((int)a[i - 1][3]);

                // Required for tie-breaking:
                // lexicographically smaller indices
                sort(candidate.begin(), candidate.end());

                vector<int> current =
                    dp[i][k].second;

                sort(current.begin(), current.end());

                if (newWeight > dp[i][k].first ||
                    (newWeight == dp[i][k].first &&
                     candidate < current)) {

                    dp[i][k] = {
                        newWeight,
                        candidate
                    };
                }
            }
        }

        return dp[n][4].second;
    }
  };