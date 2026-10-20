class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        
int n = nums.size();

vector<int> prefMax(n + 1);
vector<int> suffMin(n + 1);
vector<int> prefDrop( n + 1, 0);

for (int i = 0; i < n; i++) {
    prefMax[i + 1] = max(prefMax[i], nums[i]);

}

suffMin[n] = INT_MAX;

for(int i = n - 1; i >= 0; i--) {
    suffMin[i] = min(suffMin[i + 1], nums[i]);
}

for (int i = 1; i < n; i++) {
    prefDrop[i + 1] = prefDrop[i] + (nums[i - 1] > nums[i]);
}

auto check = [&] (int k) -> bool {
    for (int start = 0; start < n; start += k) {
        int end = start + k - 1;

        int drops = prefDrop[end + 1] - prefDrop[start + 1];

        if (nums[end] > nums[start])
        drops++;

        if ( drops > 1)
        return false;


        if (start > 0 && prefMax[start] > suffMin[start])
        return false;
    }

    return true;
};

int ans = 0;

for (int k = 1; k * k <= n; k++) {
    if ( n % k != 0)
    continue;

    if (check(k))
    ans += k;

    int other = n / k;

    if (other != k && check(other))
    ans += other;
}
return ans;

    }
};