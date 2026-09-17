class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        

        int n = arr.size();

        vector<int> best(n, INT_MAX);

        int ans = INT_MAX;
        int left = 0;
        int sum = 0;
        int minLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > target && left <= right) {
                sum -= arr[left++];

            }

            if(sum == target) {
                int len = right - left + 1;

                if ( left > 0 && best[left - 1] != INT_MAX) {
                    ans = min(ans, len + best[left - 1]);

                }

                minLen = min(minLen, len);

            }

            if (right > 0)
            best[right] = best[right - 1];

            if (minLen != INT_MAX)
            best[right] = min(best[right], minLen);
        }
return ans == INT_MAX ? -1 : ans;
    }
};