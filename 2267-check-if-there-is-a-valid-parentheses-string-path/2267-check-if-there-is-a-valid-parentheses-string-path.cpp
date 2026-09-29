class Solution {
public:


int n, m;
string grid;
vector<vector<vector<int>>> dp;

bool solve(vector<vector<char>>& a, int i, int j, int balance) {
    if(balance < 0)
    return false;

    int remaining = (n - 1 - i) + (m - 1 - j);
    if (balance > remaining)
    return false;

    if(i == n - 1 && j == m - 1)
    return balance == 0;


int & res = dp[i][j][balance];
if ( res != -1)
return res;
    
    if ( i + 1 < n) {
        int newBalance = balance + (a[i  + 1] [j] == '(' ? 1 : - 1);
        if (solve(a, i + 1, j, newBalance))
        return res = 1;

    }

    if (j + 1 < m) {
        int newBalance = balance + (a[i][j + 1] == '(' ? 1 : -1);
        if (solve(a, i, j + 1, newBalance))
        return res = 1;

    }
    return res = 0;
}
    bool hasValidPath(vector<vector<char>>& grid) {
        
        n = grid.size();
        m = grid[0].size();

        if((n + m - 1) % 2 != 0)

        return false;

        if(grid[0][0] == ')')
        return false;


        int maxBalance = n + m;
        dp.assign(n, vector<vector<int>>(m, vector<int>(maxBalance + 1, -1)));

        return solve(grid, 0, 0, 1);
    }
};