/**
 * Author: Cellul4r
 * Description: None
 */
int threeSumClosest(vector<int>& nums, int target) {
     // Sort the array to use the two-pointer approach
    sort(nums.begin(), nums.end());

    //Initialize closest sum and minimal difference
    int n = nums.size();
    int closestSum = nums[0] + nums[1] + nums[2];  // initial triplet
    int minDiff = abs(closestSum - target);        // initial diff

    // Step 3: Fix one number, use two pointers for the other two
    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            // Move the pointers based on comparison with target
            if (sum < target) {
                left++;  // Try a bigger sum
            } else if (sum > target) {
                right--; // Try a smaller sum
            } else {
                // Exact match found, best possible answer
                return sum;
            }

            int diff = abs(sum - target);
            // If this sum is closer to target, update closestSum
            if (diff < minDiff) {
                minDiff = diff;
                closestSum = sum;
            }
        }
    }

    return closestSum;
}
