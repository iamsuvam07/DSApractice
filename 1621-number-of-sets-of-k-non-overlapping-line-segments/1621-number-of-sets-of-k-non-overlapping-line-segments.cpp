class Solution {
public:
    int numberOfSets(int n, int k) {
        

        const long long MOD = 1e9 + 7;

int N = n + k - 1;
int R = 2 * k;

long long ans = 1;

for (int i = 1; i <= R; i++) {
    ans = ans * ( N - R + i) % MOD;

    long long a = i, b = MOD - 2, res = 1;

    while ( b > 0) {
        if( b & 1)
        res = res * a % MOD;

        a = a * a % MOD;
        b >>= 1;
    }

    ans = ans * res % MOD;
}

return ans ;
    }
};