class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        
int m = grid.size();
int n = grid[0].size();


int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};


function<long long(int, int)> dfs = [&](int x, int y) -> long long{
    long long sum = grid[x][y];

    grid[x][y] = 0;

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];


        if(nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] > 0) {

            sum += dfs(nx, ny);
        }
    }

    return sum;
};

int ans = 0;

for (int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) {
        if (grid[i][j] > 0) {
            long long sum = dfs(i, j);

            if(sum % k == 0) {
                ans++;
            }
        }
    }
}
  return ans;

    }
};