/**
 * Author: Cellul4r
 * Description: None
 */

int search(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(nums[mid] == target) {
            return mid;
        } else if(nums[mid] < target) {
            if(nums[mid] >= nums[0]) {
                // this guys in the first group
                l = mid + 1;
            } else {
                // this guys in the second group
                if(nums[nums.size() - 1] >= target) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            
        } else {
            if(nums[mid] >= nums[0]) {
                // this guys in the first group
                if(nums[0] <= target) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                // this guys in the second group
                r = mid - 1;
            }
        }
    }
    return -1;
}
