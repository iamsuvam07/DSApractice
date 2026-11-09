class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        

        int n = arrival.size();


        vector<int> count(k, 0);


        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> busy;



        for (int i = 0; i < n; i++) {

            while (!busy.empty() && busy.top().first <= arrival[i]) {
                available.insert(busy.top().second);
                busy.pop();
            }

            if (available.empty()) continue;

    auto it = available.lower_bound(i % k);
     
     if (it == available.end()) {
        it = available.begin();


     }

     int server = *it;
     available.erase(it);
     
     count[server]++;

     busy.push({arrival[i] + load[i], server});

        } 

        int mx = *max_element(count.begin(), count.end());


        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == mx) {

                ans.push_back(i);
            }
        }

        return ans;
    }
};