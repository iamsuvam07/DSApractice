
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int p = find(nums.begin(), nums.end(), 0) - nums.begin();

        bool inc = true;

        for (int i = 0; i < n; i++) {
            if (nums[(p + i) % n] != i) {
                inc = false;
                break;
            }
        }

        if (inc) {
            return min(p, n - p + 2);
        }

        bool dec = true;

        for (int i = 0; i < n; i++) {
            if (nums[(p - i + n) % n] != i) {
                dec = false;
                break;
            }
        }

        if (dec) {
            return min(p + 2, n - p);
        }

        return -1;
    

    }
};