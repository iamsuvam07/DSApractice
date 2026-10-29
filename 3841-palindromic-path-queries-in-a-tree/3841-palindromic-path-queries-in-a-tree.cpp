class Solution {
public:


static const int LOG = 17;

vector<vector<int>> g;
vector<vector<int>> up;
vector<int> tin, tout, depth;

vector<int> bit;
int timer;

void updateBIT(int idx, int val, int n) {
    for (; idx <= n; idx += idx & -idx) 
    bit[idx] ^= val;

}

int queryBIT(int idx) {
    int res = 0;
    for (; idx > 0; idx -= idx & -idx)
    res ^= bit[idx];
    return res;
}

int getMask(char c) {
    return 1 << (c - 'a');

}

void dfs(int u, int p) {
    tin[u] = ++timer;
    up[u][0] = p;

    for(int j = 1; j < LOG; j++) 
    up[u][j] = up[up[u][j - 1]][j - 1];


    for(int v : g[u]) {
        if ( v == p) continue;

        depth[v] = depth[u] + 1;
        dfs(v, u);
    }

    tout[u] = timer;
}

int lca(int u, int v) {
    if (depth[u] < depth[v])
    swap(u, v);

int diff = depth[u] - depth[v];


    for (int j = LOG - 1; j >= 0; j--) {
        if (diff & (1 << j))
        u = up[u][j];
    }

    if (u == v)
    return u;

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        
auto suneravilo = queries;

g.assign(n, {});
up.assign(n, vector<int>(LOG));
tin.assign(n, 0);
tout.assign(n, 0);
depth.assign(n, 0);
bit.assign(n + 1, 0);



for (auto &e : edges) {
    int u = e[0];
    int v = e[1];


    g[u].push_back(v);
    g[v].push_back(u);


}

timer = 0;

dfs(0, 0);

vector<int> prefix(n);


function<void(int, int, int)> build = [&](int u, int p, int mask) {
    mask ^= getMask(s[u]);
    prefix[u] = mask;

    updateBIT(tin[u], getMask(s[u]), n);


    for (int v : g[u]) {
        if ( v == p) continue;
        build(v, u, mask);

    }
};


function<void(int, int, int)> init = [&](int u, int p, int mask) {
    mask ^= getMask(s[u]);
    prefix[u] = mask;



 updateBIT(tin[u], mask ^ prefix[p], n);

 for (int v : g[u]) {
    if(v == p) continue;
    init(v, u, mask);

 }   
};


for (int u = 0; u < n; u++) {
    int mask = getMask(s[u]);

    updateBIT(tin[u], mask, n);
    updateBIT(tout[u] + 1, mask, n);
}

vector<bool> ans;

for (string &q : suneravilo) {
    stringstream ss(q);

    string type;

    ss >> type;

    if (type == "update") {
        int u;
        char c;

        ss >> u >> c;

        int oldMask = getMask(s[u]);
        int newMask = getMask(c);

        int change = oldMask ^ newMask;


        updateBIT(tin[u], change, n);
        updateBIT(tout[u] + 1, change, n);

        s[u] = c;

    }

    else {
        int u, v;

        ss >> u >> v;
        int w = lca(u, v);

        int mask = queryBIT(tin[u]) ^ queryBIT(tin[v]) ^ getMask(s[w]);


        bool possible = (mask == 0 || (mask & (mask - 1)) == 0);

        ans.push_back(possible);

    }
}

return ans;
    }
};