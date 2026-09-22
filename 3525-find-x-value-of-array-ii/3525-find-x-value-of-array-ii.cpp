class Solution {
public:
   
    struct Node {
        int prod = 1;
        int cnt[5] = {0};

    };

    int k;
    vector<Node> tree;

    Node merge(Node left, Node right) {
        Node res;

res.prod = (left.prod * right.prod) % k;

        for (int i = 0; i < k; i++) {
            res.cnt[i] += left.cnt[i];

        }

        for (int i = 0; i < k; i++) {


            int rem = (left.prod * i) % k;
            res.cnt[rem] +=right.cnt[i];
        }

        return res;
    }


  void build(int node, int l, int r, vector<int>& nums) {

        if (l == r) {
         
         int rem = nums[l] % k;

         tree[node].prod = rem;
         tree[node].cnt[rem] = 1;

            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

      tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);

    }

    void update(int node, int l, int r, int pos, int value) {

        if (l == r) {

           int rem  = value % k;

           tree[node].prod = rem;

           for (int i = 0; i < k; i++) {
            tree[node].cnt[i] = 0;

           }

          tree[node].cnt[rem] = 1;

            return;
        }

        int mid = l + (r - l) / 2;


if (pos <= mid) {


update(node * 2, l, mid, pos, value);
 }
  else  {

  
    update(node * 2 + 1, mid + 1, r, pos, value);
  }


tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

Node query(int node, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr)
  {

    return tree[node];
  }


        int mid = l + ( r - l) / 2;


        if (qr <= mid)  {

 return query(node * 2, l, mid, ql, qr);
        }


   if (ql > mid) {
            return query(node * 2 + 1, mid + 1, r, ql, qr);
   }

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {

this->k = k;

int n = nums.size();

tree.resize(4 * n );

build(1, 0, n - 1, nums);

vector<int> answer;

for (auto &q : queries) {


        int index = q[0];

        int value = q[1];
        int start = q[2];
        int x = q[3];

        update(1, 0, n - 1, index, value);

 Node res = query(1, 0, n - 1, start, n - 1);

    answer.push_back(res.cnt[x]);

    }   

return answer;
    }
};