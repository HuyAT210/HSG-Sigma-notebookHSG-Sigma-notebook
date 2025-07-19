/**
 * Author: Cellul4r
 * Description: None
 */

private:
    vector<int> cur;
    vector<vector<int>> res;
    void recur(int i, int target, int prev, vector<int>& candidates) {
        if(i == candidates.size() || target == 0) {
            if(target == 0) {
                res.push_back(cur);
            }
            return;
        }

        if(candidates[i] > target) return;

        if(candidates[i] != prev) recur(i+1, target, prev, candidates);
        if(candidates[i] > target) return;
        cur.push_back(candidates[i]);
        recur(i+1, target - candidates[i], candidates[i], candidates);
        cur.pop_back();
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        recur(0, target, 0, candidates);
        return res;
    }
};
