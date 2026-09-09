class Solution {
public:
    long long countCommas(long long n) {
      long long ans = 0;

      for (long long threshold = 1000; threshold <= n; ) {
        ans += n - threshold + 1;

        if(threshold > n / 1000)
        break;

        threshold *= 1000;
      }   
   return ans;

    }
};