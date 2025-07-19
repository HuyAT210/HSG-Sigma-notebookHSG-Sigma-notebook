/**
 * Author: Cellul4r
 * Description: None
 */

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> ans;
    vector<vector<string>> res;
    
    for(string& s : strs) {
        array<int,26> alpha = {0};
        for(char& c : s) {
            alpha[c-'a']++;
        }

        string key;
        for(int& x : alpha) {
            key += to_string(x) + ".";
        }
        ans[key].push_back(s);
    }

    for(auto &[x,y] : ans) {
        res.push_back(y);
    }
    return res;    
}
