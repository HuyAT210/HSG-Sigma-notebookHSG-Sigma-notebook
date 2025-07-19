/**
 * Author: Cellul4r
 * Description: None
 */

private:
    vector<vector<int>> res;
    void recur(vector<int>& now, int& prev, vector<int>& candidates, int& target) {
        if(target == 0) {
            res.push_back(now);
            return;
        }
        
        for(int& x : candidates) {
            if(x <= target && x >= prev) {
                target -= x;
                now.push_back(x);
                recur(now, x, candidates, target);
                now.pop_back();
                target += x;
            }
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> now;
        int prev = 0;
        recur(now, prev, candidates, target);
        return res;
    }
};
