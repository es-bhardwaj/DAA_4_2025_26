//Brute Force (Sliding Window)
class Solution {
  public:
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        vector<int> res;
        int lt=0, rt=arr.size();
        while(lt<=rt-k){
            int mx=0;
            for(int i=lt; i<lt+k; i++){
                mx=max(mx,arr[i]);
            }
            res.push_back(mx);
            lt++;
        }
        return res;
    }
};

//Using priority queue
class Solution {
  public:
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        vector<int> res;
        priority_queue<pair<int,int>> pq;
        for(int i=0; i<k; i++){
            pq.push({arr[i],i});
        }
        res.push_back(pq.top().first);
        for(int i=k; i<arr.size(); i++){
            pq.push({arr[i],i});
            while(pq.top().second<=i-k){
                pq.pop();
            }
            res.push_back(pq.top().first);
        }
        return res;
    }
};