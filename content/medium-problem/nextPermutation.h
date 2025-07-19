/**
 * Author: Cellul4r
 * Description: None
 */

void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int idx = -1;
    for(int i = n - 2; i >= 0; i--) {
        if(nums[i] < nums[i+1]) {
            idx = i;
            break;
        }
    }
    if(idx == -1) {
        sort(nums.begin(), nums.end());
        return;
    }
    int mn = nums[idx+1];
    int k = idx + 1;
    for(int i = idx + 1; i < n; i++) {
        if(nums[i] > nums[idx] && nums[i] < mn) {
            mn = nums[i];
            k = i;
        }
    }
    swap(nums[idx], nums[k]);
    sort(nums.begin()+idx+1, nums.end());
    
}
