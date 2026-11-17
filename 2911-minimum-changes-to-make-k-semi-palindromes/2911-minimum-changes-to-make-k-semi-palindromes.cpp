class Solution {
public:
    int minimumChanges(string s, int k) {
        

int n = s.size();

const int INF = 1e9;

vector<vector<int>> cost(n, vector<int>(n, INF));

for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len <= n; l++) {
        int r = l + len - 1;

        for (int d = 1; d < len; d++) {
            if (len % d != 0) continue;

            int changes = 0;
int groups = len / d;

            for (int r = 0; r < d; r++) {

                for (int t = 0; t < groups / 2; t++) {

                
                int i = l + r + t * d;
                int j = l + r + (groups - 1 - t) * d;


                if (s[i] != s[j]) {
                    changes++;
                }
                }
            }


            cost[l][r] = min(cost[l][r], changes);

        }
    }
}


vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));

dp[0][0] = 0;

for (int i = 1; i <=n; i++) {
    for (int j = 1; j <= k; j++) {
        for (int p = 0; p < i; p++) {
            if (i - p < 2 || dp[p][j - 1] == INF)

            continue;

            dp[i][j] = min(dp[i][j], dp[p][j - 1] + cost[p][i - 1]);

        }
    }
}


return dp[n][k];

    }
};