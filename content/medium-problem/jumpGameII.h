/**
 * Author: Cellul4r
 * Description: None
 */

int jump(vector<int>& nums) {
    int n = nums.size();
    int ans = 0, i = 0;
    while(i < n - 1) {
        int j = nums[i] + i;
        if(j >= n - 1) {
            break;
        }
        int idx = i + 1, curr = nums[i+1];
        i++;
        ans++;
        int k = 1;
        while(i <= j && i < n) {
            if(nums[i] + k > curr) {
                idx = i;
                curr = nums[i] + k;
            }
            k++;
            i++;
        }
        // cerr << idx << endl;
        i = idx;
    }
    return ans + 1;  
}
