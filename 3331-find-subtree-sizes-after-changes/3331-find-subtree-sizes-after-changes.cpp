class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        

int n = parent.size();

vector<vector<int>> adj(n);


for (int i = 1; i < n; i++) {
    adj[parent[i]].push_back(i);
}

vector<int> ans(n, 1);
vector<int> path[26];

function<void(int, int)> dfs = [&](int node, int par) {
    int c = s[node] - 'a';
    path[c].push_back(node);

    for (int child : adj[node]) {
        dfs(child, node);

    }
                int newParent = par;

            if (path[c].size() > 1) {
                newParent = path[c][path[c].size() - 2];
            }

            if (newParent != -1) {
                ans[newParent] += ans[node];
            }

            path[c].pop_back();
        };

        dfs(0, -1);
        return ans;
 



    }
};